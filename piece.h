#ifndef PIECE_H
#define PIECE_H


#include <QtCore>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>


class Piece : public QGraphicsItem {

	enum Shape {O_SHAPE, I_SHAPE, S_SHAPE, Z_SHAPE, T_SHAPE, L_SHAPE, J_SHAPE};

	static const int shapePosTable[7][4][2];	
	static const QColor colorTable[6];

public:
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;	
	
	static Piece* newPiece();	
	
	void addBlocksToScene(QGraphicsScene *scene);
	void rotateLeft();
	void rotateRight();	
	
	static int blockSize;
	QColor color;
	QRectF box;
		
private:
	Piece(Shape s, QColor c);	
	int blockPos[4][2];
	Shape pieceShape;
};


#endif
