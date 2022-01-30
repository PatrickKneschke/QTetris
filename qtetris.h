#ifndef QTETRIS_H
#define QTETRIS_H


#include "piece.h"
#include <QGraphicsScene>
#include <QKeyEvent>
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
	void keyPressEvent(QKeyEvent *event) override;

	void initBoard();
	void getNextPiece();
	
	void moveLeft();
	void moveRight();
	void moveDown();
	void drop();
	void rotate();
	

	UI::QTetris *ui;
	QGraphicsScene *mainScene, *nextPieceScene;
	QTimer *updateTimer;
	Piece *currPiece, *nextPiece;
	
	int boardWidth, boardHeight;
				   
	
};


#endif
