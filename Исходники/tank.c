int printCDBar(tankClass tank) {
	int barWidth=tank.width+10;
	int barHeight=10;
	int barRelHeight=10;
	int width;
	int barX,barY;
	int color;
	int delta;
	double percent;
	
	barX=tank.x;
	barY=tank.y+tank.width/2+barRelHeight;
	percent=(double)(MAXCD-tank.fireCD)/MAXCD;
	width=percent*barWidth;
	color=255*percent;
	delta=(128-abs(128-color))/2;
	beginPaint();
	setBrushColor(RGB(255-color+delta,color+delta,0));
	rectangle(barX-barWidth/2,barY-barHeight/2,barX-barWidth/2+width,barY+barHeight/2);
	endPaint();
}