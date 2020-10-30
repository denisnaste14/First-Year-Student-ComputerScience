#include "CosRDOnlyGUI.h"
#include <time.h>

void CosRDOnlyGUI::paintEvent(QPaintEvent* ev){
	srand(time(NULL));
	QPainter p{ this };
	int cate_sunt = cos.toti_din_cos().size();
	for (int i = 0; i < cate_sunt; i++) {
		p.drawEllipse(rand() % 350, rand() % 350, rand() % 80, rand() % 100);
	}
}

void CosRDOnlyGUI::update(){
	repaint();
}