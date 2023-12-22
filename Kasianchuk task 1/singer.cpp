#include "human.h"
#include "singer.h"
#include "concert.h"
#include "manager.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <map>

using namespace std;

//Singer

Singer::Singer() {
    this->name = "Тіль";
    this->surname = "Ліндеман";
    this->sex = "Чоловік";
    this->age = 58;
}

int Singer::get_fee() {
    return fee;
}

void Singer::set_fee(int new_fee) {
    fee = new_fee;
}

void Singer::chooseConcerts(vector<Concert*>& concerts) {
    map<string, int> dayOfWeekMap = {
        {"Понеділок", 1},
        {"Вівторок", 2},
        {"Середа", 3},
        {"Четвер", 4},
        {"П'ятниця", 5},
        {"Субота", 6},
        {"Неділя", 7}
    };

    cout << "Виберіть концерти, на яких ви хочете виступити:" << endl;
    for (int i = 0; i < concerts.size(); i++) {
        cout << i + 1 << ". " << concerts[i]->get_concertName() << endl;
    }

    int choice;
    ofstream outFile("singerSchedule.txt", ios::trunc);
    do {
        std::list<int> li;
        cout << "Виберіть концерт або введіть 0, щоб завершити вибір." << endl;
        cin >> choice;

        if (choice == 0) {
            continue;
        }

        // Запитуємо день і час
        string day, time;
        cout << "Введіть день для цього концерту: ";
        cin >> day;
        cout << "Введіть час для цього концерту: ";
        cin >> time;

        // Спочатку вставляємо концерти в список
        chosenConcerts.push_back({ dayOfWeekMap[day], concerts[choice - 1] });

        // Потім сортуємо список за днем тижня
        chosenConcerts.sort();
    
        for (int nCount = 0; nCount < 5; ++nCount)
            li.push_back(nCount);

        std::list<int>::iterator it; 
        it = min_element(li.begin(), li.end());
        std::cout << *it << ' ';
        it = max_element(li.begin(), li.end());
        std::cout << *it << ' ';

        for (int nCount = 0; nCount < 5; ++nCount)
            li.push_back(nCount);

        it = find(li.begin(), li.end(), 2);
        li.insert(it, 7); 

        for (it = li.begin(); it != li.end(); ++it) 
            std::cout << *it << ' ';

        std::cout << endl;

        cout << "Ви вибрали: " << concerts[choice - 1]->get_concertName() << endl;

      

        // Записуємо інформацію про вибраний концерт у файл
        outFile << "День: " << day << " -- Час: " << time << " -- Максимальна кількість відвідувачів: " << concerts[choice - 1]->get_maxVisitors() << endl;
        outFile << concerts[choice - 1]->get_concertName() << endl;

    } while (choice != 0);

    outFile.close();
}

void Singer::displayAndEditSchedule() {
    ifstream inFile("singerSchedule.txt");
    string line;
    int concertNumber;

    if (!inFile) {
        cout << "Не вдалося відкрити файл розкладу." << endl;
        return;
    }

    list<string> schedule;
   
    while (getline(inFile, line)) {
        cout << line << endl;
        schedule.push_back(line);
    }
    inFile.close();

    // Виводимо розклад
    for (const auto& concert : chosenConcerts) {
        cout << "День: " << concert.first << ", Концерт: " << concert.second->get_concertName() << endl;
    }



    cout << "Введіть номер концерту, який ви хочете редагувати, або 0, щоб завершити редагування." << endl;
    cin >> concertNumber;
    if (concertNumber == 0)
    {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
    while (concertNumber != 0) {
        string day, time;
        cout << "Введіть новий день для концерту " << concertNumber << ": ";
        cin >> day;
        cout << "Введіть новий час для концерту " << concertNumber << ": ";
        cin >> time;

        // Знаходимо відповідний рядок у списку і змінюємо його
        auto it = next(schedule.begin(), (concertNumber - 1) * 2);
        *it = "День: " + day + " -- Час: " + time + " -- Максимальна кількість відвідувачів: " + next(it, 1)->substr(next(it, 1)->rfind(' ') + 1);

        cout << "Введіть номер концерту, який ви хочете редагувати, або 0, щоб завершити редагування." << endl;
        cin >> concertNumber;
    }
    if (concertNumber == 0)
    {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }

    // Записуємо список назад у файл
    ofstream outFile("singerSchedule.txt", ios::trunc);
    for (const auto& line : schedule) {
        outFile << line << endl;
    }
    outFile.close();
}



void Singer::removeConcertFromList(Concert* concert) {
    for (auto it = chosenConcerts.begin(); it != chosenConcerts.end(); ++it) {
        if (it->second == concert) {
            chosenConcerts.erase(it);
            cout << "Концерт " << concert->get_concertName() << " видалено зі списку." << endl;
            return;
        }
    }
    cout << "Концерт " << concert->get_concertName() << " не знайдено в списку." << endl;
}

void Singer::receiveConcertInfo(vector<Concert*>concerts) {
   
    ifstream file("concert.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string concertName, location, date;

        if (line.find("Назва концерту:") != string::npos) {
            concertName = line.substr(line.find(":") + 2);
        }
        else if (line.find("Дата:") != string::npos) {
            date = line.substr(line.find(":") + 2);
        }
        else if (line.find("Локація:") != string::npos) {
            location = line.substr(line.find(":") + 2);
        }
    }
}


void Singer::showShortConcertInfo(vector<Concert*>concerts) {
    
    ifstream file("concert.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string concertName, location, date;

        if (line.find("Назва концерту:") != string::npos) {
            concertName = line.substr(line.find(":") + 2);
            cout << concertName << endl;
        }
        else if (line.find("Дата:") != string::npos) {
            date = line.substr(line.find(":") + 2);
            cout << date << endl;
        }
        else if (line.find("Локація:") != string::npos) {
            location = line.substr(line.find(":") + 2);
            cout << location << endl;
        }
    }

   /* for (int i = 0; i < concerts.size(); i++)
    {
        cout << concerts[i]->get_concertName() << endl;
        cout << concerts[i]->get_date() << endl;
        cout << concerts[i]->get_location() << endl;

    }*/
}

