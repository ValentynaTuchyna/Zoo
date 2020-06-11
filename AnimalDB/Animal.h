#include <string>
#include <iostream>
#include <mysql++.h>


#ifndef MAINAPP_ANIMAL_H
#define MAINAPP_ANIMAL_H


using namespace std;
using namespace mysqlpp;

class Animal {
    string type;
    int age;
    string gender;
    double weight;
    string colour;
    string name;
    string nutrition;
    int cell;
public:
    Animal(){
        cout<<"Add new animal"<<this<<endl;
    };
    Animal(string Type,int Age,string Gender,double Weight,
           string Colour,string Name,string Nutrition, int Cell){
        cout<<"Add new animal"<<this<<endl;
        type = Type;
        age = Age;
        gender = Gender;
        weight = Weight;
        colour = Colour;
        name = Name;
        nutrition = Nutrition;
        cell = Cell;
    };
    Animal(const Animal &other) = delete;
    Animal& operator=(const Animal &other) = delete;

    ~Animal(){
        cout<<"Destructor"<<this<<endl;
    };

    string getType(){
        return type;
    };
    string getName(){
        return name;
    };
    string getNutrition(){
        return nutrition;
    };
    int getAge(){
        return age;
    };
    string getGender(){
        return gender;
    };
    string getColour(){
        return colour;
    };
    double getWeight(){
        return weight;
    };
    int getCell(){
        return cell;
    };
};

#endif //MAINAPP_ANIMAL_H
