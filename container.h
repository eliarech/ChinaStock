#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include<QStringList>
#include<iostream>
#include<deeppointer.h>
using std::string;
using std::cout;

template <class T>
class Container {
    //friend class Iteratore;
    friend class model;
private:
    class nodo {
        friend class Container<T>; // DA VEDERE!!!
    private:
        T info;
        nodo* next;
        nodo(const T&, nodo* = nullptr);
        nodo(const nodo&);
        void distruggi();
    };
    nodo* primo, *ultimo;
    static nodo* clone(nodo*, nodo*&);
    nodo* rimuovi(nodo*, const T&);
    nodo* rimuovi_s(nodo*, string);
    //nodo *copia(const nodo*);
    //nodo *lastNode(const nodo*);
public:
    Container();
    Container(const T&);
    Container(const Container&);
    ~Container();
    Container& operator=(const Container&);
    //bool operator==(const Container<T>&) const;   ci serve davvero?
    //bool operator!=(const Container<T>&) const;

//    void aggiungiDavanti(const T&);
//    void aggiungiDietro(const T&);
    void aggInOrdine(const T&);
    void rimpiazzaFinale(unsigned int, const T&);
    //T prendiNodoIndice(unsigned int) const;
    void rimuoviIndice(const unsigned int);
    T prendiNodoIndice(const unsigned int) const;
    unsigned int trovaIndiceNodo(const T&); //forse bisogna passare const come return? Però mi segna warning
    void clear();
    bool isEmpty() const;


    class constIteratore
    {
        friend class Container<T>;
    private:
        const nodo* puntatore;
        constIteratore(nodo*);
    public:
        constIteratore();
        constIteratore& operator=(const constIteratore&);
        constIteratore& operator++();
        constIteratore& operator++(int);
        const T& operator*() const;
        const T* operator->() const;
        bool operator==(const constIteratore&);
        bool operator!=(const constIteratore&);
    };


    class Iteratore{
        friend Container<T>;
    private:
        nodo * puntatore;
        Iteratore(nodo *);
    public:
        Iteratore();
        Iteratore& operator=(const Iteratore&);
        Iteratore &operator++();
        Iteratore &operator++(int);
        T &operator*() const;
        T *operator->() const;
        bool operator==(const Iteratore &);
        bool operator!=(const Iteratore &);

    };
    constIteratore inizio() const;
    constIteratore fine() const;
    T& davanti() const;
    T& dietro() const;
    Iteratore inizio();
    Iteratore fine();
    void rimuovi(const T&);
    void rimuovi_s(string); //DA RIVEDERE!!!
    Iteratore cerca(const T&);
    Iteratore cerca_s(string); // DA RIVEDERE!!!
    constIteratore cerca(const T&) const;
    constIteratore cerca_s(string) const; //DA RIVEDERE!!!
};

//-------------------------------------IMPLEMENTAZIOONE METODI--------------------------
template <class T>
Container<T>::nodo::nodo(const T& obj, nodo* n) : info(obj), next(n) {}

template <class T>
Container<T>::nodo::nodo(const nodo& n):info(n.info), next(n.next){}

template<class T>
void Container<T>::nodo::distruggi()
{
    if (next) next->distruggi();
    delete this;
}

template<class T>
typename Container<T>::nodo* Container<T>::clone(nodo * pri, nodo *& ult)
{
    if (pri == nullptr)
    {
        ult = nullptr;
        return nullptr;
    }
    nodo* p = new nodo(pri->info, clone(pri->next, ult));
    if(pri->next == nullptr) ult = p;
    return p;
}

template<class T>
void Container<T>::rimuovi(const T & obj)
{
    rimuovi(primo, obj);
}

template<class T>
void Container<T>::rimuovi_s(string s)
{
    rimuovi_s(primo, s);
}

template<class T>
Container<T>::Container() : primo(nullptr), ultimo(nullptr) {}

template <class T>
Container<T>::Container(const T& obj): primo(new nodo(obj)){ ultimo=primo;}

template<class T>
Container<T>::Container(const Container & q) : primo(clone(q.primo, ultimo)) {}

template<class T>
Container<T>::~Container()
{
    if (primo) primo->distruggi();
}

template<class T>
Container<T>& Container<T>::operator=(const Container & q)
{
    if (this != &q)
    {
        if(primo) delete primo;
        primo = clone(q.primo, ultimo);
    }
    return *this;
}

//template <class T> capire se serve implementare
//bool Container<T>::operator==(const Container<T>& c) const{
//    return equal(primo, c.primo);
//}


//template<class T>
//void Container<T>::aggiungiDavanti(const T & obj)
//{
//    nodo* new_nodo = new nodo(obj);
//    if (primo == nullptr) {
//        primo = ultimo = new_nodo;
//    }
//    else
//    {
//        new_nodo->next = primo;
//        primo = new_nodo;
//    }
//}

//template<class T>
//void Container<T>::aggiungiDietro(const T & obj)
//{
//    if (primo == nullptr) primo = ultimo = new nodo(obj);
//    else
//    {
//        ultimo->next = new nodo(obj);
//        ultimo = ultimo->next;
//    }
//}



template<class T> //commentato aggiungidavanti e sostituito con aggInOrdine (cambiare nome), capire perchè non funziona overloading deep pointer > e <
void Container<T>::aggInOrdine(const T & obj){
    nodo* cliente = new nodo(obj);
    if (primo == nullptr) primo = ultimo = cliente;
    else if (primo->info > cliente->info) {
        cliente->next = primo;
        primo = cliente;
    }
    else {
        nodo* tmp = primo;
        while (tmp->next && tmp->next->info < cliente->info) tmp = tmp->next;
        cliente->next = tmp->next;
        tmp->next = cliente;
        if (cliente->next == nullptr) ultimo = cliente;
    }
}




template<class T>
void Container<T>::rimpiazzaFinale(unsigned int indice, const T& clienteModificato){
    rimuoviIndice(indice);
    aggInOrdine(clienteModificato);
}

// template <class T> capire se cancellare o tenere!!!
// T Container<T>::prendiNodoIndice(unsigned int i) const{
//     //if(i>= size())
//     //    return nullptr;    DA IMPLEMENTARE PER IL CONTROLLO, SERVE?
//     nodo* contatore = primo;
//     for(unsigned int k=0; k<i; k++)
//         contatore=contatore->next;
//     return contatore->info;
// }



template <class T>
void Container<T>::rimuoviIndice(const unsigned int i){ //da modificare perchè è uguale a gotta, vedere se cambia
    if(isEmpty())
        return;

    if(!primo->next){//coda
        if(i==0){//testa
            delete primo;
            primo=nullptr;
            return;
        }
    }
    else{//piu di un el
        nodo* prec=primo;
        nodo* corr=primo->next;

        if(i==0){//testa
            primo=primo->next;
            prec->next=nullptr;
            delete prec;
            return;
        }

        for(unsigned int x=1; corr->next && x<i; x++){
            prec=prec->next;
            corr=corr->next;
        }

        if(corr){
            prec->next=corr->next;
            corr->next=nullptr;
            delete corr;
            return;
        }
    }

    return;
}

template <class T>
T Container<T>::prendiNodoIndice(const unsigned int i) const{
    if(!primo->next){ //si potrebbe tenere if i==0 sennò cicla, capire se sistemare funzione
        if(i==0){
            return primo->info;
        }
    }
    else{
        nodo* corr=primo->next;

        if(i==0){
            return primo->info;
        }

        for(unsigned int x=1; corr->next && x<i; x++){
            corr=corr->next;
        }

        if(corr){
            return corr->info;
        }
    }
    T temp; //oggetto da ritornare se non trovo nulla
    return temp;
}

template<class T>
unsigned int Container<T>::trovaIndiceNodo(const T& nodoDaTrovare) {
    unsigned int i=0;
    nodo* corr = primo;
    bool trovato = false;
    while (trovato == false && corr->next){
        if (corr->info == nodoDaTrovare) trovato = true;
        else {
            corr = corr->next;
            i=i+1;
        }
    }
    return i;
}

template<class T>
void Container<T>::clear()
{
    if (primo){
        primo->distruggi();
        primo = nullptr;
    }
}

template<class T>
bool Container<T>::isEmpty() const
{
    return (primo==nullptr);
}

template<class T>
Container<T>::constIteratore::constIteratore(nodo * p) : puntatore(p) {}

template<class T>
Container<T>::constIteratore::constIteratore() : puntatore(nullptr) {}

template<class T>
typename Container<T>::constIteratore & Container<T>::constIteratore::operator=(const constIteratore & cit)
{
    puntatore=cit.puntatore;
    return *this;
}

template<class T>
typename Container<T>::constIteratore& Container<T>::constIteratore::operator++()
{
    if(puntatore) puntatore=puntatore->next;
    return *this;

}
template<class T>
typename Container<T>::constIteratore& Container<T>::constIteratore::operator++(int)
{
    Iteratore aux=*this;
    if(puntatore) puntatore=puntatore->next;
    return aux;

}

template<class T>
const T & Container<T>::constIteratore::operator*() const
{
    return puntatore->info;
}

template<class T>
const T * Container<T>::constIteratore::operator->() const
{
    return &(puntatore->info);
}

template<class T>
bool Container<T>::constIteratore::operator==(const constIteratore& cit)
{
    return puntatore == cit.puntatore;
}

template<class T>
bool Container<T>::constIteratore::operator!=(const constIteratore& cit)
{
    return puntatore != cit.puntatore;
}

template<class T>
Container<T>::Iteratore::Iteratore(nodo * p) : puntatore(p) {}

template<class T>
Container<T>::Iteratore::Iteratore() : puntatore(nullptr) {}

template<class T>
typename Container<T>::Iteratore & Container<T>::Iteratore::operator=(const Iteratore & it)
{
    puntatore=it.puntatore;
    return *this;
}

template<class T>
typename Container<T>::Iteratore& Container<T>::Iteratore::operator++()
{
    if(puntatore) puntatore=puntatore->next;
    return *this;

}
template<class T>
typename Container<T>::Iteratore& Container<T>::Iteratore::operator++(int)
{
    Iteratore aux=*this;
    if(puntatore) puntatore=puntatore->next;
    return aux;

}

template<class T>
T & Container<T>::Iteratore::operator*() const
{
    return puntatore->info;
}

template<class T>
T * Container<T>::Iteratore::operator->() const
{
    return &(puntatore->info);
}

template<class T>
bool Container<T>::Iteratore::operator==(const Iteratore& it)
{
    return puntatore == it.puntatore;
}

template<class T>
bool Container<T>::Iteratore::operator!=(const Iteratore& it)
{
    return puntatore != it.puntatore;
}


template<class T>
typename Container<T>::constIteratore Container<T>::inizio() const
{
    return constIteratore(primo);
}

template<class T>
typename Container<T>::constIteratore Container<T>::fine() const
{
    return constIteratore(nullptr);
}

template<class T>
T & Container<T>::davanti() const
{
    return primo->info;
}

template<class T>
T & Container<T>::dietro() const
{
    return ultimo->info;
}

template<class T>
typename Container<T>::Iteratore Container<T>::inizio()
{
    return Iteratore(primo);
}

template<class T>
typename Container<T>::Iteratore Container<T>::fine()
{
    return Iteratore(nullptr);
}

template<class T>
typename Container<T>::nodo* Container<T>::rimuovi(nodo* f, const T & obj)
{
    if (f == nullptr)
        return nullptr;
    f->next = rimuovi(f->next, obj);
    if (f->info == obj)
    {
        nodo* tmp = f->next;
        if (primo == f) primo = tmp;
        if (f == ultimo) ultimo = nullptr;
        delete f;
        return tmp;
    }
    if (ultimo == nullptr) ultimo = f;
    return f;
}

template<class T> //bisogna togliere questa funzione
typename Container<T>::nodo* Container<T>::rimuovi_s(nodo* f, string s)
{
    if (f == nullptr)
        return nullptr;
    f->next = rimuovi_s(f->next, s);
    if (f->info == s)
    {
        nodo* tmp = f->next;
        if (primo == f) primo = tmp;
        if (f == ultimo) ultimo = nullptr;
        delete f;
        return tmp;
    }
    if (ultimo == nullptr)
        ultimo = f;
    return f;
}

template<class T>
typename Container<T>::Iteratore Container<T>::cerca(const T & obj) // ritorna Iteratore alla prima occorrenza del match
{
    Iteratore it = primo;
    while (it != fine())
    {
        if (obj == *it)
        {
            return it;
        }
        it++;
    }
    return Iteratore();
}

template<class T>
typename Container<T>::Iteratore Container<T>::cerca_s(string s)
{
    Iteratore it = primo;
    while (it != fine())
    {
        if (*it == s)
        {
            return it;
        }
        it++;
    }
    return Iteratore();
}

template<class T>
typename Container<T>::constIteratore Container<T>::cerca(const T & obj) const // ritorna const_iterator alla prima occorrenza del match
{
    constIteratore cit = primo;
    while (cit != fine())
    {
        if (obj == *cit)
        {
            return cit;
        }
        cit++;
    }
    return constIteratore();
}

template<class T>
typename Container<T>::constIteratore Container<T>::cerca_s(string s) const
{
    constIteratore cit = primo;
    while (cit != fine())
    {
        if (*cit == s)
        {
            return cit;
        }
        cit++;
    }
    return constIteratore();
}

#endif // CONTAINER_H
