#include "Admin.h"

Admin::Admin() {
 cout<<"Admin start work day"<<this<<endl;
 this->workDay=true;
}
Admin::~Admin() {
    cout<<"Admin end work day"<<this<<endl;
}

void Admin::produse(string topic, string message) {
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" },
            { "group.id", "test-consumer-group" }
    };

    Producer producer(config);
    producer.produce(MessageBuilder(topic).partition(0).payload(message));
    sleep(5);
    producer.flush();
}
void Admin::printList(string topic,string addres){
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

string Admin::subs(string topic,string addres){
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



void Admin::addAnimal() {
    string str, mes ="AddAnimal ";
    cout<<"Press type of annimal: ";
    cin>>str;
    mes+="'"+str +"',";
    cout<<"Press age of annimal: " ;
    cin>>str;
    mes+=str +",'";
    cout<<"Press gender of annimal: " ;
    cin>>str;
    mes+=str +"',";
    cout<<"Press weight of annimal: " ;
    cin>>str;
    mes+=str +",'";
    cout<<"Press colour of annimal: " ;
    cin>>str;
    mes+=str +"','";
    cout<<"Press name of annimal: " ;
    cin>>str;
    mes+=str +"','";
    cout<<"Press nutrition of annimal (herb/meat): " ;
    cin>>str;
    if((str!="meat")&&(str!="herb"))
        cout<<"Please use only herb or meat"<<endl;
    else{
    mes+=str +"',";
    cout<<"Press cell of annimal: " ;
    cin>>str;
    mes+=str;
    cout<<mes<<endl;
    produse("command",mes);
    cout<<subs("response","127.0.0.1:9094")<<endl;
    }
}

void Admin::moveAnimal() {
    string s;
    int k;
    cout<<"who you waant move?"<<endl;
    cin >>s;
    produse("command","GetInfo "+s);
    printList("response","127.0.0.1:9094");
    cout<<"Pres name of animal that u want move"<<endl;
    cin>>s;
    cout<<"Pres cell for move"<<endl;
    cin>>k;
    if(!cin){
        cout<<"ERROR: No number";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else{
    produse("command","MoveAnimal "+s+" "+to_string(k));
    cout<<subs("response","127.0.0.1:9094")<<endl;
    }
}


void Admin::nextStep() {
    char choice;
    cout << "What you want to do?" << endl
         << "1)Add animal" << endl
         << "2)Move animals" << endl
         << "3)End work day" << endl;
    cin >> choice;
    switch (choice) {
        case '1': {
            addAnimal();
            break;
        };
        case '2': {
            moveAnimal();
            break;
        };
        case '3': {
            this->workDay=false;
            break;
        };
        default:
            cout << "uncorect choise";
    }
}