
#include "piece.h"


const int Piece::shapePosTable[7][4][2]= {
	// O_SHAPE
	{{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
	// I_SHAPE
	{{ 0, -1}, {0,  0}, { 0, 1}, {0, 2}},
	// S_SHAPE
	{{-1,  1}, {0,  1}, { 0, 0}, {1, 0}},
	// Z_SHAPE
	{{-1,  0}, {0,  0}, { 0, 1}, {1, 1}},
	// T_SHAPE
	{{-1,  0}, {0,  0}, { 1, 0}, {0, 1}},
	// L_SHAPE
	{{ 0, -1}, {0,  0}, { 0, 1}, {1, 1}},
	// J_SHAPE
	{{ 0, -1}, {0,  0}, {-1, 1}, {0, 1}}
};

const QColor Piece::colorTable[6]  = {
	QColor(230, 25, 25), QColor(25, 230, 25), QColor(25, 25, 230), 
	QColor(230, 230, 25), QColor(230, 25, 230), QColor(25, 230, 230)
};

int Piece::blockSize = 50;


Piece::Piece(Shape s, QColor c) : 
	color(c),
	pieceShape(s) 
{
	int left = INT_MAX, right = INT_MIN, top = INT_MAX, bottom = INT_MIN;
	for(int i=0; i<4; i++) {
		blockPos[i][0] = shapePosTable[pieceShape][i][0]*blockSize;
		blockPos[i][1] = shapePosTable[pieceShape][i][1]*blockSize;
		left 	= qMin(left,   blockPos[i][0]);
		top  	= qMin(top,    blockPos[i][1]);
		right 	= qMax(right,  blockPos[i][0] + blockSize);
		bottom  = qMax(bottom, blockPos[i][1] + blockSize);
	}
	box.setRect(left, top, right-left, bottom-top);
}


QRectF Piece::boundingRect() const {
	return box;
}


QPainterPath Piece::shape() const {
	QPainterPath path;
	for(int i=0; i<4; i++) {
		path.addRect(blockPos[i][0] + 1, blockPos[i][1] + 1, blockSize - 2, blockSize - 2);
	}
	return path;
}


void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {	
	painter->setBrush(color);
	for(int i=0; i<4; i++)
		painter->drawRect(blockPos[i][0], blockPos[i][1], blockSize, blockSize);
}


Piece* Piece::newPiece() {
	return new Piece(Shape(QRandomGenerator::global()->bounded(7)), colorTable[QRandomGenerator::global()->bounded(6)]);
}


void Piece::addBlocksToScene(QGraphicsScene *scene) {
	for(int i=0; i<4; i++)
		scene->addRect(x() + blockPos[i][0], y() + blockPos[i][1], blockSize, blockSize, QPen(), QBrush(color));
}


void Piece::rotateLeft() {
	if(pieceShape == O_SHAPE)
		return;
		
	int temp;
	for(int i=0; i<4; i++) {
		temp = blockPos[i][0];
		blockPos[i][0] = blockPos[i][1];
		blockPos[i][1] = -temp;
	}
	box.setRect(box.top(), -(box.right()-blockSize), box.height(), box.width());	
}


void Piece::rotateRight() {
	if(pieceShape == O_SHAPE)
		return;
		
	int temp;
	for(int i=0; i<4; i++) {
		temp = blockPos[i][0];
		blockPos[i][0] = -blockPos[i][1];
		blockPos[i][1] = temp;
	}
	box.setRect(-(box.bottom() - blockSize), box.left(), box.height(), box.width());
}
