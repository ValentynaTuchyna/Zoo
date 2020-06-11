#include <string>
#include <iostream>
#include <mysql++.h>
#include <vector>
#include "Animal.h"

#ifndef ANIMALDB_ZOO_H
#define ANIMALDB_ZOO_H

#define dbname "my_zoo"
#define server "localhost"
#define user "usr1"
#define pass "password"

using namespace std;
using namespace mysqlpp;

class Zoo{
    Connection con;
public:
    Zoo(){
     con = Connection(dbname, server, user, pass);
     if(con.connected())
         cout<<"Successful connection"<<endl;
     else cout<<"No connection"<<endl;
    }
    ~Zoo(){
        cout<<"Disconnect"<<endl;
        con.disconnect();
    };

    bool checkCell(string str,string cell){
        string s;
        if(str.find("herb",0)!=str.npos)
            s = "SELECT * FROM Animals WHERE  CELL='"+cell+"' AND NUTRITION='meat';";
        else{
            s = "SELECT * FROM Animals WHERE  CELL='"+cell+"' AND NUTRITION='herb';";
        }
        Query q = con.query(s);
        StoreQueryResult sq = q.store();
        if(sq.empty()) return true;
        else return false;
    }

    string addAnimal(string prop){
        string s;
            string cell= prop.substr( prop.find_last_of(",")+1,prop.length() );
            if(checkCell(prop,cell)){
                s = "INSERT INTO Animals VALUES ("+prop+");";
                Query q = con.query(s);
                StoreQueryResult sq = q.store();
                return "Successfully added";
            }
            else return "ERROR: incompatibility between animals in a cage";
    };

    string moveAnimal(string prop){
        size_t  next = prop.find(" ", 0 ) ;
        string name= prop.substr( 0, next );
        string cell = prop.substr( next+1, prop.length());
        string s;
        Query q = con.query("SELECT NUTRITION FROM Animals WHERE NAME='"+name+"';");
        StoreQueryResult sq = q.store();
        if(!sq.empty()){
            StoreQueryResult::const_iterator it = sq.begin();
            Row row = *it;
            s=row[0].c_str();
            if(checkCell(s,cell)){
                s = "UPDATE Animals SET CELL='"+cell+"' WHERE NAME='"+name+"';";
                Query q = con.query(s);
                StoreQueryResult sq = q.store();
                return "Successfully move";
            }
            else return "ERROR: incompatibility between animals in a cage";
        }
        else return "ERROR: incorect name";
    };

    vector <Animal*> listOfAnimall(string prop){
        string s;
        vector<Animal*> *animals = new vector<Animal*>;
        if (prop=="all")
            s = "SELECT * FROM Animals ;";
        else
            s = "SELECT * FROM Animals WHERE TYPE='"+prop+"' OR CELL='"+prop+"';"; //TYPE, NAME,CELL
        Query q = con.query(s);
        StoreQueryResult sq = q.store();
        if (!sq.empty()) {
            animals->reserve(sq.num_rows());
            StoreQueryResult::const_iterator it;
            for (it = sq.begin(); it != sq.end(); it++){
                Row row = *it;
                animals->push_back(new Animal(row[0].c_str(),atoi(row[1]),
                        row[2].c_str(),atof(row[3]),row[4].c_str(),
                        row[5].c_str(),row[6].c_str(),atoi(row[7])));
            }
        }
     return *animals;
    };

    string feedAnimal(string prop){
        string s = "SELECT AVG(WEIGHT) FROM Animals WHERE TYPE='"+prop+"'AND NUTRITION='herb';";
        Query q = con.query(s);
        StoreQueryResult sq = q.store();
        StoreQueryResult::iterator it;
        it = sq.begin();
        Row row = *it;
        if(atof(row[0])<=0.0)
             return "ERROR: The animal is absent or cannot be fed";
        else{
            s=to_string(atof(row[0]));
            return s;
        }

    }

};

#endif //ANIMALDB_ZOO_H
