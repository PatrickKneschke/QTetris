#ifndef PIECE_H
#define PIECE_H


#include <QtCore>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>


class Piece : public QGraphicsItem {

	enum Shape {O_SHAPE, I_SHAPE, S_SHAPE, Z_SHAPE, T_SHAPE, L_SHAPE, J_SHAPE};

	static const int shapePosTable[7][4][2];	
	static const QColor colorTable[6];

public:
	static Piece* newPiece(const int &x, const int &y);	
	
	void move(const int &dx, const int &dy);
	void rotate();	

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;	
	
	static int blockSize;	
	int blockPos[4][2];
	int left, right, top, bottom;
	
private:
	Piece(const int &x, const int &y, Shape s);
	
	Shape shape;
	QColor color;
};


#endif
