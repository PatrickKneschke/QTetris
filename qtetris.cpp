
#include <qtetris.h>
#include <ui_qtetris.h>


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
	
	initBoard();
}


QTetris::~QTetris() {
	delete ui;
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
