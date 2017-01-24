#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "deo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Dodaj_clicked();

    void on_Obrisi_clicked();

    void on_Izracunaj_clicked();

    void on_Ucitaj_clicked();

    void on_ObrisiSVe_clicked();

private:

    std::vector<Deo> elementi;

    void upisi();
    void menjaj(int d,int k,char c);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
