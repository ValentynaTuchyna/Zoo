#include <string>
#include <iostream>
#include <cppkafka/cppkafka.h>
#include "cppkafka/consumer.h"
#include "cppkafka/configuration.h"
#include <cppkafka/utils/consumer_dispatcher.h>
#include <csignal>
#include <limits>

#ifndef MAINAPP_ADMIN_H
#define MAINAPP_ADMIN_H

using namespace std;
using namespace cppkafka;

class Admin {
public:
    bool workDay;

   Admin();
   Admin(const Admin &other) = delete;
   Admin& operator=(const Admin &other) = delete;
   ~Admin();
    void produse(string topic,string message);
    string subs(string topic,string addres);
    void printList(string topic,string addres);


   void moveAnimal();
   void addAnimal();
   void nextStep();

};


#endif //MAINAPP_ADMIN_H
