void WorldUIView::drawBorder(){
	color(Color(0, 0, 0));
	lineWidth(5);
	drawStrokedRect(Rectf(rect.x, rect.y, rect.xEnd, rect.yEnd));
}	