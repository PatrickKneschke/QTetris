
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


Piece::Piece(const int &x, const int &y, Shape s) : 
	shape(s), 
	left(INT_MAX), right(INT_MIN), top(INT_MAX), bottom(INT_MIN)
{
	for(int i=0; i<4; i++) {
		blockPos[i][0] = x + shapePosTable[shape][i][0];
		blockPos[i][1] = y + shapePosTable[shape][i][1];
		left   = qMin(left,   blockPos[i][0]);
		right  = qMax(right,  blockPos[i][0]+1);
		top    = qMin(top,    blockPos[i][1]);
		bottom = qMax(bottom, blockPos[i][1]+1);
	}
}


QRectF Piece::boundingRect() const {
	return QRectF(left*blockSize, top*blockSize, (right-left)*blockSize, (bottom-top)*blockSize);
}


void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawRect(boundingRect());

	painter->setBrush(color);
	for(int i=0; i<4; i++)
		painter->drawRect(blockPos[i][0]*blockSize, blockPos[i][1]*blockSize, blockSize, blockSize);
		

}


Piece* Piece::newPiece(const int &x, const int &y) {
	Piece *piece = new Piece(x, y, Shape(QRandomGenerator::global()->bounded(7)));
	piece->color = colorTable[QRandomGenerator::global()->bounded(6)];
	return piece;
}


void Piece::move(const int &dx, const int &dy) {
	for(int i=0; i<4; i++) {
		blockPos[i][0] += dx;
		blockPos[i][1] += dy;
	}
	left   += dx;
	right  += dx;
	top    += dy;
	bottom += dy;
}


void Piece::rotate() {
	if(shape == O_SHAPE)
		return;

	int temp;
	for(int i=0; i<4; i++) {
		temp = blockPos[i][0];
		blockPos[i][0] = -blockPos[i][1];
		blockPos[i][1] = temp;
	}
	temp   = left;
	left   = -bottom;
	bottom = right;
	right  = -top;
	top    = temp;
}
