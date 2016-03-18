#ifndef PAWN_H
#define PAWN_H
#include <QGraphicsPixmapItem>
#include "board.h"
class Board; // predefinicja klasy Board
///
/// \brief The Pawn class - klasa reprezentująca pionek. Dziedziczy po klasie "QGraphicsPixmapItem"
///
class Pawn : public QGraphicsPixmapItem
{

public:
    Pawn();
    ~Pawn();
    ///
    /// \brief - wskaźnik na plaszę, na której znajduje się pionek. Powiązanie takie ułatwia kontrolę planszy z poziomu pionka.
    ///
    Board * BoardPtr;

    ///
    /// \brief - współrzędna logiczna X pionka
    ///
    int LogicX;
    ///
    /// \brief - współrzędna logiczna Y pionka
    ///
    int LogicY;
    ///
    /// \brief - znak koloru pionka. Jeżeli wartość równa 'b' to pionek należy do zestawu czarnych. Jeżeli wartość równa 'w' to pionek należy do zestawu białych.
    ///
    char Color;
    ///
    /// \brief - informuje o tym czy pionek jest damką, jeżeli wartość równa "True" to pionek istotnie nia jest.
    ///
    bool Status;
    ///
    /// \brief - identyfikator pionka wewnątrz danego zestawu
    ///
    int ID;
    ///
    /// \brief - przechwytuje zdarzenie przesunięcia myszy. Kontroluje zachowanie przemieszczania się pionka, tak by kursor znajdował się na jego środku w czasie przesuwania
    /// \param eve - parametr przechwytujący zdarzenie przesunięcia myszki na planszy
    ///
    void mouseMoveEvent(QGraphicsSceneMouseEvent *eve = NULL);
    ///
    /// \brief - przechwytuje zdarzenie zwolnienia przycisku myszy. Wszystkie funkcje konrolujące przebieg gry uruchamiane są w czasie zwolnienia przycisku myszy z pionka
    /// \param event2 - parametr przechwytujący zdarzenie zwolnienia przycisku myszy na planszy
    ///
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event2 = NULL);
    ///
    /// \brief - sprawdza czy zwykły pionek ma dostępne bicie
    /// \return - jeżeli "True" to pionek ma bicie
    ///
    bool hasPawnStrike();
    ///
    /// \brief  - sprawdza czy damka ma dostępne bicie
    /// \return - jeżeli "True" to damka ma bicie
    ///
    bool hasLadyStrike();
    ///
    /// \brief  - sprawdza czy zwykły pionek może wykonać ruch. Nie uwzględnia bicia
    /// \return - jeżeli "True" to pionek może wykonac ruch
    ///
    bool hasMove();

private:
    ///
    /// \brief  - funkcja wykonująca ruch pionka. Po wykonaniu niezbędnych funkcji sprawdzających decyduje czy pozycja pionka zostanie zmieniona czy wraca on na poprzednie miejsce i nie nastepuje zmiana rundy.
    /// \param  - wskaźnik kursora myszy
    ///
   void pawnMove(QPoint *mouse);
   ///
   /// \brief  - funkcja wykonująca ruch lub bice dla damki, w zależności od wartości drugiego parametru
   /// \param  - wskaźnik kursora myszy
   /// \param  - jeżeli "True" to wykonany zostanie blok instrukcji dla bicia, jeżeli "False" to blok ruchu bez bicia
   ///
   void ladyMove(QPoint *mouse,bool strikeflag);
   ///
   /// \brief  - funkcja wykonuje bicie dla zwykłego pionka
   /// \param  - wskaźnik kursora myszy
   ///
   void pawnStrike(QPoint *mouse);
   ///
   /// \brief  - funkcja sprawdza czy pionek zyskał status damki, jeżeli tak to podmienia jego obrazek i zmienia wartość jego pola "Status" na "True"
   ///
   void checkIfLady();

};

#endif // PAWN_H
