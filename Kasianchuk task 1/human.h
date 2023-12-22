#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Human {
protected:
    string name;
    string surname;
    int age;
    string sex;

public:

    Human() {};

    virtual void display() {
        cout << "Ім'я: " << name << ", Прізвище: " << surname << ", Вік: " << age << ", Стать: " << sex << endl;
    }

    void set_name(string name);
    void set_surname(string surname);
    void set_sex(string sex);
    void set_age(int age);

    string get_name();
    string get_surname();
    string get_sex();
    int get_age();

    virtual ~Human() {
    }

};