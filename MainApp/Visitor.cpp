#include "Visitor.h"

Visitor::Visitor(string old, string mon, const bool tk) {
    type =old;
    money =mon;
    ticket =tk;
    cout<<"Visitor is created"<<endl;
};

Visitor::~Visitor() {
    cout<<"Visitor is drop"<<endl;
};
void Visitor::produse(string topic, string message) {
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" },
            { "group.id", "test-consumer-group" }
    };

    Producer producer(config);
    producer.produce(MessageBuilder(topic).partition(0).payload(message));
    sleep(5);
    producer.flush();
}
void Visitor::printList(string topic,string addres){
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
string Visitor::subs(string topic,string addres){
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


void Visitor::BuyTicket() {
    string str;
    cout<<"Buy ticket for "+type<<endl;
    produse("visitor",type +" "+ money);
    str =subs("ticket", "127.0.0.1:9093");
    if(str.find("ERROR",0)!=str.npos)
        cout<<str<<endl;
    else {
        money = str;
        cout<<"The rest of money: "+money<<endl;
        this->ticket=true;
    }
};

void Visitor::feedAnimals() {
 cout<<"What animal you want feed?"<<endl;
 string str;
 cin>>str;
 produse("command","FeedAnimal "+str);
 str=subs("response", "127.0.0.1:9094");
    if(str.find("ERROR",0)!=str.npos)
        cout<<str<<endl;
    else{
        produse ("feedAnimal",str +" "+ money);
        str=subs("balance", "127.0.0.1:9095");
        if(str.find("ERROR",0)!=str.npos)
            cout<<str<<endl;
        else {
            money=str;
            cout<<"The rest of money ="<<money<<endl;
        }
    }
};

void Visitor::getInfo() {
    cout<< "About what you want get info?"<<endl;
    string str ;
    cin>>str;
    produse("command","GetInfo "+str);
   printList("response","127.0.0.1:9094");
};
void Visitor::lookAnimals() {
    cout<< "On what you want look(enter number of cell or animal type)?"<<endl;
    string str ;
    cin>>str;
    produse("command","LookAnimal "+str);
    printList("response","127.0.0.1:9094");
};

void Visitor::nextStep() {
    char choice;
    cout << endl<<"What you want to do?" << endl
         << "1)Look on animals" << endl
         << "2)Feed animals" << endl
         << "3)Get info about animals" << endl
         << "4)Exit Zoo" << endl;
    cin >> choice;
    switch (choice) {
        case '1': {
            lookAnimals();
            break;
        };
        case '2': {
            feedAnimals();
            break;
        };
        case '3': {
            getInfo();
            break;
        };
        case '4': {
            this->ticket=false;
            break;
        };
        default:
            cout << "ERROR: Incorrect input";
    }
};




