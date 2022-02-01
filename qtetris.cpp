
#include <qtetris.h>
#include <ui_qtetris.h>

#include <QApplication>


QTetris::QTetris(QWidget *parent) :
	QWidget(parent),
	ui(new UI::QTetris()),
	currPiece(nullptr),
	nextPiece(nullptr),
	boardWidth(10),
	boardHeight(20),
	score(0),
	lines(0),
	level(0),
	nextLevelLines(20)
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


void QTetris::getNextPiece() {
	mainScene->removeItem(currPiece);
	nextPieceScene->removeItem(nextPiece);

	currPiece = nextPiece;
	currPiece->moveTo(boardWidth/2, 0);
	mainScene->addItem(currPiece);
	
	nextPiece = Piece::newPiece(2, 2);
	nextPieceScene->addItem(nextPiece);

	mainScene->update();
	nextPieceScene->update();
}


void QTetris::moveLeft() {
	currPiece->moveBy(-1, 0);
	if(currPiece->left < 0 || !mainScene->collidingItems(currPiece).isEmpty())
		currPiece->moveBy(1, 0);
		
	mainScene->update();
}


void QTetris::moveRight() {
	currPiece->moveBy(1, 0);
	if(currPiece->right > boardWidth || !mainScene->collidingItems(currPiece).isEmpty())
		currPiece->moveBy(-1, 0);
		
	mainScene->update();
}


void QTetris::moveDown() {
	currPiece->moveBy(0, 1);		
	if(currPiece->bottom > boardHeight || !mainScene->collidingItems(currPiece).isEmpty()) {
		currPiece->moveBy(0, -1);
		touchdown();
	}
		
	mainScene->update();
}


void QTetris::drop() {
	while(currPiece->bottom <= boardHeight && mainScene->collidingItems(currPiece).isEmpty())
		currPiece->moveBy(0, 1);
	currPiece->moveBy(0, -1);
	mainScene->update();
}


void QTetris::rotate() {
	currPiece->rotateRight();
	if(currPiece->left<0 || currPiece->right>boardWidth || currPiece->bottom>boardHeight || !mainScene->collidingItems(currPiece).isEmpty())
		currPiece->rotateLeft();
		
	mainScene->update();
}


void QTetris::touchdown() {
	currPiece->addBlocksToScene(mainScene);	
	
	//check for completed lines
	QGraphicsLineItem line(0, 0, boardWidth*Piece::blockSize, 0);
	int removedLines = 0;
	for(int row=currPiece->bottom; row>currPiece->top; row--) {
		line.setY((row - 0.5)*Piece::blockSize);
		auto blocksOnLine = mainScene->collidingItems(&line);
		if(blocksOnLine.size() == boardWidth) {
			for(auto block : blocksOnLine) 
				mainScene->removeItem(block);
			++removedLines;
		}
		else if(removedLines > 0) {
			for(auto block : blocksOnLine) 
				block->moveBy(0, removedLines*Piece::blockSize);
		}
	}
	for(int row=currPiece->top; row>0; --row) {
		line.setY((row - 0.5)*Piece::blockSize);
		auto blocksOnLine = mainScene->collidingItems(&line);
		for(auto block : blocksOnLine) 
			block->moveBy(0, removedLines*Piece::blockSize);
	}
	
	// update score, lines, level
	if(removedLines > 0) {
		lines += removedLines;
		score += 5*(1 + level)*(1 + removedLines);
		if(lines >= nextLevelLines) {
			++level;
			updateTimer->setInterval(5000/(5 + level));
			nextLevelLines += 20;
		}
		ui->scoreLCD->display(score);
		ui->linesLCD->display(lines);
		ui->levelLCD->display(level);
	}
	
	// only way to clear removed blocks from view ???
	mainScene->setSceneRect(mainScene->sceneRect().adjusted(1,0,0,0));
	mainScene->setSceneRect(mainScene->sceneRect().adjusted(-1,0,0,0));
	
	
	getNextPiece();
}
