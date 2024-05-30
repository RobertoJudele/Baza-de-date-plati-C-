#include <iostream>
#include <unordered_map>
using namespace std;
class cashPayment{
protected:
    string date;
    double amount;
public:
    cashPayment(){
        date = "";
        amount = 0;
    }
    cashPayment(string date, double amount){
        this->date = date;
        this->amount = amount;
    }
    void setAmount(double amount){
        this->amount = amount;
    }
    string getDate(){
        return date;
    }
    double getAmount(){
        return amount;
    }
    void paymentDetails(){
        cout << "Date: " << date << endl;
        cout << "Amount: " << amount << endl;
    }
};
class cecPayment : public cashPayment{
protected:
    string cecNumber;
public:
    cecPayment() : cashPayment(){
        cecNumber = "";
    }
    cecPayment(string date, double amount, string checkNumber) : cashPayment(date, amount){
        this->cecNumber = checkNumber;
    }
    void setCheckNumber(string checkNumber){
        this->cecNumber = checkNumber;
    }
    string getCheckNumber(){
        return cecNumber;
    }
    void paymentDetails(){
        cout << "Date: " << date << endl;
        cout << "Amount: " << amount << endl;
        cout << "Check Number: " << cecNumber << endl;
    }
};

template <typename T>
class Gestiune {
protected:
    unordered_map<int, T*> payments;

public:
    int getTotalPayments() const {
        return payments.size();
    }
    Gestiune& operator+=(T& payment) {
        int id = payments.size();
        payments[id] = &payment;
        return *this;
    }
    void displayAllPayments() const {
        for (const auto& payment : payments) {
            cout << "ID: " << payment.first << endl;
            payment.second->paymentDetails();
            cout << endl;
        }
    }
};

class Client {
protected:
    string name;
    string cardNumber;
public:
    Client(string name, string cardNumber)
            : name(name), cardNumber(cardNumber) {}
};

class cardPayment : public cashPayment {
protected:
    Client client;
public:
    cardPayment() : cashPayment(), client("", "") {}
    cardPayment(string date, double amount, Client client)
            : cashPayment(date, amount), client(client) {}

    Client getClient() const {
        return client;
    }
};
class meniuGestiune{
    Gestiune<cashPayment> cashPayments;
    Gestiune<cecPayment> cecPayments;
    Gestiune<cardPayment> cardPayments;
public:
    static const string ADD;
    static const std::string REMOVE;
    static const std::string DISPLAY_ALL;
    static const std::string TOTAL;
    static const std::string STOP;
    static const string COPY;
    static void DisplayMenuMessage(){
        cout<<ADD<<" - citeste si adauga un nou client"<<endl;
        cout<<REMOVE<<" - sterge client"<<endl;
        cout<<DISPLAY_ALL<<" - afiseaza toti clientii"<<endl;
        cout<<TOTAL<<" - afiseaza numarul total de clienti"<<endl;
        cout<<STOP<<" - opreste programul"<<endl;
    };
    void RunMenu() {
        DisplayMenuMessage();
        string command;
        while (command != STOP) {
            cin>>command;
            if (command == ADD) {
                cout<<"Ce tip de client doriti sa adaugati?"<<endl;
                string client_tip;
                cin>>client_tip;
                cout<<"Introduceti datele clientului"<<endl;
                if(client_tip=="cash"){
                    cashPayment* cashPayment1 = new cashPayment;
                    double suma;
                    cout<<"Introduceti suma"<<endl;
                    cin>>suma;
                    cashPayment1->setAmount(suma);
                    string data;
                    cout<<"Introduceti data"<<endl;
                    cin>>data;
                    cashPayment1->paymentDetails();
                    cashPayments+=*cashPayment1;
                }
                else if(client_tip=="cec") {
                    cecPayment* cecPayment1 = new cecPayment;
                    double suma;
                    cout<<"Introduceti suma"<<endl;
                    cin>>suma;
                    cecPayment1->setAmount(suma);
                    string data;
                    cout<<"Introduceti data"<<endl;
                    cin>>data;
                    string cec;
                    cout<<"Introduceti numarul de cec"<<endl;
                    cin>>cec;
                    cecPayment1->setCheckNumber(cec);
                    cecPayment1->paymentDetails();
                    cecPayments+=*cecPayment1;
                }
                else if(client_tip=="card") {
                    cardPayment* cardPayment1 = new cardPayment;
                    double suma;
                    cout<<"Introduceti suma"<<endl;
                    cin>>suma;
                    cardPayment1->setAmount(suma);
                    string data;
                    cout<<"Introduceti data"<<endl;
                    cin>>data;
                    string nume;
                    cout<<"Introduceti numele clientului"<<endl;
                    cin>>nume;
                    string card;
                    cout<<"Introduceti numarul de card"<<endl;
                    cin>>card;
                    Client* client1 = new Client(nume, card);
                    cardPayment1->paymentDetails();
                    cardPayments+=*cardPayment1;
                }
                else{
                    cout<<"Tip de client invalid"<<endl;
                }
            } else if (command == DISPLAY_ALL) {
                cashPayments.displayAllPayments();
                cecPayments.displayAllPayments();
                cardPayments.displayAllPayments();
            } else if (command == TOTAL) {
                cout << "Total payments: " << cashPayments.getTotalPayments() + cecPayments.getTotalPayments() + cardPayments.getTotalPayments() << endl;
            } else if (command == STOP) {
                cout << "Program stopped" << endl;
            }else {
                cout << "Comanda invalida" << endl;
            }
        }
    }
    meniuGestiune();
    ~meniuGestiune();
};
meniuGestiune::meniuGestiune() = default;
meniuGestiune::~meniuGestiune() {
    // Cleanup code here
}
const string meniuGestiune::ADD = "ADD";
const string meniuGestiune::REMOVE = "REMOVE";
const string meniuGestiune::DISPLAY_ALL = "DISPLAY_ALL";
const string meniuGestiune::TOTAL = "TOTAL";
const string meniuGestiune::STOP = "STOP";
int main() {

//    Gestiune<cashPayment> cashPayments;
//    cashPayment* cashPayment1 = new cashPayment("01.01.2021", 100);
//    cashPayment* cashPayment2 = new cashPayment("02.01.2021", 200);
//    cashPayments += *cashPayment1;
//    cashPayments += *cashPayment2;
//    cashPayments.displayAllPayments();
//    cout<<cashPayments.getTotalPayments();
//
//    Gestiune<cecPayment> cecPayments;
//    cecPayment* cecPayment1 = new cecPayment("03.01.2021", 300, "123");
//    cecPayment* cecPayment2 = new cecPayment("04.01.2021", 400, "456");
//    cecPayments += *cecPayment1;
//    cecPayments += *cecPayment2;
//    cecPayments.displayAllPayments();
//    cout<<cecPayments.getTotalPayments();
//
//
//    Gestiune<cardPayment> cardPayments;
//    Client* client1 = new Client("John", "1234");
//    Client* client2 = new Client("Doe", "5678");
//    cardPayment* cardPayment1 = new cardPayment("05.01.2021", 500, *client1);
//    cardPayment* cardPayment2 = new cardPayment("06.01.2021", 600, *client2);
//    cardPayments += *cardPayment1;
//    cardPayments += *cardPayment2;
//    cardPayments.displayAllPayments();
//    cout<<cardPayments.getTotalPayments();
//
//    cout << "Total cash payments: " << cashPayments.getTotalPayments() << endl;
//    cout << "Total cec payments: " << cecPayments.getTotalPayments() << endl;
//    cout << "Total card payments: " << cardPayments.getTotalPayments() << endl;
    meniuGestiune meniu;
    meniu.RunMenu();
    return 0;
}