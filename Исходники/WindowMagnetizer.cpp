//Draws a rectangle on the given DC with a NOT ROP2
void WindowMagnetizer::DrawNotRectangle(HDC hDC, CONST LPRECT rect)
{
	int oldROP=SetROP2(hDC,R2_NOT);
	BEGIN_SELOBJ(hDC,GetStockPen(BLACK_PEN),pen);
	BEGIN_SELOBJ(hDC,GetStockBrush(NULL_BRUSH),brush);
	Rectangle(hDC,rect->left,rect->top,rect->right,rect->bottom);
	END_SELOBJ(hDC,brush);
	END_SELOBJ(hDC,pen);
	SetROP2(hDC,oldROP);
};