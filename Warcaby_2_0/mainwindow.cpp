#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    board = new Board(parent);
    // inicjalizacja i ustawienie parametrów plnszy do gry
    board->setMinimumSize(620,620);
    board->setMaximumSize(620,620);
    board->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    board->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->setupUi(this);
    ui->gridLayout->addWidget(board);

    // utworzenie powiązań między sygnałami i slotami widgetów
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(init()));
    connect(board,SIGNAL(changeLabel()),this,SLOT(changeLabel()));
}


void MainWindow::init(){
 this->board->initGame();

}


MainWindow::~MainWindow()
{
 ui->gridLayout->removeWidget(board);
 delete ui->label;
 delete board;
 delete ui->verticalLayout;
 delete ui->gridLayout;
 delete ui;
}

void MainWindow::changeLabel()
{
    if(board->Round == 'b'){
     ui->label->setText(QString :: fromUtf8("Ruch Gracza: Czarny"));
    }else{
     ui->label->setText(QString :: fromUtf8("Ruch Gracza: Biały"));
    }
}
