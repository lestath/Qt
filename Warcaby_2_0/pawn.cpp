#include "pawn.h"


Pawn::Pawn():QGraphicsPixmapItem()
{
  BoardPtr = NULL;
  Color = 'w';
  Status =false;
  LogicX = -10;
  LogicY = -10;
  ID = 0;
}

Pawn::~Pawn()
{
 if(LogicX!=-10){
  BoardPtr->Scene->removeItem(this);
 }
}
void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *even)
{
   QPoint mousepos = this->BoardPtr->mapFromGlobal(QCursor::pos());
   this->setPos((qreal)mousepos.x()-20,(qreal)mousepos.y()-20);
}

// funkcja uruchamia sie na zwolnienie przycisku myszy, zawiera instrukcje sterujące przebiegiem gry
void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event2)
{

    if(ItemIsMovable){
     QPoint mouse = this->BoardPtr->mapFromGlobal(QCursor::pos());
         if(Status){
          ladyMove(&mouse,hasLadyStrike());
         }else{
              if(hasPawnStrike()){
                 pawnStrike(&mouse);
              }else{
                 pawnMove(&mouse);
              }
         }
    }
   setPos((qreal)BoardPtr->BoardMap[this->LogicX],(qreal)BoardPtr->BoardMap[this->LogicY]);// fizyczne ustawienie pionka na szachownicy według współrzednych logicznych
}


//funkcja sprawdza czy dostępne są bicia dla tego pionka;
bool Pawn::hasPawnStrike()
{
    int i = 0;
    int x = -1;
    int y;

    while(x<2){
    y = -1 ;
     while(y<2){
        if(((LogicX+2*x)<10)&&((LogicX+2*x)>-1)&&((LogicY+2*y)>-1)&&((LogicY+2*y)<10)){
         if(BoardPtr->BoardFieldAcces[LogicX+2*x][LogicY+2*y]){
          if(BoardPtr->BoardFieldAcces[LogicX+x][LogicY+y]==false){
           if(Color=='b'){
             for(i=0;i<20;i++){
               if((BoardPtr->WhiteSet[i].LogicX==LogicX+x)&&((BoardPtr->WhiteSet[i].LogicY==LogicY+y))){
                return true;
               }
             }
           }else{
             for(i=0;i<20;i++){
                 if((BoardPtr->BlackSet[i].LogicX==LogicX+x)&&((BoardPtr->BlackSet[i].LogicY==LogicY+y))){
                  return true;
                 }
             }
          }
         }
        }
       }
      y=y+2;
     }
    x=x+2;
   }
 return false;
}

// wykonuje ruch pionka
void Pawn::pawnMove(QPoint *mouse)
{
   int x = -1;
   int y;
   if(Color=='b'){y=1;}else{y=-1;}
   while(x<2){
    if((x+LogicX<10) && (x+LogicX>-1)){
        if(((mouse->x())>BoardPtr->BoardMap[LogicX+x])&&((mouse->x())<(BoardPtr->BoardMap[LogicX+x]+30))){
           if((y+LogicY<10) && (y+LogicY>-1)){
               if(((mouse->y())>BoardPtr->BoardMap[LogicY+y])&&((mouse->y())<(BoardPtr->BoardMap[LogicY+y]+30))){
                  if(BoardPtr->BoardFieldAcces[LogicX+x][LogicY+y]){
                     BoardPtr->BoardFieldAcces[LogicX][LogicY]=true;
                     LogicX=LogicX+x;
                     LogicY=LogicY+y;
                     BoardPtr->BoardFieldAcces[LogicX][LogicY]=false;
                     checkIfLady();
                     BoardPtr->changeRound();
                  }
               }
          }
        }
   }
   x=x+2;
  }
}
 // koniec funkcji pawnMove();
void Pawn::pawnStrike(QPoint *mouse)
{
   int x = -1;
   int i;
   int y;
   while(x<2){
   y = -1 ;
    while(y<2){
      if((2*x+LogicX<10) && (2*x+LogicX>-1)){
                if(((mouse->x())>BoardPtr->BoardMap[LogicX+2*x])&&((mouse->x())<(BoardPtr->BoardMap[LogicX+2*x]+30))){
                   if((2*y+LogicY<10) && (2*y+LogicY>-1)){
                       if(((mouse->y())>BoardPtr->BoardMap[LogicY+2*y])&&((mouse->y())<(BoardPtr->BoardMap[LogicY+2*y]+30))){
                           if(BoardPtr->BoardFieldAcces[LogicX+2*x][LogicY+2*y]){
                            if(BoardPtr->BoardFieldAcces[LogicX+x][LogicY+y]==false){
                             if(Color=='b'){
                               for(i=0;i<20;i++){
                                 if((BoardPtr->WhiteSet[i].LogicX==LogicX+x)&&((BoardPtr->WhiteSet[i].LogicY==LogicY+y))){
                                  BoardPtr->Scene->removeItem(&BoardPtr->WhiteSet[i]);
                                  BoardPtr->WhiteSet[i].LogicX =-10;
                                  BoardPtr->WhiteSet[i].LogicY =-10;
                                  BoardPtr->BoardFieldAcces[LogicX+x][LogicY+y]=true;
                                  BoardPtr->BoardFieldAcces[LogicX][LogicY]=true;
                                  this->LogicX=this->LogicX+2*x;
                                  this->LogicY=this->LogicY+2*y;
                                  BoardPtr->BoardFieldAcces[LogicX][LogicY]=false;
                                  BoardPtr->MoveBlackCounter = 0;
                                  BoardPtr->MoveWhiteCounter = 0 ;
                                  if(hasPawnStrike()){
                                   BoardPtr->lockSet(Color);
                                   setFlag(QGraphicsItem::ItemIsMovable,true);
                                  }else{
                                   checkIfLady();
                                   BoardPtr->changeRound();
                                  }
                                  return;
                                 }
                               }
                             }else{
                               for(i=0;i<20;i++){
                                   if((BoardPtr->BlackSet[i].LogicX==LogicX+x)&&((BoardPtr->BlackSet[i].LogicY==LogicY+y))){
                                    BoardPtr->Scene->removeItem(&BoardPtr->BlackSet[i]);
                                    BoardPtr->BlackSet[i].LogicX =-10;
                                    BoardPtr->BlackSet[i].LogicY =-10;
                                    BoardPtr->BoardFieldAcces[LogicX+x][LogicY+y]=true;
                                    BoardPtr->BoardFieldAcces[LogicX][LogicY]=true;
                                    this->LogicX=this->LogicX+2*x;
                                    this->LogicY=this->LogicY+2*y;
                                    BoardPtr->BoardFieldAcces[LogicX][LogicY]=false;
                                    BoardPtr->MoveBlackCounter = 0;
                                    BoardPtr->MoveWhiteCounter = 0 ;
                                    if(hasPawnStrike()){
                                     BoardPtr->lockSet(Color);
                                     setFlag(QGraphicsItem::ItemIsMovable,true);
                                    }else{
                                     checkIfLady();
                                     BoardPtr->changeRound();
                                    }
                                    return;
                                   }
                               }
                             }
                            }
                          }
                       }
                    }
                }
       }
     y=y+2;
    }
   x=x+2;
  }
}
void Pawn::ladyMove(QPoint *mouse, bool strikeflag) // ruchy damki z bicicem i bez
{
     int x,y; // iteratory sprawdzanych pozycji
     int i; // iterator pętli sprawdzającej sety;
     int nextx,nexty; // przyjmie pozycje zakończenia ruchu;
     int toremove = 0; // przyjmie identyfikator pionka do usunięcia
     int counter=0; // licznik pionków tego samego koloru występujących po drodze
     int counter2 =0; // licznik pionków innego koloru występujących po drodze
     nextx=-10;
     nexty=-10;
     x=-9;
     while(x<10){
       if((LogicX+x>9)||(LogicX+x<0)){x=x+1;continue;}
       if(((mouse->x())>BoardPtr->BoardMap[LogicX+x])&&((mouse->x())<(BoardPtr->BoardMap[LogicX+x]+30))){
        y=-9;
        while(y<10){
         if((LogicY+y>9)||(LogicY+y<0)){y=y+1;continue;}
         if(((mouse->y())>BoardPtr->BoardMap[LogicY+y])&&((mouse->y())<(BoardPtr->BoardMap[LogicY+y]+30))){
           nextx=LogicX+x;
           nexty=LogicY+y;
          }
        y=y+1;
        }
      }
     x=x+1;
    }
    if(nextx==-10){return;}
    if(nexty==-10){return;}
    x=LogicX;
    while(x!=nextx){
     if(x>nextx){x=x-1;}else{x=x+1;}
     y=LogicY;
     while(y!=nexty){
         if(y>nexty){y=y-1;}else{y=y+1;}
          if(((x+y)==(LogicX+LogicY))||((y-x)==(LogicY-LogicX))){
             if(!BoardPtr->BoardFieldAcces[x][y]){
                  if(Color=='b'){
                      for(i=0;i<20;i++){
                          if((BoardPtr->WhiteSet[i].LogicX==x) && (BoardPtr->WhiteSet[i].LogicY==y)){
                                 toremove=BoardPtr->WhiteSet[i].ID;
                                 counter = counter +1;
                           }
                      }
                      for(i=0;i<20;i++){
                          if((BoardPtr->BlackSet[i].LogicX==x) && (BoardPtr->BlackSet[i].LogicY==y)){
                              toremove=BoardPtr->BlackSet[i].ID;
                              counter2 = counter2 +1;
                          }
                     }
                  }else{
                       for(i=0;i<20;i++){
                           if((BoardPtr->BlackSet[i].LogicX==x) && (BoardPtr->BlackSet[i].LogicY==y)){
                               toremove=BoardPtr->BlackSet[i].ID;
                               counter = counter +1;
                           }
                      }
                       for(i=0;i<20;i++){
                           if((BoardPtr->WhiteSet[i].LogicX==x) && (BoardPtr->WhiteSet[i].LogicY==y)){
                                  toremove=BoardPtr->WhiteSet[i].ID;
                                  counter2 = counter2 +1;
                            }
                       }
                 }
            }
         }
    }
   }
   if(BoardPtr->BoardFieldAcces[x][y]){
        if(((x+y)==(LogicX+LogicY))||((y-x)==(LogicY-LogicX))){
            if(counter<2 && counter2==0){
                if(strikeflag){
                  if(counter>0){
                      BoardPtr->BoardFieldAcces[LogicX][LogicY] = true;
                      LogicX=x;
                      LogicY=y;
                      BoardPtr->BoardFieldAcces[LogicX][LogicY] = false;
                      BoardPtr->MoveBlackCounter = 0;
                      BoardPtr->MoveWhiteCounter = 0 ;
                      if(Color=='b'){
                         BoardPtr->Scene->removeItem(&BoardPtr->WhiteSet[toremove]);
                         BoardPtr->BoardFieldAcces[BoardPtr->WhiteSet[toremove].LogicX][BoardPtr->WhiteSet[toremove].LogicY] = true;
                         BoardPtr->WhiteSet[toremove].LogicX = -10;
                         BoardPtr->WhiteSet[toremove].LogicY = -10;
                      }else{
                          BoardPtr->Scene->removeItem(&BoardPtr->BlackSet[toremove]);
                          BoardPtr->BoardFieldAcces[BoardPtr->BlackSet[toremove].LogicX][BoardPtr->BlackSet[toremove].LogicY] = true;
                          BoardPtr->BlackSet[toremove].LogicX = -10;
                          BoardPtr->BlackSet[toremove].LogicY = -10;
                      }
                     if(hasLadyStrike()){
                      BoardPtr->lockSet(Color);
                      setFlag(QGraphicsItem::ItemIsMovable,true);
                     }else{
                      BoardPtr->changeRound();
                     }
                  }
                }else{
                    BoardPtr->BoardFieldAcces[LogicX][LogicY] = true;
                    LogicX=x;
                    LogicY=y;
                    BoardPtr->BoardFieldAcces[LogicX][LogicY] = false;
                    if(Color == 'b'){
                       BoardPtr->MoveBlackCounter =  BoardPtr->MoveBlackCounter + 1;
                    }else{
                       BoardPtr->MoveWhiteCounter = BoardPtr->MoveWhiteCounter + 1 ;
                    }
                    BoardPtr->changeRound();
                }
             }
       }
   }
}

bool Pawn::hasLadyStrike()
{
 int i,j; // iteratory znakowe
 int k; // iterator setów
 int x,y; // iteratory sprawdzające pola
 int counter = 0; // licznik pionków po drodze;
  i=-1;
  while(i<2){
    j=-1;
    while(j<2){
        counter= 0;
        x= LogicX+i;
        while(x<10 && x>-1){
         y = LogicY+j;
         while(y<10 && y>-1){
           if((LogicX+LogicY==x+y)||(LogicY-LogicX==y-x)){
              if(!BoardPtr->BoardFieldAcces[x][y]){
                if(Color=='b'){
                  for(k=0;k<20;k++){
                      if(BoardPtr->BlackSet[k].LogicX == x && BoardPtr->BlackSet[k].LogicY == y){counter=counter+1;}
                  }
                  for(k=0;k<20;k++){
                   if(BoardPtr->WhiteSet[k].LogicX == x && BoardPtr->WhiteSet[k].LogicY == y){
                    if((x+i>-1)&&(x+i<10)&&(y+j>-1)&&(y+j<10)){
                     if(BoardPtr->BoardFieldAcces[x+i][y+j]){
                       if(counter == 0){
                         return true;
                       }
                     }else{
                       counter = counter+1;
                     }
                    }
                   }
                  }
                }else{
                    for(k=0;k<20;k++){
                        if(BoardPtr->WhiteSet[k].LogicX == x && BoardPtr->WhiteSet[k].LogicY == y){counter=counter+1;}
                    }
                    for(k=0;k<20;k++){
                     if(BoardPtr->BlackSet[k].LogicX == x && BoardPtr->BlackSet[k].LogicY == y){
                      if((x+i>-1)&&(x+i<10)&&(y+j>-1)&&(y+j<10)){
                       if(BoardPtr->BoardFieldAcces[x+i][y+j]){
                         if(counter == 0){
                           return true;
                         }
                       }else{
                           counter = counter+1;
                       }
                      }
                     }
                    }
                }
              }
           }
          y=y+j;
         }
         x=x+i;
        }
     j=j+2;
    }
   i=i+2;
  }
  return false;
}
// sprawdza czy pionek ma dostępne ruchy
bool Pawn::hasMove(){
 int x,y;
 if(Status){
   if(hasLadyStrike()){// sprawdzamy czy damka ma bicie, jeżeli tak oznacza to, że jakiś ruch jest dostępny
     return true;
   }
 }else{
     if(hasPawnStrike()){// sprawdzamy czy pionek ma bicie, jeżeli tak oznacza to, że jakiś ruch jest dostępny
       return true;
     }
 }
 x=-1;
 while(x<2){
  if((x+LogicX<10) && (x+LogicX>-1)){
   y=-1;
   if(!Status){
     if(Color=='b'){y=1;}else{y=-1;}
   }
   while(y<2){
     if((y+LogicY<10) && (y+LogicY>-1)){
       if(BoardPtr->BoardFieldAcces[LogicX+x][LogicY+y]){
        return true;
       }
     }
     if(Status){y=y+2;}else{y=y+3;}
   }
  }
  x=x+2;
 }
 return false;
}
// funkcja sprawdza czy na planszy pojawiły sie damki
void Pawn::checkIfLady()
{
     if(!Status){
     if(Color == 'b'){
       if(LogicY==9){
         Status=true;
         this->setPixmap(*this->BoardPtr->BlackLadyImg);
       }
     }else{
       if(LogicY==0){
         Status=true;
         this->setPixmap(*this->BoardPtr->WhiteLadyImg);
       }
     }
    }
}


