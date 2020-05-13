#ifndef CLIENTE_H
#define CLIENTE_H
#include<string>
#include<QDate>
using std::string;
class cliente{
private:
    string nome;
    string cognome;
    QDate dataNascita;
    string codicefiscale;
    string luogodN;
    string residenza;
    string via;
    string numvia;
    string  numerotel;
    string mail;
    bool student;
public:
    cliente(string="",string="", int=2000, int=1, int=1,string="",string="", string="",string="",string="",string="",string="",bool=false);
    virtual ~cliente() = default;

    virtual cliente* clone() const; //DA CONTROLLARE!!

    virtual bool operator<(const cliente&) const; //capire se è giusto virtual
    virtual bool operator>(const cliente&) const;
    virtual bool operator==(const cliente&) const;

    string getnome() const; //forse bisognerà passare per riferimento costante le stringhe ritornate per non fare la copia, quindi const string& come ritorno
    string getcognome() const;
    QDate getDataN() const;
    int getGiornoN() const;
    int getMeseN() const;
    int getAnnoN() const;
    string getcodfiscale() const;
    string getluogo() const;
    string getres() const;
    string getvia() const;
    string getnum() const;
    string getnumerotel() const;
    string getmail() const;
    bool getstudent() const;
};

#endif
