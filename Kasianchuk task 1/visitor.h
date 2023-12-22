#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Human;
class Concert;

class Visitor : virtual public Human {
public:
   
    class Ticket {
    public:
        Ticket();
        Ticket(int id, Concert* concert) : id(id), concert(concert) {}
        int get_id() const {
            return id;
        }
        Concert* get_concert() {
            return concert;
        }
    protected:
        int id;
    private:
        Concert* concert;
    };

    vector<Visitor>& getVisitors() {
        return visitors;
    }

    Visitor();
    Visitor(string name, string surname, string sex, int age, int ticket_id, Concert* concert);

    void registrationProcess(vector<Visitor>& visitors, vector<Concert*>& concerts);
    void showVisitors();

    vector<Ticket> tickets;
    vector<Visitor> visitors;

    void add_ticket(int id, Concert* concert) {
        tickets.push_back(Ticket(id, concert));
    };

    bool doesVisitorExistInFile(int id);

    template <typename T>
    bool doesVisitorExist(vector<T>& visitors, int id) {
        for (T& visitor : visitors) {
            for (Ticket& ticket : visitor.tickets) {
                if (ticket.get_id() == id) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    int moneyBalance;
    bool ticket;
};