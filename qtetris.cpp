
#include <qtetris.h>
#include <ui_qtetris.h>


QTetris::QTetris(QWidget *parent) :
	QWIdget(parent),
	ui(new UI::QTetris())
{
	ui->setupUI();
}


QTetris::~QTetris() {
	delete ui;
}
