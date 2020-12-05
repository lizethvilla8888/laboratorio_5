#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QFile> // leer archivos
#include <QDebug>
#include <QPixmap>
#include <QVector>

#include "cuerpo.h"
#include "enemy.h"
#include "pared.h"
#include "moneda.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots:
  //  void moveEnemy();

private:
    Ui::MainWindow *ui;

    //QTimer *timer;

    cuerpo *personaje;
    enemy *enemigo;

    QList<moneda *> monedas;
    QList <pared*> paredes;

    QGraphicsScene *scene;

    void keyPressEvent(QKeyEvent * evento);
    QList<moneda *> eliminarMonedas(QList<moneda *> monedas,int pos);
    void crear_pared(int, int);
    void crear_monedas (int, int);
     //QList<moneda *> eliminarMonedas(QList<moneda *> monedas,int pos);
    void moveEnemy();

};
#endif // MAINWINDOW_H

