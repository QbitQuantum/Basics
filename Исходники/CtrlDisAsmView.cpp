int CtrlDisAsmView::yToAddress(int y)
{
	int ydiff=y-rect.bottom/2-rowHeight/2;
	ydiff=(int)(floorf((float)ydiff / (float)rowHeight))+1;
	return curAddress + ydiff * align;
}