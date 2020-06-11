#include <string>
#include <iostream>
#include <cppkafka/cppkafka.h>
#include "cppkafka/consumer.h"
#include "cppkafka/configuration.h"
#include <cppkafka/utils/consumer_dispatcher.h>
#include <csignal>
#include <string>

using namespace std;
using namespace cppkafka;

#ifndef MAINAPP_FORCONECT_H
#define MAINAPP_FORCONECT_H

class forConnect{
    forConnect();
    ~forConnect();
    void produse(string topic, string message) {
        Configuration config = {
                { "metadata.broker.list", "127.0.0.1:9092" },
                { "group.id", "test-consumer-group" }
        };

        Producer producer(config);
        producer.produce(MessageBuilder(topic).partition(0).payload(message));
        sleep(5);
        producer.flush();
    }
    void printList(string topic,string addres){
        cout<<"List of animal:"<<endl;
        Configuration config = {
                { "metadata.broker.list", addres },
                { "group.id", "test-consumer-group" }
        };
        Consumer consumer(config);
        consumer.subscribe({ topic });
        ConsumerDispatcher dispatcher(consumer);
        dispatcher.run(
                // Callback executed whenever a new message is consumed
                [&](Message msg) {
                    if(msg.get_payload().get_size()<=1)
                        dispatcher.stop();
                    cout << msg.get_payload() << endl;
                    consumer.commit(msg);
                },
                // Whenever there's an error (other than the EOF soft error)
                [](Error error) {
                    cout << "[+] Received error notification: " << error << endl;
                },
                // Whenever EOF is reached on a partition, print this
                [](ConsumerDispatcher::EndOfFile, const TopicPartition& topic_partition) {
                    cout << "Reached EOF on partition " << topic_partition << endl;
                }
        );
    }

    string subs(string topic,string addres){
        string answer;
        Configuration config = {
                { "metadata.broker.list", addres },
                { "group.id", "test-consumer-group" },
                { "auto.offset.reset", "latest"}
        };
        Consumer consumer(config);
        consumer.subscribe({ topic });
        ConsumerDispatcher dispatcher(consumer);
        dispatcher.run(
                [&](Message msg) {
                    answer= msg.get_payload();
                    consumer.commit(msg);
                    dispatcher.stop();
                },
                [](Error error) {
                    cout << "[+] Received error notification: " << error << endl;
                },
                [](ConsumerDispatcher::EndOfFile, const TopicPartition& topic_partition) {
                    cout << "Reached EOF on partition " << topic_partition << endl;
                }
        );
        return answer;
    }



};

#endif //MAINAPP_FORCONECT_H
