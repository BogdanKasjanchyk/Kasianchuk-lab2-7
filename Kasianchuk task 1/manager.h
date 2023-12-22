#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Concert;
class Human;
class Visitor;
class Singer;

class Manager : virtual public Human {
private:
  
public:
    Manager();

    Concert* concert;
    vector<Concert*>concerts;

    void display() override {
        cout << "Менеджер: " << name << ", Прізвище: " << surname << ", Вік: " << age << ", Стать: " << sex << endl;
    }

    void loadVisitors(vector<Visitor>& visitors, vector<Concert*>& concerts);
    void addConcerts(vector<Concert*>& concerts, string location, string date, int ticketPrice , int i);
    void loadConcerts(vector<Concert*>& concerts);

    void informSingerAboutConcert(Singer& singer, vector<Concert*>concerts);
    void receiveInfoAboutPickedConcerts(Concert &concert);

    void findUserByIdInFiles(string filename, int id);
    void findUserById(vector<Visitor>& visitors, int id);
    void findUserByIdForSignIn(int id);

    void removeVisitorById(vector<Visitor>& visitors, int id);
    void removeVisitorByIdinFile(string filename, int id);

    virtual ~Manager() override {}
};