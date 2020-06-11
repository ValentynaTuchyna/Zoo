#include <iostream>
#include <cppkafka/cppkafka.h>
#include "cppkafka/consumer.h"
#include "cppkafka/configuration.h"
#include <cppkafka/utils/consumer_dispatcher.h>
#include <csignal>
#include <string>

using namespace std;
using namespace cppkafka;

#ifndef MAINAPP_VISITOR_H
#define MAINAPP_VISITOR_H

class Visitor {
    string type;
    string money;
public:
    bool ticket;

    Visitor(string old,string mon,const bool tk = 0);
    Visitor(const Visitor &other) = delete;
    Visitor& operator=(const Visitor &other) = delete;
    ~Visitor();
    void BuyTicket();
    void feedAnimals();
    void lookAnimals();
    void getInfo();
    void nextStep();

    void produse(string topic,string message);
    string subs(string topic,string addres);
    void printList(string topic,string addres);
};

#endif //MAINAPP_VISITOR_H
