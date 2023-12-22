#include "human.h"
#include "visitor.h"
#include "manager.h"
#include "concert.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>



using namespace std;

// Visitors

Visitor::Visitor() {
    this->name = "Паша";
    this->surname = "Конашевич";
    this->sex = "Чоловік";
    this->age = 12;
}

Visitor::Visitor(string name, string surname, string sex, int age, int ticket_id, Concert* concert) {
    this->name = name;
    this->surname = surname;
    this->sex = sex;
    this->age = age;
    tickets.push_back(Ticket(ticket_id, concert));
}

void readFromFile(const string& filename) {
    ifstream readFile(filename);
    string line;
    while (getline(readFile, line)) {
        cout << filename << " " << line << endl;
    }
    if (filename.empty())
    {
        cout << filename << " " << "Немає даних" << endl;
    }
    readFile.close();
}

void Visitor::showVisitors() {
    readFromFile("masquarade.txt");
    readFromFile("rock.txt");
    readFromFile("opera.txt");
    readFromFile("jazz.txt");
    readFromFile("symphony.txt");

}

bool Visitor::doesVisitorExistInFile(int id) {
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
                    return true;
                }
            }
            inFile.close();
        }
    }

    return false;
}

void Visitor::registrationProcess(vector<Visitor>& visitors, vector<Concert*>& concerts) {
    Manager manager;

    string name;
    cout << "Введіть ваше ім'я: " << endl;
    cin >> name;

    string surname;
    cout << "Введіть ваше прізвище: " << endl;
    cin >> surname;

    string sex;
    cout << "Введіть вашу стать: " << endl;
    cin >> sex;

    int age;
    cout << "Введіть ваш вік: " << endl;
    cin >> age;

    for (int i = 0; i < concerts.size(); i++) {
        Concert* concert = concerts[i];
        string concertName = concert->get_concertName();
        cout << i + 1 << ". " << concertName << " " << endl;
    }

    cout << "Введіть номер концерту, який ви хочете вибрати: " << endl;
    int concertNumber;
    cin >> concertNumber;

    Concert* chosenConcert = concerts[concertNumber - 1];

    srand(time(0));
    int ticket_id = rand() % 200;

    if (ticket_id < 0) {
        throw std::invalid_argument("ID квитка не може бути від'ємним");
    }

    Visitor visitor(name, surname, sex, age, ticket_id, chosenConcert);

    visitors.push_back(visitor);

    string filename;
    switch (concertNumber)
    {
    case 1:
        filename = "masquarade.txt";
        break;
    case 2:
        filename = "rock.txt";
        break;
    case 3:
        filename = "opera.txt";
        break;
    case 4:
        filename = "jazz.txt";
        break;
    case 5:
        filename = "symphony.txt";
        break;
    default:
        break;
    }

    try {
        if (chosenConcert->get_ticketStatus() == 0)
        {
            throw runtime_error("Вибачте, але всі квитки на цей концерт вже розкуплено.");
        }
        else {

            ofstream writeFile;
            writeFile.open(filename, ios::app);

            for (int i = 0; i < visitors.size(); i++)
            {
                writeFile << visitors[i].get_name() << " ";
                writeFile << visitors[i].get_surname() << " ";
                writeFile << visitors[i].get_age() << " ";
                writeFile << visitors[i].get_sex() << " ";
                if (!visitors[i].tickets.empty()) {
                    writeFile << visitors[i].tickets[0].get_id() << " " << visitors[i].tickets[0].get_concert()->get_concertName() << " " << endl;
                    cout << "Вітаємо! Ви зареєструвались на : " << visitors[i].tickets[0].get_concert()->get_concertName() << endl;
                    cout << "Ваш ID: " << visitors[i].tickets[0].get_id() << endl;
                }
            }
            writeFile.close();
        }
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
        exit(0);
    }

}