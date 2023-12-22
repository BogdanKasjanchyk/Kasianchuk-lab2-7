#include "human.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void Human::set_name(string name) {
    this->name = name;
}
string Human::get_name() {
    return this->name;
}

void Human::set_surname(string surname) {
    this->surname = surname;
}

string Human::get_surname() {
    return this->surname;
}

void Human::set_sex(string sex) {
    this->sex = sex;
}


string Human::get_sex() {
    return this->sex;
}

void Human::set_age(int age) {
    this->age = age;
}

int Human::get_age() {
    return this->age;
}
