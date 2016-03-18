#include "board.h"
Board::Board(QWidget *parent):
    QGraphicsView(parent)
{
  // inicjalizacja obrazów
    MoveBlackCounter = 0;
    MoveWhiteCounter = 0;
    Path =NULL;
    WinnerRect = NULL;
    BoardImg = new QPixmap(":/board.png");
    BlackPawnImg = new QPixmap(":/black_pawn.png");
    WhitePawnImg = new QPixmap(":/white_pawn.png");
    WhiteLadyImg =  new QPixmap(":/white_lady.png");
    BlackLadyImg = new QPixmap(":/black_lady.png");
    Scene = new QGraphicsScene(this); // inicjalizacja sceny warcabów
    Scene->addPixmap(*BoardImg); // dodanie planszy do sceny
    WhiteSet= new Pawn[20];
    BlackSet= new Pawn[20];
    initGame(); // inicjalizacja gry;
    setScene(Scene); // dodajemy scene do Widoku graficznego
    show(); // pokazujemy
}

Board::~Board()
{
    if(Path!=NULL){
      Scene->removeItem(Path);
      delete Path;
    }
    if(WinnerRect!=NULL){
      Scene->removeItem(WinnerRect);
      delete WinnerRect;
    }
    delete [] BlackSet;
    delete [] WhiteSet;
    delete BoardImg;
    delete WhitePawnImg;
    delete BlackPawnImg;
    delete BlackLadyImg;
    delete WhiteLadyImg;
    delete Scene;

}

void Board::initGame()
{
 if(Path != NULL){
   Scene->removeItem(Path);
   delete Path;
   Path = NULL;
 }
 if(WinnerRect != NULL){
   Scene->removeItem(WinnerRect);
   delete WinnerRect;
   WinnerRect = NULL;
 }
 Round='w';
 emit changeLabel();
 int i = 0;
 int j = 0;
 for(i=0;i<10;i++){
  for(j=0;j<10;j++){
     BoardFieldAcces[i][j]=true;
   }
 }
 // inicjalizacja pionków
 for(i = 0; i<20 ; i++){
     BlackSet[i].Color = 'b';
     BlackSet[i].ID = i;
     WhiteSet[i].ID = i;
     WhiteSet[i].BoardPtr=this;
     BlackSet[i].BoardPtr=this;
     if(BlackSet[i].LogicX==-10){
        Scene->addItem(&BlackSet[i]);
     }
     if(WhiteSet[i].LogicX==-10){
        Scene->addItem(&WhiteSet[i]);
     }
     BlackSet[i].Status=false;
     BlackSet[i].setPixmap(*BlackPawnImg);
     BlackSet[i].setFlag(QGraphicsItem::ItemIsMovable,false);
     WhiteSet[i].setPixmap(*WhitePawnImg);
     WhiteSet[i].Status=false;
     WhiteSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);

  }

 //incjalizacja mapy planszy
 for(i=0;i<10;i++){
     BoardMap[i]=(60*i+17);
 }
 // rozstawienie pionków na planszy;
 for(i=0;i<20;i++){
        if(i<5){
          BlackSet[i].setPos((qreal)BoardMap[2*i+1],(qreal)BoardMap[0]);
          BlackSet[i].LogicX = (2*i+1);
          BlackSet[i].LogicY =0;
          BoardFieldAcces[BlackSet[i].LogicX][0]=false;
          WhiteSet[i].setPos((qreal)BoardMap[2*i],(qreal)BoardMap[9]);
          WhiteSet[i].LogicX = 2*i;
          WhiteSet[i].LogicY = 9;
          BoardFieldAcces[WhiteSet[i].LogicX][9]=false;
        }else
        if( (i>4) && (i<10) ){
          BlackSet[i].setPos((qreal)BoardMap[(2*i)%10],(qreal)BoardMap[1]);
          BlackSet[i].LogicX = (2*i)%10;
          BlackSet[i].LogicY =1;
          BoardFieldAcces[BlackSet[i].LogicX][1]=false;
          WhiteSet[i].setPos((qreal)BoardMap[(2*i+1)%10],(qreal)BoardMap[8]);
          WhiteSet[i].LogicX = (2*i+1)%10;
          WhiteSet[i].LogicY = 8;
          BoardFieldAcces[WhiteSet[i].LogicX][8]=false;
        }else
        if( (i>9) && (i<15) ){
          BlackSet[i].setPos((qreal)BoardMap[(2*i+1)%10],(qreal)BoardMap[2]);
          BlackSet[i].LogicX = (2*i+1)%10;
          BlackSet[i].LogicY =2;
          BoardFieldAcces[BlackSet[i].LogicX][2]=false;
          WhiteSet[i].setPos((qreal)BoardMap[(2*i)%10],(qreal)BoardMap[7]);
          WhiteSet[i].LogicX = (2*i)%10;
          WhiteSet[i].LogicY = 7;
          BoardFieldAcces[WhiteSet[i].LogicX][7]=false;
        }else
        if(i>14){
          BlackSet[i].setPos((qreal)BoardMap[(2*i)%10],(qreal)BoardMap[3]);
          BlackSet[i].LogicX = (2*i)%10;
          BlackSet[i].LogicY =3;
          BoardFieldAcces[BlackSet[i].LogicX][3]=false;
          WhiteSet[i].setPos((qreal)BoardMap[(2*i+1)%10],(qreal)BoardMap[6]);
          WhiteSet[i].LogicX = (2*i+1)%10;
          WhiteSet[i].LogicY = 6;
          BoardFieldAcces[WhiteSet[i].LogicX][6]=false;
        }
  }
}

// blokuje możliwość poruszania pionkami wybranego koloru
void Board::lockSet(const char color)
{
    if(color=='b')
    {
        for(int i = 0; i<20 ; i++)
        {
            BlackSet[i].setFlag(QGraphicsItem::ItemIsMovable,false);
        }
    }
    else
    {
        for(int i = 0; i<20 ; i++)
        {
            WhiteSet[i].setFlag(QGraphicsItem::ItemIsMovable,false);
        }
    }
}

// odblokowuje możliwość poruszania pionkami wybranego koloru z uwzględnieniem pierwszeństwa bicia
void Board::unlockSet(const char color)
{
    bool strikeflag = false; // flaga dostępnych bić
    if(color=='b')
    {
        for(int i = 0; i<20 ; i++)
        {
          if(BlackSet[i].Status){
            if(BlackSet[i].hasLadyStrike()){
             BlackSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);
             strikeflag=true;
            }
           }else{
             if(BlackSet[i].hasPawnStrike()){
               BlackSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);
               strikeflag=true;
              }
           }
        }
        if(!strikeflag){
            for(int i = 0; i<20; i++)
            {
              BlackSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);
            }
        }
    }
    else
    {
        for(int i = 0; i<20 ; i++)
        {
          if(WhiteSet[i].Status){
            if(WhiteSet[i].hasLadyStrike()){
             WhiteSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);
             strikeflag=true;
            }
           }else{
             if(WhiteSet[i].hasPawnStrike()){
               WhiteSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);
               strikeflag=true;
              }
           }
        }
        if(!strikeflag){
            for(int i = 0; i<20; i++)
            {
              WhiteSet[i].setFlag(QGraphicsItem::ItemIsMovable,true);
            }
        }
    }

}

void Board::changeRound() // funkcja zmieniająca rundę dla drugiego gracza
{
 int i = 0;
 bool ismove = false; // flaga wskazująca czy jest ruch dla pionka
 lockSet(Round);
  if((MoveWhiteCounter < 15) && (MoveBlackCounter<15)){
     if(Round=='b'){
         Round='w';
         for(i=0;i<20;i++){
          if(WhiteSet[i].hasMove()){
            ismove = true ;
            break;
          }
         }
         if(!ismove){
          setWinner('b');
          return;
         }
     }else{
         Round='b';
         for(i=0;i<20;i++){
          if(BlackSet[i].hasMove()){
            ismove = true ;
            break;
          }
         }
         if(!ismove){
          setWinner('w');
          return;
         }
     }
   }else{
    setWinner('d');
    return;
   }
  unlockSet(Round);
  emit changeLabel();
}


void Board::setWinner(char color)
{
  lockSet('w');
  lockSet('b');
  QPen pen;
  QFont font;
  QString str =  "Wygrywa gracz : ";
  QPainterPath path;
  QRect rect;
  font.setPixelSize(20);
  font.setBold(false);
  if(color=='b'){
    str = str + QString::fromUtf8("Czarny");
  }else if(color == 'd'){
    str = QString::fromUtf8("Gra Zakończona Remisem");
  }else{
    str = str + QString::fromUtf8("Biały");
  }
  path.addText(200, 300, font,str);
  WinnerRect = Scene->addRect(150,200,300,200,pen,Qt::white);
  Path = Scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));
  WinnerRect->setZValue(10);
  Path->setZValue(11);

}

void Board::wheelEvent ( QWheelEvent * event )
{

}

