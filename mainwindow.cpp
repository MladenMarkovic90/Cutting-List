#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "krojnalista.h"
#include "deo.h"
#include <vector>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <algorithm>

//#define DEBUG

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    elementi.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upisi()
{
    //qDeleteAll(ui->listWidget->selectedItems());

    ui->listWidget->clear();
    int n=elementi.size();
    for(int i=0;i<n;i++)
    {
        if(elementi[i].kolicina() > 0)
            ui->listWidget->addItem(QString("%1x%2").arg(elementi[i].kolicina()).arg(elementi[i].duzina()));
#ifdef DEBUG
        std::cout << "Debug: " << elementi[i].kolicina() << "x" << elementi[i].duzina() << std::endl;
#endif
    }
#ifdef DEBUG
    std::cout << "END" << std::endl;
#endif
}

void MainWindow::on_Dodaj_clicked()
{
    int duzina=abs(ui->unos2->text().toInt());
    int kolicina=abs(ui->unos1->text().toInt());
    menjaj(duzina,kolicina,'+');
}

void MainWindow::menjaj(int duzina,int kolicina,char c)
{
    int n=elementi.size();
    int i;

    for(i=0;i<n;i++)
        if(elementi[i].duzina()==duzina)
        {
            elementi[i].kolicina(kolicina,c);
            if(elementi[i].kolicina() < 0)
                elementi[i].kolicina(0);
            break;
        }


    if(i == n)
        elementi.push_back(Deo(duzina,kolicina));

    upisi();
}

void MainWindow::on_Obrisi_clicked()
{
    int duzina=ui->unos2->text().toInt();
    int kolicina=ui->unos1->text().toInt();
    menjaj(duzina,kolicina,'-');
}

void MainWindow::on_Izracunaj_clicked()
{
    ui->Izracunaj->setEnabled(false);
    ui->textBrowser->setText(QString(""));
    std::vector<int> niz;

    //unsigned int n=ui->listWidget->count();

    for(unsigned int i=0;i<elementi.size();i++)
        for(int j=0;j<elementi[i].kolicina();j++)
            niz.push_back(elementi[i].duzina());
    niz.push_back(0);

    std::sort(niz.begin(),niz.end(),std::greater<int>());

    int min=ui->minOtpad->text().toInt();
    int max=ui->maxOtpad->text().toInt();
    int duzinaSipke=ui->duzinaSipke->text().toInt();
    int sirinaReza=ui->sirinaReza->text().toInt();

#ifdef DEBUG
    std::cout << "MinMax: " << min << " : " << max << std::endl;
#endif


    krojnaLista * k;


    while(niz[0]!=0)
    {
        k=new krojnaLista(min,max,duzinaSipke,sirinaReza,niz);
        k->racunaj();
        if(k->error())
        {
            ui->textBrowser->append(QString("Error: "));
            ui->textBrowser->append(QString(k->stanje().c_str()));
            delete k;
            break;
        }
        else
            ui->textBrowser->append(k->ispis());
        delete k;
    }

#ifdef DEBUG
    std::cout << std::endl << "END" << std::endl;
#endif

    ui->Izracunaj->setEnabled(true);
}

void MainWindow::on_Ucitaj_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, "Otvorite podatke", QDir::homePath());

    std::fstream file(fileName.toLocal8Bit().data(),std::fstream::in);

    if(!file)
    {
        std::cout << "Error while opening: " << fileName.toLocal8Bit().data() << std::endl;
        return;
    }

    std::string text;

    file >> text; ui->duzinaSipke->setText(text.c_str());

    file >> text; ui->sirinaReza->setText(text.c_str());

    file >> text; ui->minOtpad->setText(text.c_str());

    file >> text; ui->maxOtpad->setText(text.c_str());


    ui->listWidget->clear();

    elementi.clear();

    while(file)
    {
        int kolicina;
        int duzina;
        file >> kolicina;
        file >> duzina;

        std::cout << kolicina << "x" << duzina << std::endl;

        menjaj(duzina,kolicina,'+');
    }


    file.close();
}

void MainWindow::on_ObrisiSVe_clicked()
{
    ui->listWidget->clear();
    elementi.clear();
}
