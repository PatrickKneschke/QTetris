
#include <qtetris.h>
#include <ui_qtetris.h>


QTetris::QTetris(QWidget *parent) :
	QWidget(parent),
	ui(new UI::QTetris())
{
	setMinimumSize(720, 920);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	ui->setupUI(this);
}


QTetris::~QTetris() {
	delete ui;
}
