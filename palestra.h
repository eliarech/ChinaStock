#ifndef PALESTRA_H
#define PALESTRA_H
#include "cliente.h"

class palestra : virtual public cliente
{
private:
    bool scheda; //se fa la scheda oppure no;
    string nomeistruttorepalestra; //nome istruttore;
    QDate scadenzapalestra;
public:
    palestra(string="",string="", int=0,int=0,int=0,string="",string="", string="",string="",unsigned int = 0,string="",string="",bool=false,bool=false,string="",int=0,int=0,int=0);
    //palestra(const palestra& p);
    palestra(cliente,bool=false,string="",int=1,int=1,int=2000);
    palestra* clone() const;
    //virtual ~palestra();
    //virtual bool operator==(const cliente& c) const; //override?
    //virtual bool operator!=(const cliente& c) const; //override?


    int getGiornoPalestra() const;
    int getMesePalestra() const;
    int getAnnoPalestra() const;
    bool isscheda() const;
    string getnomeistruttorepalestra() const;

};

#endif // PALESTRA_H
