#ifndef UI_QTETRIS_H
#define UI_QTETRIS_H


#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>


namespace UI {

class QTetris {
public:
	void setupUI(QWidget *parent) {
		mainLayout 		= new QGridLayout();
		
		mainView 		= new QGraphicsView(parent);
		nextPieceView 	= new QGraphicsView(parent);
		
		titleLabel 		= new QLabel("QTETRIS", parent);
		titleLabel->setAlignment(Qt::AlignCenter);
		titleLabel->setFont(QFont("Arial", 14, QFont::ExtraBold, true));
		nextPieceLabel 	= new QLabel("Next", parent);
		nextPieceLabel->setAlignment(Qt::AlignCenter);
		nextPieceLabel->setFont(QFont("Arial", 12, QFont::Bold));
		scoreLabel 		= new QLabel("Score", parent);
		scoreLabel->setAlignment(Qt::AlignCenter);
		scoreLabel->setFont(QFont("Arial", 12, QFont::Bold));
		linesLabel 		= new QLabel("Lines", parent);
		linesLabel->setAlignment(Qt::AlignCenter);
		linesLabel->setFont(QFont("Arial", 12, QFont::Bold));
		levelLabel 		= new QLabel("Level", parent);
		levelLabel->setAlignment(Qt::AlignCenter);
		levelLabel->setFont(QFont("Arial", 12, QFont::Bold));
		
		scoreLCD 		= new QLCDNumber(5, parent);
		linesLCD 		= new QLCDNumber(5, parent);
		levelLCD 		= new QLCDNumber(2, parent);
		
		parent->setLayout(mainLayout);
				
		mainLayout->addWidget(titleLabel, 		0, 0,  1, 6);
		mainLayout->addWidget(mainView, 		1, 0, 12, 6);
		mainLayout->addWidget(nextPieceLabel,	1, 6,  1, 3);
		mainLayout->addWidget(nextPieceView,	2, 6,  3, 3);
		mainLayout->addWidget(scoreLabel, 		6, 6,  1, 3);
		mainLayout->addWidget(scoreLCD, 		7, 6,  1, 3);
		mainLayout->addWidget(linesLabel, 		8, 6,  1, 3);
		mainLayout->addWidget(linesLCD, 		9, 6,  1, 3);
		mainLayout->addWidget(levelLabel, 	   10, 6,  1, 3);
		mainLayout->addWidget(levelLCD, 	   11, 6,  1, 3);
	}
	
	
	QGridLayout 	*mainLayout;
	QGraphicsView	*mainView,
					*nextPieceView;
	QLabel			*titleLabel,
					*nextPieceLabel,
					*scoreLabel,
					*linesLabel,
					*levelLabel;
	QLCDNumber		*scoreLCD,
					*linesLCD,
					*levelLCD;
	
};

} //UI


#endif
