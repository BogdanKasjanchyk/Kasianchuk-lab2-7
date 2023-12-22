#include "human.h"
#include "visitor.h"
#include "manager.h"
#include "singer.h"
#include "concert.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Manager

Manager::Manager() {
   this->name  = "Степан";
   this->surname = "Петров";
   this->age = 22;
   this->sex = "Чоловік";
}

void Manager::addConcerts(vector<Concert*>& concerts, string location, string date, int ticketPrice, int i) {

    concerts[i]->set_location(location);
    concerts[i]->set_date(date);
    concerts[i]->set_ticketPrice(ticketPrice);

}

void Manager::receiveInfoAboutPickedConcerts(Concert &concert) {
    ifstream file("singerSchedule.txt");
    string concertName;

    cout << "Концерти, на які піде співак:" << endl;
    while (getline(file, concertName)) {
        cout << concertName << endl;
    }
}


void Manager::loadConcerts(vector<Concert*>& concerts) {

    try
    {
        Concert* masquarade = new Concert("Маскарад ляльок", "location", "date", 1500, 15, false);
        Concert* rock = new Concert("Рок-фестиваль", "location", "date", 25000, 25, false);
        Concert* opera = new Concert("Опера", "location", "date", 2344, 20, true);
        Concert* jazz = new Concert("Джазовий вечір", "location", "date", 2324, 10, false);
        Concert* orchestra = new Concert("Симфонічний оркестр", "location", "date", 3533, 30, true);

        concerts.push_back(masquarade);
        concerts.push_back(rock);
        concerts.push_back(opera);
        concerts.push_back(jazz);
        concerts.push_back(orchestra);
    }
    catch (const std::bad_alloc& e) {
       cerr << "Помилка виділення пам'яті: " << e.what() << '\n';
    }

}

void Manager::loadVisitors(vector<Visitor>& visitors, vector<Concert*>& concerts) {
    int ticket_id = rand(); // Встановлюємо ID квитка
    int balance = rand() % 101 + 100;

    Concert* concert = concerts[0]; // Вибираємо концерт для квитка
    Visitor jane("Jane", "Doe", "Female", 28, ticket_id, concert);
    ticket_id = rand();
    concert = concerts[1];
    Visitor alice("Alice", "Smith", "Female", 31, ticket_id, concert);
    ticket_id = rand();
    concert = concerts[2];
    Visitor bob("Bob", "Johnson", "Male", 35, ticket_id, concert);
    ticket_id = rand();
    concert = concerts[3];
    Visitor charlie("Charlie", "Brown", "Male", 33, ticket_id, concert);
    ticket_id = rand();
    concert = concerts[4];
    Visitor emily("Emily", "Davis", "Female", 30, ticket_id, concert);

}

void Manager::informSingerAboutConcert(Singer& singer, vector<Concert*>concerts) {
    singer.receiveConcertInfo(concerts);
}

void Manager::findUserByIdInFiles(string filename, int id) {
    ifstream inFile(filename);
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, surname, sex, concertName;
            int age, ticketId;

            ss >> name >> surname >> age >> sex >> ticketId >> concertName;

            if (ticketId == id) {
                cout << "Ім'я: " << name << endl;
                cout << "Прізвище: " << surname << endl;
                cout << "Вік: " << age << endl;
                cout << "Стать: " << sex << endl;
                cout << "ID квитка: " << ticketId << endl;
                cout << "Назва концерту: " << concertName << endl;
            }
        }
        inFile.close();
    }
}

void Manager::findUserById(vector<Visitor>& visitors, int id) {
    for (Visitor& visitor : visitors) {
        for (Visitor::Ticket& ticket : visitor.tickets) {
            if (ticket.get_id() == id) {
                cout << "Ім'я: " << visitor.get_name() << endl;
                cout << "Прізвище: " << visitor.get_surname() << endl;
                cout << "Вік: " << visitor.get_age() << endl;
                cout << "Стать: " << visitor.get_sex() << endl;
                cout << "ID квитка: " << ticket.get_id() << endl;
                cout << "Назва концерту: " << ticket.get_concert()->get_concertName() << endl;
            }
        }
    } 
}

void Manager::removeVisitorById(vector<Visitor>& visitors, int id) {
    for (int i = 0; i < visitors.size(); i++) {
        for (Visitor::Ticket& ticket : visitors[i].tickets) {
            if (ticket.get_id() == id) {
                visitors.erase(visitors.begin() + i);
                cout << "Відвідувач з ID " << id << " був видалений." << endl;
                return;
            }
        }
    }
}

void Manager::removeVisitorByIdinFile(string filename, int id) {
    ifstream inFile(filename);
    string line;
    vector<string> lines;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, surname, sex, concertName;
            int age, ticketId;

            ss >> name >> surname >> age >> sex >> ticketId >> concertName;

            if (ticketId != id) {
                lines.push_back(line);
            }
        }
        inFile.close();
    }

    ofstream outFile(filename);
    for (const string& line : lines) {
        outFile << line << endl;
    }
    outFile.close();
}

void Manager::findUserByIdForSignIn(int id) {
    vector<string> filenames = { "masquarade.txt", "rock.txt", "symphony.txt", "jazz.txt", "opera.txt" };
    for (const string& filename : filenames) {
        ifstream inFile(filename);
        string line;

        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                string name, surname, sex, concertName;
                int age, ticketId;

                ss >> name >> surname >> age >> sex >> ticketId >> concertName;

                if (ticketId == id) {
                    cout << "Вітаємо, " << name << " " << endl;
                    cout << "ID квитка: " << ticketId << endl;
                    cout << "Назва концерту: " << concertName << endl;
                    return;
                }
            }
            inFile.close();
        }
    }
}

