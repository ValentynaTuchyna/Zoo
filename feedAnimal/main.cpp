#include <iostream>
#include <cppkafka/cppkafka.h>
#include <cppkafka/consumer.h>
#include <cppkafka/utils/consumer_dispatcher.h>
#include <cppkafka/configuration.h>
#include <csignal>


using namespace std;
using namespace cppkafka;

void produse(string topic,string message){
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9095" },
    };
    Producer producer(config);
    producer.produce(MessageBuilder(topic).partition(0).payload(message));
    sleep(5);
    producer.flush();
}
int balance;
double size;

void selectEat(string str) {
   size_t next = str.find(" ", 0);
    size = stod(str.substr(0, next));
    balance = stoi(str.substr(next + 1, str.length()));
    if (size < 10.0)
        balance  -= 20;
    else if (size < 50.0)
        balance  -= 30;
    else if (size < 100.0)
        balance  -= 50;
    else if (size < 150.0)
        balance  -= 60;
    else if (size >= 150.0) {
       produse("balance", "ERROR: the animal is too big");
    }
    cout<<to_string(balance )<<endl;
    if (balance  < 0)
        produse("balance", "ERROR: not enough money");
    else if(size <150)
        produse("balance", to_string(balance ));
}

int main() {
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" },
            { "group.id", "test-consumer-group" },
            { "auto.offset.reset", "latest"}
    };

    Consumer consumer(config);
    consumer.subscribe({ "feedAnimal" });
    ConsumerDispatcher dispatcher(consumer);
    dispatcher.run(
            [&](Message msg) {
                selectEat(msg.get_payload());
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
