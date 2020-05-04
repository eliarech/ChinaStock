#ifndef GUI_H
#define GUI_H
#include <QWidget>
#include<QGridLayout>
#include<QMenuBar>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QCheckBox>
#include<QGroupBox>
#include<QHBoxLayout>
#include<QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QDate>
#include <QGroupBox>
#include <QPushButton>
#include <QFile>
#include<QMessageBox>
#include "viewlistaclienti.h"
#include"deeppointer.h"
#include"cliente.h"
#include"piscina.h"
#include"palestra.h"
#include"vip.h"

#include<iostream>
using std::cout;
using std::endl;

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent =nullptr);
    //~mainwindow();
    void mostraClienti(const QStringList); //era displayCatalog
    const QString getParolaCercata() const; //era getResearchWord
    void nessunSelezionato();
    void visualizzaDettagliCliente(deepPointer<cliente>);
    void resetDettCliente();

    bool isSelected() const;
    unsigned int getIndexSelected() const;

public slots:
    void richiestaRimoz();
    void showInfoCliente();
private:
    //controllare quali non si usano!!!!
    QVBoxLayout* mainLayout;
    QGridLayout* gridLayout;
    QVBoxLayout* verticalDxLayout, *verticalSxLayout;
    QHBoxLayout* divH, *hLeftBottoni;
    QCheckBox* studenteCheckbox, *corsoNuotoCheckbox, *schedaPalestraCheckbox;
    QLineEdit* nomeLineEdit, *nomeIstruttorePiscinaEdit, *nomeIstruttorePalestraEdit,* cognomeLineEdit,*codFiscLineEdit,*ldnLineEdit,*residenzaLineEdit,*viaLineEdit,*telefonoLineEdit,*mailLineEdit;
    QCheckBox* All,*palestraCheckFiltro,*piscinaCheckFiltro,*minorenne,*maggiorenne,*deseleziona;
    QLineEdit* lineCerca;
    QDateEdit* dateNascita,*dateScadPiscina,*dateScadPalestra;
    QPushButton* Cerca;
    QPushButton* addButton,*modButton,*removeButton;
    viewListaClienti *listaClienti;
    QLabel *nomeClienteLabel, *cognomeClienteLabel,*codiceFClienteLabel,* LuogoDNLabel,*residenzaClienteLabel,*viaClienteLabel, *telefonoClienteLabel, *mailClienteLabel, *datadNClienteLabel,*AbbonamentoPiscinaLabel, *nomeIstruttorePiscinaLabel, *AbbonamentoPalestraLabel,*nomeIstruttorePalestraLabel;
    void setMainWindowStyle();
    //void handleSearchClick(); da implementare


signals:
    void signOpenAddWindow();
    void signOpenModWindow();
    void cercaRuntime();
    void salvaFileMenu();
    //void clickedSearch(QString searchText); da implementare search
    void richiestaRimozCliente(const unsigned int);
    void richiestaShowCliente(const unsigned int);

};

#endif // GUI_H
