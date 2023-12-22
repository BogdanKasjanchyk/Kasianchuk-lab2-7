#include "concert.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>

// Concert

double Concert::get_ticketPrice() {
    return this->ticketPrice;
}

Concert::Concert(string concertName, string location, string date, int maxVisitors, int ticketPrice, bool isSoldOut) {
    this->concertName = concertName;
    this->location = location;
    this->date = date;
    this->maxVisitors = maxVisitors;
    this->ticketPrice = ticketPrice;
    this->isSoldOut = isSoldOut;
}

void Concert::set_concertName(string concertName) {
    this->concertName = concertName;
}

void Concert::set_location(string location) {
    this->location = location;
}                                                       //Перевантаження функції

void Concert::set_location(char* location) {
    this->location = string(location);
}

string Concert::get_location() {
    return this->location;
}

void Concert::set_date(string date) {
    this->date = date;
}

int Concert::totalConcerts = 0;

string Concert::get_concertName() {
    return this->concertName;
}
string Concert::get_date() {
    return this->date;
}

void Concert::showConcert(vector<Concert*>& concerts) {

    ifstream inFile("concert.txt");

    if (!inFile) {
        cout << "Не вдалося відкрити файл";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

}

void Concert::writeConcert(vector<Concert*>& concerts) {
    ofstream outFile("concert.txt", ios::trunc);
    int numConcerts = min(5, (int)concerts.size());
    for (int i = 0; i < numConcerts; i++) {
        outFile << "Назва концерту: " << concerts[i]->get_concertName() << endl;
        outFile << "Локація: " << concerts[i]->get_location() << endl;
        outFile << "Дата: " << concerts[i]->get_date() << endl;
        outFile << "Макс. кількість відвідувачів: " << concerts[i]->get_maxVisitors() << endl;
        outFile << "Ціна квитків: " << concerts[i]->get_ticketPrice() << endl;
        outFile << "Стан продажу: " << (concerts[i]->get_ticketStatus() ? "1" : "0") << endl;
        outFile << "------------------------" << endl;
    }

    outFile.close();
}

void Concert::set_maxVisitors(int maxVisitors) {
    this->maxVisitors = maxVisitors;
}

int Concert::get_maxVisitors() {
    return this->maxVisitors;
}

void Concert::set_ticketPrice(int ticketPrice) {
    this->ticketPrice = ticketPrice;
}

void Concert::set_ticketStatus(bool isSoldOut) {
    this->isSoldOut = isSoldOut;
}

bool Concert::get_ticketStatus() {
    return this->isSoldOut;
}