#include <string>
#include <vector>
#include <iostream>
#include <list>


class Concert;
class Manager;

class Singer : virtual public Human {
public:

    Singer();

    Singer& operator++() {
        fee += 3000;
        return *this;
    }

    Singer& operator--() {
        fee -= 3000;
        return *this;
    }

    Singer& operator+=(int amount) {
        fee += amount;
        return *this;
    }

    Singer& operator*=(int factor) {
        fee *= factor;
        return *this;
    }

    Singer& operator/=(int factor) {
        fee /= factor;
        return *this;
    }

    list<pair<int, Concert*>> chosenConcerts;

    int get_fee();
    void set_fee(int new_fee);

    void receiveConcertInfo(vector<Concert*>concerts);
    void receiveConcertInfoInFile(string filename);

    void removeConcertFromList(Concert* concert);
    void displayAndEditSchedule();
    void showShortConcertInfo(vector<Concert*>concerts);

    void chooseConcerts(vector<Concert*>& concerts);

    void display() override {
        cout << "Співак: " << name << ", Прізвище: " << surname << ", Вік: " << age << ", Стать: " << sex << endl << endl;
    }

    ~Singer() override {}

private:
    int fee;
};