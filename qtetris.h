#ifndef QTETRIS_H
#define QTETRIS_H


#include "piece.h"
#include <QGraphicsScene>
#include <QWidget>


namespace UI {
	class QTetris;
}

class QTetris : public QWidget {
	Q_OBJECT
public:
	QTetris(QWidget *parent=nullptr);
	~QTetris();

private:
	void initBoard();


	UI::QTetris *ui;
	QGraphicsScene *mainScene, *nextPieceScene;
	Piece *currPiece, *nextPiece;
	
	int boardWidth, boardHeight;
				   
	
};


#endif
