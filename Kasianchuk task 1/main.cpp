#include "human.h"
#include "visitor.h"
#include "manager.h"
#include "concert.h"
#include "singer.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>

#include <functional>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

void Service(Visitor& visitor) {
    visitor.showVisitors();
}

int main() {

    Visitor visitor;
    Manager manager;
    Singer singer;
    Concert concert;

    vector<Visitor>visitors;
    vector<Concert*>concerts;

    Human* p, b;
    Human* unicycle;

    p = &manager;
    p->display();
    p = &singer;
    p->display();

    unicycle = new Manager;
    unicycle->display();
    delete unicycle;

    unicycle = new Singer;
    unicycle->display();
    delete unicycle;

    Human human;
    Human* g = &human;

    g = (Human*)&singer;
    g->display();

    g = (Human*)&manager;
    g->display();

    vector<int> vect;
    vect.push_back(4);
    vect.push_back(8);
    vect.push_back(-3);
    vect.push_back(3);
    vect.push_back(-8);
    vect.push_back(12);
    vect.push_back(5);

    std::vector<int>::const_iterator it; 
    for (it = vect.begin(); it != vect.end(); ++it) 
        std::cout << *it << ' ';

    std::cout << '\n';

    std::reverse(vect.begin(), vect.end()); 

    for (it = vect.begin(); it != vect.end(); ++it) 
        std::cout << *it << ' ';


    Service(visitor);

    static int fee[6] = { 2500, 2000, 1500, 4000, 3500, 3000 };

    list<int> pricesList(fee, fee + sizeof(fee) / sizeof(fee[0]));

    plus<int> addition;
    addition(fee[3], fee[5]);

    multiplies<int> multiplication;
    multiplication(fee[1], 2);

    divides<int> division;
    division(fee[1], 2);

    greater<int> greater_than;
    greater_than(fee[2], fee[5]);

    less<int> less_than;
    less_than(fee[5], fee[6]);

    logical_and<bool> logical_and_Object;
    bool all_greater_than_2000 = true;
    for (int i = 0; i < 6; i++) {
        all_greater_than_2000 = logical_and_Object(all_greater_than_2000, fee[i] > 2000);
    }

    logical_or<bool> logical_or_Object;
    bool any_less_than_2000 = false;
    for (int i = 0; i < 6; i++) {
        any_less_than_2000 = logical_or_Object(any_less_than_2000, fee[i] < 2000);
    }

    logical_not<bool> logical_not_Object;
    bool not_all_greater_than_2000 = logical_not_Object(all_greater_than_2000);

    manager.loadConcerts(concerts);

    string checker;
    string continueProgram;

    do {

        cout << "Відвідувач / Менеджер / Співак" << endl;
        cin >> checker;

        if (checker == "Відвідувач")
        {
            cout << "Переглянути інформацію про концерти / Реєстрація / Увійти " << endl;
            cin >> checker;

            manager.loadVisitors(visitors, concerts);

            if (checker == "Переглянути")
            {
                concert.showConcert(concerts);
            }
            else if (checker == "Реєстрація")
            {
                visitor.registrationProcess(visitors, concerts);
            }
            else if (checker == "Увійти")
            {

                int id; 
                cout << "Введіть ваш ID для входу: ";
                cin >> id;

                if (visitor.doesVisitorExist(visitors, id) || visitor.doesVisitorExistInFile(id)){
                    cout << "Користувача з ID " << id << " знайдено. " << endl;
                    manager.findUserByIdForSignIn(id);
                }
                else
                {
                    cout << "Користувача з ID " << id << " не знайдено. " << endl;
                    break;
                }

            }
        }
        else if (checker == "Менеджер")
        {
            cout << "Концерти / Відвідувачі / Співак" << endl;
            cin >> checker;
            if (checker == "Концерти")
            {

                string location;
                string date;


                for (int i = 0; i < concerts.size(); i++)
                {
                    cout << "Введіть локацію концерту" << endl;
                    cin >> location;
                    cout << "Введіть дату концерту" << endl;
                    cin >> date;

                    int ticketPrice;
                    cout << "Введіть ціну на концерт" << endl;
                    cin >> ticketPrice;

                    manager.addConcerts(concerts, location, date, ticketPrice, i);

                }

                concert.writeConcert(concerts);
                manager.informSingerAboutConcert(singer, concerts);
            }
            if (checker == "Відвідувачі") 
            {
                cout << "Показати / ID" << endl;
                cin >> checker;
                if (checker == "Показати")
                {
                    visitor.showVisitors();
                }
            
            else if (checker == "ID")
            {
                cout << "Шукати / Видалити" << endl;
                cin >> checker;

                if (checker == "Шукати")
                {
                    int number;
                    cout << "Введіть ID відвідувача: " << endl;
                    cin >> number;

                    manager.findUserById(visitors, number);

                    manager.findUserByIdInFiles("masquarade.txt", number);
                    manager.findUserByIdInFiles("rock.txt", number);
                    manager.findUserByIdInFiles("symphony.txt", number);
                    manager.findUserByIdInFiles("jazz.txt", number);
                    manager.findUserByIdInFiles("opera.txt", number);

                }
                if (checker == "Видалити")
                {
                    int number;
                    cout << "Введіть ID відвідувача: " << endl;
                    cin >> number;

                    manager.removeVisitorById(visitors, number);

                    manager.removeVisitorByIdinFile("masquarade.txt", number);
                    manager.removeVisitorByIdinFile("rock.txt", number);
                    manager.removeVisitorByIdinFile("symphony.txt", number);
                    manager.removeVisitorByIdinFile("jazz.txt", number);
                    manager.removeVisitorByIdinFile("opera.txt", number);
                }
            }
            }
            if (checker == "Співак") {
                manager.receiveInfoAboutPickedConcerts(concert);
            }
        }
       
        else if (checker == "Співак")
        {
            singer.set_fee(15350);
            for (int i = 0; i < concerts.size(); i++)
            {
                ++singer;
            }
           
            cout << "Гонорар за " << concerts.size() << " концертів " << singer.get_fee() << " гривень" << endl;

            cout << "Редактувати графік / Збільшити гонорар / Зменшити гонорар / Пропустити" << endl;
            cin >> checker;

            if (checker == "Редактувати")
            {
                singer.displayAndEditSchedule();
            }
            if (checker == "Збільшити")
            {
                cout << "Введіть в скільки раз збільшити гонорар" << endl;
                int x;
                cin >> x;
                singer = singer *= x;
                cout << "Гонорар за " << concerts.size() << " концертів " << singer.get_fee() << " гривень" << endl;
            }
            if (checker == "Зменшити")
            {
                cout << "Введіть в скільки раз зменшити гонорар" << endl;
                int x;
                cin >> x;
                singer = singer /= x;
                cout << "Гонорар за " << concerts.size() << " концертів " << singer.get_fee() << " гривень" << endl;
            }
            
            cout << "Отримати інформацію про концерти" << endl;
            cin >> checker;
            if (checker == "Отримати")
            {
                ifstream file("concert.txt");
                singer.receiveConcertInfo(concerts);
                if (concerts.empty() || !file.good()) 
                {
                    cout << "Наразі немає жодного концерту." << endl;
                    break;
                }
                else {
                    singer.showShortConcertInfo(concerts);
                    cout << "Вибрати концерти" << endl;
                    cin >> checker;
                    if (checker == "Вибрати")
                    {
                        singer.chooseConcerts(concerts);
                    }
                }
            }

           
        }

            cout << "Продовжити? (так/ні)" << endl;
            cin >> continueProgram;
} while (continueProgram == "так");

return 0;
}
