#include <cppkafka/cppkafka.h>
#include <cppkafka/consumer.h>
#include <cppkafka/utils/consumer_dispatcher.h>
#include <cppkafka/configuration.h>
#include <iostream>


using namespace std;
using namespace cppkafka;

#define STUDTICKET 20;
#define CHILDTICKET 10;
#define ADULTTICKET 40;

void produse(string topic,string message){

    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9093" },
    };
    Producer producer(config);
    producer.produce(MessageBuilder(topic).partition(0).payload(message));
    sleep(3);
    producer.flush();
}


void giveChange(string str){
    sleep(5);
        size_t  next = str.find(" ", 0 ) ;
        string type = str.substr( 0, next );
        int cost = stoi(str.substr(next + 1, str.length()));
        if((type!="child")&&(type!="student")&&(type!="adult"))
            produse("ticket","ERROR: invalid type of visitor");
        else {
            if (type == "child")
                cost = cost - CHILDTICKET;
            if (type == "student")
                cost = cost - STUDTICKET;
            if (type == "adult")
                cost = cost - ADULTTICKET;
            if (cost < 0)
                produse("ticket", "ERROR: not enough money to buy ticket");
            else
                produse("ticket", to_string(cost));
        }
}

int main() {
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" },
            { "group.id", "test-consumer-group" },
            { "auto.offset.reset", "latest"}
    };

    Consumer consumer(config);
    consumer.subscribe({ "visitor" });
    ConsumerDispatcher dispatcher(consumer);
    dispatcher.run(
            [&](Message msg) {
                giveChange(msg.get_payload());
                consumer.commit(msg);
            },
            [](Error error) {
                cout << "[+] Received error notification: " << error << endl;
            },
            [](ConsumerDispatcher::EndOfFile, const TopicPartition& topic_partition) {
                cout << "Reached EOF on partition " << topic_partition << endl;
            }
    );
}
