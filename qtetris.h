#ifndef QTETRIS_H
#define QTETRIS_H


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
	UI::QTetris *ui;
};


#endif
