#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(590,400);
    scene->setSceneRect(0,0,500,500);
    scene->setBackgroundBrush(QPixmap(":/new/prefix1/imagenes/fondo.jpg"));

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Pac Man");

    personaje = new cuerpo(20,30,30); // se crea bolita de pacman
    scene->addItem(personaje);

    enemigo = new enemy(20,420,180); // se crea fantasma
    scene->addItem(enemigo);

    QMediaPlayer *music_inicio_pacman = new QMediaPlayer();
    music_inicio_pacman->setMedia(QUrl("qrc:/sonido /musica/Pacman_Cancion.mp3"));
    music_inicio_pacman->play();

    //AGREGO MONEDAS
    int x = 30, y= 30 ;
    for (int i = 0; i<7 ;i ++){
        x=30;//x=30;
        for (int j =0  ; j<9; j++,x+=65){
             crear_monedas(x,y);
        }
        y+=55;// y+=40;
       crear_monedas(x,y);
     }
    //AGREGO PAREDES
     x = 60, y= 60 ;
    for (int i = 0; i<3 ;i ++){
        x=60;//x=30;
        for (int j =0  ; j<4; j++,x+=130){
             crear_pared(x,y);
        }
        y+=110;// y+=40;
       crear_pared(x,y);
     }
    int p_s[16] = {0,0,590,10,0,0,10,400,0,390,590,10,580,0,10,400};
    for (int i=0;i<=16;i+=4)
    {
        paredes.push_back(new pared(p_s[i],p_s[i+1],p_s[i+2],p_s[i+3]));
        scene->addItem(paredes.back());
    }

    puntaje_ = new puntaje;
    scene->addItem(puntaje_);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveEnemy()));
    timer->start(25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento){
    if(evento->key()==Qt::Key_D)
     {
         //Evaluacion de colision con monedas
        personaje->Move_derecha();
        for (int i = 0;i < monedas.size();i++) {
             if(personaje->collidesWithItem(monedas.at(i))){
                 puntaje_->incremento(); // incremento de puntaje

                 scene->removeItem(monedas.at(i));
                 monedas.removeAt(i);
              }
         }
        //Colicion con muros
        for (int i = 0;i < paredes.size();i++) {
             if(personaje->collidesWithItem(paredes.at(i))){
                personaje->Move_izquierda();
             }
        }
    }
     else if(evento->key()==Qt::Key_S)
     {
        personaje->Move_arriba();
        for (int i = 0;i < monedas.size();i++) {
             if(personaje->collidesWithItem(monedas.at(i))){
                puntaje_->incremento(); // incremento de puntaje

                scene->removeItem(monedas.at(i));
                monedas.removeAt(i);
              }
         }

        //Colicion con muros
        for (int i = 0;i < paredes.size();i++) {
             if(personaje->collidesWithItem(paredes.at(i))){
                personaje->Move_abajo();
             }
        }
    }
     else if (evento->key()==Qt::Key_Z)
     {
         personaje->Move_abajo();
         for (int i = 0;i < monedas.size();i++) {
              if(personaje->collidesWithItem(monedas.at(i))){
                  puntaje_->incremento(); // incremento de puntaje
                  scene->removeItem(monedas.at(i)); // eliminar moneda de esena
                  monedas.removeAt(i);
               }
          }
         //Colicion con muros
         for (int i = 0;i < paredes.size();i++) {
              if(personaje->collidesWithItem(paredes.at(i))){
                 personaje->Move_arriba();
              }
         }
     }
     else if (evento->key()==Qt::Key_A)
     {
        //if(!EvaluarColision())
        personaje->Move_izquierda();
        for (int i = 0;i < monedas.size();i++) {
             if(personaje->collidesWithItem(monedas.at(i))){
                 puntaje_->incremento(); // incremento de puntaje
                 scene->removeItem(monedas.at(i));
                 monedas.removeAt(i);
              }
         }
        //Colicion con muros
        for (int i = 0;i < paredes.size();i++) {
             if(personaje->collidesWithItem(paredes.at(i))){
                personaje->Move_derecha();
             }
        }
    }   
}

void MainWindow::crear_pared(int x, int y)
{
    int ancho = 80, alto = 60;
    paredes.push_back(new pared(x,y,ancho,alto));
    scene->addItem(paredes.back());
}

void MainWindow::crear_monedas(int x, int y)
{
    int ancho = 10;
    monedas.push_back(new moneda(x,y,ancho,ancho));
    scene->addItem(monedas.back());
}

QList<moneda *> MainWindow::eliminarMonedas(QList<moneda *> monedas, int pos)
{
    QList<moneda *> aux;
    for (int i = 0;i < monedas.size() ; i++) {
        if(i != pos){
            aux.push_back(monedas.at(i));
        }
    }
    return aux;
}

void MainWindow::moveEnemy()
{
    if(enemigo->x() < personaje->x()){
        enemigo->right();

        for (int i = 0;i < paredes.size();i++) {
             if(enemigo->collidesWithItem(paredes.at(i))){
                enemigo->left();
             }
        }
    }

    else if(enemigo->x() > personaje->x()){
        enemigo->left();

        for (int i = 0;i < paredes.size();i++) {
             if(enemigo->collidesWithItem(paredes.at(i))){
                enemigo->right();
             }
        }
    }

    else if(enemigo->y() < personaje->y()){
        enemigo->down();
        for (int i = 0;i < paredes.size();i++) {
             if(enemigo->collidesWithItem(paredes.at(i))){
                enemigo->up();
             }
        }
    }
    else if(enemigo->y() > personaje->y()){
        enemigo->up();
        for (int i = 0;i < paredes.size();i++) {
             if(enemigo->collidesWithItem(paredes.at(i))){
                enemigo->down();
             }

        }
    }
enemigo->setPos(enemigo->posx,enemigo->posy);
}







