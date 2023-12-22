#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Concert {
public:
    static int totalConcerts; // статичне поле

    Concert() {
        totalConcerts++;
    };
    Concert(string concertName, string location, string date, int maxVisitors, int ticketPrice, bool isSoldOut);

    vector<Concert>concerts;

    void set_concertName(string concertName);
    void set_location(string location);
    void set_location(char* location);
    void set_date(string date);
    void set_maxVisitors(int maxVisitors);
    void set_ticketPrice(int ticketPrice);
    void set_ticketStatus(bool isSoldOut);

    void showConcert(vector<Concert*>& concerts);
    void writeConcert(vector<Concert*>& concerts);

    string get_concertName();
    string get_location();
    string get_date();
    int get_maxVisitors();
    bool get_ticketStatus();
    double get_ticketPrice();

private:
    string concertName;
    string location;
    string date;
    int maxVisitors;
    int ticketPrice;
    bool isSoldOut;
};