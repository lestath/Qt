#ifndef BOARD_H
#define BOARD_H

#include "pawn.h"
#include <QGraphicsView>

class Pawn; // predefinicja klasy Pawn
///
/// \brief The Board class - klasa reprezentująca planszę do gry. Dziedziczy po klasie widoku graficznego "QGraphicsView"
///
class Board: public QGraphicsView
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    ///
    /// \brief  - funkcja inicjująca grę. Ustawia wartości i pozycje początkowe pionków
    ///
    void initGame();
    ///
    /// \brief  - funkcja wyłącza możliwość ruchu dla zestawu pionków, którego kolor podany został w parametrze
    /// \param color - parametr przyjmujący znak koloru zestawu 'b' : zestaw czarny ; 'w' : zestaw biały
    ///
    void lockSet(const char color);
    ///
    /// \brief  - funkcja odblokowuje ruch dla zestawu pionków, którego kolor podany został w parametrze
    /// \param color - parametr przyjmujący znak koloru zestawu 'b' : zestaw czarny ; 'w' : zestaw biały
    ///
    void unlockSet(const char color);
    ///
    /// \brief - funkcja zmienia rundę na rzecz gracza oczekującego na ruch
    ///
    void changeRound();
    ///
    /// \brief  - generuje informacje o zwycięzcy rozgrywki w zależności od koloru podanego w parametrze
    /// \param Color - parametr przyjmujący znak koloru zwycięzkiego zestawu, lub znak remisu  'b' : wygrał czarny ; 'w' : wygrał biały ; 'd' : nastąpił remis
    ///
    void setWinner(char Color);
    ///
    /// \brief - przechwytuje zdarzenie scrolla na planszy w celu zapobiegnięcia niechcianemu przesuwaniu się planszy
    /// \param event - parametr przechwytujący zdarzenie scroll na planszy
    ///
    void wheelEvent ( QWheelEvent * event );
    ///
    /// \brief - przechowuje informacje o tym, który gracz ma obecnie ruch. Dla wartości 'b' : ruch czarnego a dla wartości 'w' : ruch białego
    ///
    char Round;
    ///
    /// \brief - tablica jednowymiarowa przechowująca współrzędne dla poszczególnych pól szachownicy. Pomaga w ustawieniu pionka na odpowiedniej pozycji sceny
    ///
    int BoardMap[10];
    ///
    /// \brief - tablica dwuwymiarowa przechowująca informacje o dostępności poszczególnych pól planszy. Jeżeli wartość "True" to pole jest wolne.
    ///
    bool BoardFieldAcces[10][10];
    ///
    /// \brief - licznik ruchów białej damki w których nie wykonała bicia. Potrzebny do ustalenia remisu. Zeruje się w momencie wykonania bicia przez którąkolwiek damkę.
    ///
    int MoveWhiteCounter;
    ///
    /// \brief  - licznik ruchów czarnej damki w których nie wykonała bicia. Potrzebny do ustalenia remisu. Zeruje się w momencie wykonania bicia przez którąkolwiek damkę.
    ///
    int MoveBlackCounter;
    ///
    /// \brief - wskaźnik sceny graficznej
    ///
    QGraphicsScene * Scene;
    ///
    /// \brief - wskaźnik na obrazek planszy
    ///
    QPixmap * BoardImg;
    ///
    /// \brief - wskaźnik na obrazek białego pionka
    ///
    QPixmap * WhitePawnImg;
    ///
    /// \brief - wskaźnik na obrazek czarnego pionka
    ///
    QPixmap * BlackPawnImg;
    ///
    /// \brief - wskaźnik na obrazek białej damki
    ///
    QPixmap * WhiteLadyImg;
    ///
    /// \brief - wskaźnik na obrazek czarnej damki
    ///
    QPixmap * BlackLadyImg;
    ///
    /// \brief - wskaźnik do informacji o wygranym wyświetlany na końcu rozgrywki
    ///
    QGraphicsPathItem * Path;
    ///
    /// \brief - wskaźnik białego tła informacji o wygranym
    ///
    QGraphicsRectItem * WinnerRect;
    ///
    /// \brief - wskaźnik na tablicę zestawu białych pionków
    ///
    Pawn * WhiteSet;
    ///
    /// \brief - wskaźnik na tablicę zestawu czarnych pionków
    ///
    Pawn * BlackSet;

signals:
    ///
    /// \brief - sygnał emitowany w momencie zmiany rundy, w celu zmiany tekstu etykiety informującej o obecnym ruchu
    ///
   void changeLabel();
};


#endif // BOARD_H
