#ifndef QTETRIS_H
#define QTETRIS_H


#include "piece.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QSound>
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
	
	void setupSound();
	void initBoard();
	void getNextPiece();
	void handleGameover();
	
	void moveLeft();
	void moveRight();
	void moveDown();
	void drop();
	void rotate();
	void touchdown();
	

	UI::QTetris *ui;
	QGraphicsScene *mainScene, *nextPieceScene;
	QTimer *updateTimer;
	
	Piece *currPiece, *nextPiece;
	int boardWidth, boardHeight, unit;
	int score, lines, level, nextLevelLines;
	bool gameover;
	
	QSound *blockMoveSound, 
		   *blockRotateSound, 
		   *blockTouchdownSound,
		   *lineClearSound, 
		   *levelUpSound,
		   *gameoverSound;
	
};


#endif
