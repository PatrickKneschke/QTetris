
#include <QApplication>
#include "qtetris.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	QTetris game;
	game.show();
	
	return app.exec();
}
