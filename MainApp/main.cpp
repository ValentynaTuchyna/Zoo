#include <iostream>
#include <limits>
#include "Visitor.h"
#include "Admin.h"

using namespace std;

string str;
int main() {
    char choice;
    cout<<"Welcome to ZOO!"<<endl;
    do {
        cout << "What you want to do?" << endl
             << "1)Create Visitor" << endl
             << "2)Create Admin" << endl
             << "3)Exit" << endl;
        cin >> choice;
        switch (choice) {
            case '1': {
                cout<<"Enter type of visitor(student/child/adult)"<<endl;
                string type;
                cin>>type;
                cout<<"How match money have visitor?"<<endl;
                int money;
                cin>>money;
                if(!cin){
                    cout<<"ERROR: Not number "<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else{
                    Visitor visitor(type, to_string(money));
                    visitor.BuyTicket();
                    while(visitor.ticket) {
                        visitor.nextStep();
                    }
                }
                break;
            };
            case '2': {
                Admin adm;
                while(adm.workDay) {
                    adm.nextStep();
                }
                break;
            };
            case '3': {
                break;
            }
            default:
                cout << "ERROR: Incorrect input";
        }
    }while(choice!='3');
    return 0;
};