#include <cppkafka/cppkafka.h>
#include <cppkafka/consumer.h>
#include <cppkafka/utils/consumer_dispatcher.h>
#include <cppkafka/configuration.h>
#include <iostream>
#include "Zoo.h"

using namespace std;
using namespace cppkafka;

Zoo myzoo;
vector<Animal*> an;

void produse(string topic,string message){
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9094" },
    };
    Producer producer(config);
    producer.produce(MessageBuilder(topic).partition(0).payload(message));
    sleep(3);
    producer.flush();
}

void getComand(string msg){
    size_t  next = msg.find(" ", 0 ) ;
    string command = msg.substr( 0, next );
    string properties = msg.substr( next+1, msg.length());
    if (command =="AddAnimal"){
        produse("response", myzoo.addAnimal(properties));
    }
    if (command =="GetInfo"){
         an = myzoo.listOfAnimall(properties);
        if(an.empty()){
            produse("response", "ERROR : animal is missing");
        }
        else {
            for (auto i = 0; i < an.size(); i++) {
                cout << an[i]->getType() << +" " << an[i]->getName() << " " << an[i]->getCell() << endl;
                produse("response", an[i]->getType() + " " + an[i]->getName() + " " + to_string(an[i]->getCell()));
                delete an[i];
            }
        }
        produse("response", " ");
        an.clear();
    }
    if (command =="LookAnimal"){//TYPE, AGE,GENDER,WEIGHT,COLOR
        an = myzoo.listOfAnimall(properties);
        if(an.empty()){
            produse("response", "ERROR : animal is missing");
        }
        else {
            for (auto i = 0; i < an.size(); i++) {
                cout << an[i]->getType() << " " << an[i]->getAge() << " " << an[i]->getGender()
                     << " " << an[i]->getWeight() << " " << an[i]->getColour() << endl;

                produse("response", an[i]->getType() + " " + to_string(an[i]->getAge()) + " "
                                    + an[i]->getGender() + " " + to_string(an[i]->getWeight()) + " " +
                                    an[i]->getColour());
                delete an[i];
            }
        }
        produse("response", " ");
        an.clear();
    }
    if (command =="MoveAnimal"){
        produse("response", myzoo.moveAnimal(properties));
    }
    if (command == "FeedAnimal"){
        produse("response",myzoo.feedAnimal(properties));
    }
}


int main() {
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" },
            { "group.id", "test-consumer-group" },
            { "auto.offset.reset", "latest"}
    };
    Consumer consumer(config);
    consumer.subscribe({ "command" });
    ConsumerDispatcher dispatcher(consumer);
    dispatcher.run(
            [&](Message msg) {
                getComand(msg.get_payload());
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
