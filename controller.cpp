#include "controller.h"
controller::controller(QObject *parent) : QObject(parent),view(new mainwindow()), addClientW(new addClientWindow()),infoProgetto(new info()), ModifyClientW(new modifyClientWindow()), m(new model("data.xml"))
{
    connect(view,SIGNAL(signOpenAddWindow()),this,SLOT(openAddView()));
    connect(view,SIGNAL(infoWindow()),this,SLOT(openInfoWindow()));
    connect(view,SIGNAL(signOpenModWindow()),this,SLOT(openModifyView()));
    connect(view,SIGNAL(salvaFileMenu()),this,SLOT(salvaFile()));
    connect(view,SIGNAL(richiestaRimozCliente(const unsigned int)),this,SLOT(rimuoviCliente(const unsigned int)));
    connect(view,SIGNAL(richiestaShowCliente(const unsigned int)),this,SLOT(mostraCliente(const unsigned int)));
    connect(view, SIGNAL(cercaRuntime()), this, SLOT(resetListaClienti()));
    connect(view, SIGNAL(filtroPiscina()), this, SLOT(filtraClientiPiscina()));
    connect(view, SIGNAL(filtroTutti()), this, SLOT(filtraTuttiClienti()));
    connect(view, SIGNAL(filtroPalestra()), this, SLOT(filtraClientiPalestra()));
    connect(view, SIGNAL(filtroMaggiorenne()), this, SLOT(filtraClientiMaggiorenni()));
    connect(view, SIGNAL(filtroMinorenne()), this, SLOT(filtraClientiMinorenni()));
    connect(view, SIGNAL(filtroStudente()), this, SLOT(filtraClientiStudenti()));
    connect(view,SIGNAL(controllaModificato()),this,SLOT(salvaIfModificato()));
    connect(view, SIGNAL(signStampaPDFCliente(const unsigned int)), this, SLOT(stampaPDFCliente(const unsigned int)));
    connect(view, SIGNAL(signEsportaCsvClienti()), this, SLOT(esportaCsvClienti()));
    connect(view, SIGNAL(signEsportaPDFClienti()), this, SLOT(esportaPDFClienti()));
    connect(view, SIGNAL(filtroVip()), this, SLOT(filtraClientiVip()));
    connect(view, SIGNAL(filtroCorsoNuoto()), this, SLOT(filtraClientiIstruttoriPiscina()));
    connect(view, SIGNAL(filtroSchedaPalestra()), this, SLOT(filtraClientiIStruttoriPalestra()));

    connect(m, SIGNAL(clienteAggiunto()), this, SLOT(resetListaClienti()));
    connect(m, SIGNAL(clienteRimosso()), this, SLOT(resetListaClienti()));
    connect(m, SIGNAL(clienteRimosso()), this, SLOT(clienteRimossoShowBox()));
    connect(m, SIGNAL(resetColoreFiltroM()), this, SLOT(resetColoreFiltroC()));

    connect(addClientW, SIGNAL(inviaStringaCliente(const QStringList)), this, SLOT(aggClienteContainer(const QStringList)));
    connect(addClientW, SIGNAL(erroreInput(string)), this, SLOT(erroreInputRicevuto(string)));
    connect(addClientW, SIGNAL(erroreDatax()),this , SLOT(erroreDataRicevuto()));

    connect(ModifyClientW, SIGNAL(rimpiazzaCliente(const unsigned int,const QStringList)), this, SLOT(rimpiazzaItem(const unsigned int, QStringList)));
    resetListaClienti();
    view->show();
}

controller::~controller()
{
    delete m;
}

void controller::openInfoWindow() const
{
    infoProgetto->show();
}
void controller::openAddView() const
{
    addClientW->pulisciRighe();
    addClientW->setModal(true);
    addClientW->show();
}

void controller::salvaFile()
{
    m->salva();
}

void controller::openModifyView() const
{
    if(view->isSelected()){
        ModifyClientW->caricaDati(m->getCampiCliente(view->getIndexSelected()), view->getIndexSelected());
        ModifyClientW->setModal(true);
        ModifyClientW->show();
    }
    else
        view->nessunSelezionato();
}

void controller::rimuoviCliente(const unsigned int indice){
    m->rimuoviCliente(indexTranslate[indice]);
}

void controller::rimpiazzaItem(const unsigned int indice, const QStringList stringaCliente)
{
    m->modificaItem(indexTranslate[indice], stringaCliente);
    resetListaClienti();
}

void controller::mostraCliente(const unsigned int cliente){
    view->visualizzaDettagliCliente(m->mostraCliente(indexTranslate[cliente]));
}

void controller::salvaIfModificato()
{
    if (m->getModificato())
        if(QMessageBox::question(view, "ChinaFit","Desideri salvare le modifiche?")==QMessageBox::Yes){
            emit salvaFile();
        }
}

void controller::filtraClientiPiscina()
{
    m->filterPiscina();
    resetListaClienti();
}

void controller::filtraTuttiClienti()
{
    m->resetfiltro();
    resetListaClienti();
}

void controller::filtraClientiPalestra()
{
    m->filterPalestra();
    resetListaClienti();
}

void controller::filtraClientiMaggiorenni()
{
    m->filterMaggiorenne();
    resetListaClienti();
}

void controller::filtraClientiMinorenni()
{
    m->filterMinorenne();
    resetListaClienti();
}

void controller::filtraClientiStudenti()
{
    m->filterStudente();
    resetListaClienti();
}

void controller::filtraClientiVip()
{
    m->filterVip();
    resetListaClienti();
}

void controller::filtraClientiIstruttoriPiscina()
{
    m->filterCorsoPiscina();
    resetListaClienti();
}

void controller::filtraClientiIStruttoriPalestra()
{
    m->filterSchedaPalestra();
    resetListaClienti();
}

void controller::clienteRimossoShowBox(){
    QMessageBox clienteRimossoBox;
    clienteRimossoBox.information(view,"Cliente rimosso","Il cliente è stato rimosso con successo!");
}

void controller::resetColoreFiltroC() const
{
    view->resetColoreFiltro();
}

void controller::stampaPDFCliente(const unsigned int cliente) const
{
        QString nomeFile = QFileDialog::getSaveFileName(view,"Stampa Cliente","../ChinaStock/ClientePdf","Cliente_pdf(*.pdf)");
        QPdfWriter writer(nomeFile);
        QPainter painter(&writer);
        painter.setPen(Qt::black);
        painter.drawText(700,1200,"DATI DI");
        painter.drawText(700,2000,"Codice Fiscale:");
        painter.drawText(700,2400,"Luogo Di Nascita:");
        painter.drawText(700,2800,"Residenza:");
        painter.drawText(700,3200,"Via:");
        painter.drawText(700,3600,"Numero Telefono:");
        painter.drawText(700,4000,"Mail:");
        painter.drawText(700,4400,"Data Di Nascita:");
        painter.drawText(700,4800,"Studente:");
        painter.drawText(700,5200,"Data Corso Piscina:");
        painter.drawText(700,5600,"Nome Istruttore Piscina:");
        painter.drawText(700,6000,"Corso Nuoto:");
        painter.drawText(700,6400,"Data Scheda Palestra:");
        painter.drawText(700,6800,"Nome Istruttore Palestra:");
        painter.drawText(700,7200,"Scheda Palestra");

        QStringList p = m->getCampiCliente(cliente);

        QString nomeTmp =(p.at(0));
        QString cognomeTmp=(p.at(1));
        QString codFisc=(p.at(2));
        QString ldn=(p.at(3));
        QString residenza=(p.at(4));
        QString via=(p.at(5));
        QString numerovia=(p.at(6));
        QString telefono=(p.at(7));
        QString mail=(p.at(8));
        QString datenascita=(p.at(9));
        QString studente=(p.at(10));
        QString datacorsopiscina =(p.at(11));
        QString nomeistruttorepiscina=(p.at(12));
        QString corsonuoto =(p.at(13));
        QString dateschedaPalestra =(p.at(14));
        QString Nomeistruttorepalestra =(p.at(15));
        QString schedaPalestra = (p.at(16));
        painter.drawText(3000,1200,nomeTmp+" "+cognomeTmp);
        painter.drawText(3000,2000,codFisc);
        painter.drawText(3000,2400,ldn);
        painter.drawText(3000,2800,residenza);
        painter.drawText(3000,3200,via);
        painter.drawText(3000,3600,telefono);
        painter.drawText(3000,4000,mail);
        painter.drawText(3000,4400,datenascita);
        painter.drawText(3000,4800,studente);
        painter.drawText(3000,5200,datacorsopiscina);
        painter.drawText(3000,5600,nomeistruttorepiscina);
        painter.drawText(3000,6000,corsonuoto);
        painter.drawText(3000,6400,dateschedaPalestra);
        painter.drawText(3000,6800,Nomeistruttorepalestra);
        painter.drawText(3000,7200,schedaPalestra);

        painter.end();
}

void controller::esportaCsvClienti() const
{
    QString nomeFile = QFileDialog::getSaveFileName(view,"Esporta csv","../ChinaStock/ClientiCsv");
    if(!nomeFile.endsWith(".csv"))
    nomeFile=nomeFile+".csv";
    string str = nomeFile.toStdString();
    ofstream myfile(str);
    QStringList listaClienti = m->getListaClientiCsv();

    myfile<<"Nome,Cognome,Codice fiscale,Luogo di nascita,Residenza,Via,Telefono,Mail,Data di nascita,Studente,Scadenza piscina,Istruttore piscina,Corso nuoto,Scadenza palestra,Istruttore palestra,Scheda"<<endl;
    auto it = listaClienti.begin();
    while(it!=listaClienti.end()){
        myfile<<it->toStdString()<<endl;
        ++it;
    }
    myfile.close();
}

void controller::esportaPDFClienti() const
{
    QString nomeFile = QFileDialog::getSaveFileName(view,"Stampa Cliente","../ChinaStock/ClientiTotaliPdf","ListaClientiTOTALE_pdf(*.pdf)");
    QPdfWriter writer(nomeFile);
    QPainter painter(&writer);
    painter.setPen(Qt::black);

    int l=900, a1=1000;
    QStringList clienti = m->getListaClientiPDF();
    for(auto it = clienti.begin();it!=clienti.end();++it)
    {
        painter.drawText(l,a1,*it);
        a1+=400;
    }
    painter.end();
}

void controller::resetListaClienti()
{
    QString parolaNelCampoCerca = view->getParolaCercata();
    view->mostraClienti(m->getListaClientiFiltrata(parolaNelCampoCerca,indexTranslate));
    resetDettClienteView();
}

void controller::resetDettClienteView() const{
    view->resetDettCliente();
}

void controller::aggClienteContainer(const QStringList dettagli)
{
    m->aggNelContainer(dettagli);
}

void controller::erroreInputRicevuto(string motivo)
{
    addClientW->mostraErroreInput(motivo);
}

void controller::erroreDataRicevuto()
{
    addClientW->mostraErroreData();
}
