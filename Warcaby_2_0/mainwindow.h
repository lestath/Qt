#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "board.h"

namespace Ui {
class MainWindow;
class Board;
}
///
/// \brief The MainWindow class - klasa głównego okna programu
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    ///
    /// \brief  - wskaźnik projektu graficznego
    ///
    Ui::MainWindow *ui;
    ///
    /// \brief  - wskaźnik planszy
    ///
    Board * board;
public slots:
    ///
    /// \brief  - slot inicjujacy nową grę
    ///
   void init();
   ///
   /// \brief  - slot zmieniający tekst etykiety informującej o ruchu
   ///
   void changeLabel();
};

#endif // MAINWINDOW_H
