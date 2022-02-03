
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
	unit(Piece::blockSize),
	score(0),
	lines(0),
	level(0),
	nextLevelLines(20),
	gameover(false)
{
	ui->setupUI(this);
	setMinimumSize(16*unit, 22*unit);
	setMaximumSize(16*unit, 22*unit);
	setFocus();
	
	setupSound();	
	initBoard();
	
	updateTimer = new QTimer();
	connect(updateTimer, &QTimer::timeout, this, &QTetris::moveDown);
	updateTimer->start(1000);
}


QTetris::~QTetris() {
	delete ui;
}


void QTetris::keyPressEvent(QKeyEvent *event) {
	if(gameover)
		return;
		
	switch(event->key()) {
		case Qt::Key_Left :
			blockMoveSound->play();
			moveLeft();
			break;
		case Qt::Key_Right :
			blockMoveSound->play();
			moveRight();
			break;
		case Qt::Key_Down :
			blockMoveSound->play();
			drop();
			break;
		case Qt::Key_Up :
			blockRotateSound->play();
			rotate();
			break;
		default:
			QWidget::keyPressEvent(event);
			break;
	}
}


void QTetris::setupSound() {
	blockMoveSound = new QSound("block_move.wav", this);
	blockRotateSound = new QSound("block_rotate.wav", this);
	blockTouchdownSound = new QSound("block_touchdown.wav", this);
	lineClearSound = new QSound("line_clear.wav", this);
	levelUpSound = new QSound("level_up.wav", this);
	gameoverSound = new QSound("gameover.wav", this);
}


void QTetris::initBoard() {
	mainScene = new QGraphicsScene(0, 0, boardWidth*unit, boardHeight*unit, this);
	ui->mainView->setScene(mainScene);
	ui->mainView->resize(mainScene->width(), mainScene->height());
	
	nextPieceScene = new QGraphicsScene(0, 0, 4*unit, 4*unit, this);
	ui->nextPieceView->setScene(nextPieceScene);
	ui->nextPieceView->resize(nextPieceScene->width(), nextPieceScene->height());	
	
	currPiece = Piece::newPiece();
	mainScene->addItem(currPiece);
	currPiece->setPos(boardWidth*unit/2, 0);
	
	nextPiece = Piece::newPiece();
	nextPieceScene->addItem(nextPiece);
	nextPiece->setPos(unit, unit);
}


void QTetris::getNextPiece() {
	nextPieceScene->removeItem(nextPiece);

	currPiece = nextPiece;
	mainScene->addItem(currPiece);
	currPiece->setPos(boardWidth*unit/2, 0);
	
	nextPiece = Piece::newPiece();
	nextPieceScene->addItem(nextPiece);
	nextPiece->setPos(unit, unit);
}


void QTetris::handleGameover() {
	gameover = true;
	gameoverSound->play();
	updateTimer->stop();
}


void QTetris::moveLeft() {
	currPiece->moveBy(-unit, 0);
	if(currPiece->x() + currPiece->box.left() < 0 || !mainScene->collidingItems(currPiece).isEmpty())
		currPiece->moveBy(unit, 0);
}


void QTetris::moveRight() {
	currPiece->moveBy(unit, 0);
	if(currPiece->x() + currPiece->box.right() > boardWidth*unit || !mainScene->collidingItems(currPiece).isEmpty())
		currPiece->moveBy(-unit, 0);
}


void QTetris::moveDown() {
	blockMoveSound->play();
	
	currPiece->moveBy(0, unit);		
	if(currPiece->y() + currPiece->box.bottom() > boardHeight*unit || !mainScene->collidingItems(currPiece).isEmpty()) {
		currPiece->moveBy(0, -unit);
		touchdown();
	}
}


void QTetris::drop() {
	while(currPiece->y() + currPiece->box.bottom() <= boardHeight*unit && mainScene->collidingItems(currPiece).isEmpty())
		currPiece->moveBy(0, unit);
	currPiece->moveBy(0, -unit);
}


void QTetris::rotate() {
	currPiece->rotateRight();
	if(currPiece->x() + currPiece->box.left() < 0 || 
	   currPiece->x() + currPiece->box.right() > boardWidth*unit || 
	   currPiece->y() + currPiece->box.bottom() > boardHeight*unit || 
	   !mainScene->collidingItems(currPiece).isEmpty())
		currPiece->rotateLeft();
	mainScene->update();
}


void QTetris::touchdown() {
	// check for gameover
	if(currPiece->y() + currPiece->box.top() < 0) {
		handleGameover();
		return;
	}

	blockTouchdownSound->play();
	currPiece->addBlocksToScene(mainScene);
	mainScene->removeItem(currPiece);
	
	//check for completed lines
	QGraphicsLineItem line(0, 0, boardWidth*unit, 0);
	int removedLines = 0;
	for(int row = currPiece->y() + currPiece->box.bottom(); row>currPiece->y() + currPiece->box.top(); row-=unit) {
		line.setY(row - unit/2);		
		auto blocksOnLine = mainScene->collidingItems(&line);
		if(blocksOnLine.size() == boardWidth) {
			for(auto block : blocksOnLine) 
				mainScene->removeItem(block);
			++removedLines;
		}
		else if(removedLines > 0) {
			for(auto block : blocksOnLine) 
				block->moveBy(0, removedLines*unit);
		}
	}
	for(int row=currPiece->y() + currPiece->box.top(); row>0; row-=unit) {
		line.setY(row - unit/2);
		auto blocksOnLine = mainScene->collidingItems(&line);
		for(auto block : blocksOnLine) 
			block->moveBy(0, removedLines*unit);
	}
	
	// update score, lines, level
	if(removedLines > 0) {
		lineClearSound->play();
		lines += removedLines;
		score += 5*(1 + level)*(1 + removedLines);
		if(lines >= nextLevelLines) {
			levelUpSound->play();
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
