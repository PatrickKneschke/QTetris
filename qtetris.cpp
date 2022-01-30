
#include <qtetris.h>
#include <ui_qtetris.h>

#include <QApplication>


QTetris::QTetris(QWidget *parent) :
	QWidget(parent),
	ui(new UI::QTetris()),
	currPiece(nullptr),
	nextPiece(nullptr),
	boardWidth(10),
	boardHeight(20)
{
	ui->setupUI(this);
	setMinimumSize(16*Piece::blockSize, 22*Piece::blockSize);
	setMaximumSize(16*Piece::blockSize, 22*Piece::blockSize);
	setFocus();
	
	initBoard();
	
	updateTimer = new QTimer();
	connect(updateTimer, &QTimer::timeout, this, &QTetris::moveDown);
	updateTimer->start(1000);
}


QTetris::~QTetris() {
	delete ui;
}


void QTetris::keyPressEvent(QKeyEvent *event) {
	switch(event->key()) {
		case Qt::Key_Left :
			moveLeft();
			break;
		case Qt::Key_Right :
			moveRight();
			break;
		case Qt::Key_Down :
			drop();
			break;
		case Qt::Key_Up :
			rotate();
			break;
	}
}


void QTetris::initBoard() {
	mainScene = new QGraphicsScene(0, 0, boardWidth*Piece::blockSize, boardHeight*Piece::blockSize, this);
	ui->mainView->setScene(mainScene);
	ui->mainView->resize(mainScene->width(), mainScene->height());
	
	nextPieceScene = new QGraphicsScene(0, 0, 4*Piece::blockSize, 4*Piece::blockSize, this);
	ui->nextPieceView->setScene(nextPieceScene);
	ui->nextPieceView->resize(nextPieceScene->width(), nextPieceScene->height());
	
	
	currPiece = Piece::newPiece(boardWidth/2, 0);
	mainScene->addItem(currPiece);
	
	nextPiece = Piece::newPiece(2, 2);
	nextPieceScene->addItem(nextPiece);
}


void QTetris::moveLeft() {
	if(currPiece->left > 0)
		currPiece->move(-1, 0);
	mainScene->update(0, 0, boardWidth*Piece::blockSize, boardHeight*Piece::blockSize);
}


void QTetris::moveRight() {
	if(currPiece->right < boardWidth)
		currPiece->move(1, 0);	
	mainScene->update(0, 0, boardWidth*Piece::blockSize, boardHeight*Piece::blockSize);
}


void QTetris::moveDown() {
	// TODO
	if(currPiece->bottom < boardHeight)
		currPiece->move(0, 1);
	mainScene->update(0, 0, boardWidth*Piece::blockSize, boardHeight*Piece::blockSize);
}


void QTetris::drop() {
	//TODO
	currPiece->move(0, boardHeight-currPiece->bottom);
	mainScene->update(0, 0, boardWidth*Piece::blockSize, boardHeight*Piece::blockSize);
}


void QTetris::rotate() {
	//TODO
	currPiece->rotate();
	mainScene->update(0, 0, boardWidth*Piece::blockSize, boardHeight*Piece::blockSize);
}
