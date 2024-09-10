//Draws the cursor on the DC
void PrecisionCursor::drawCursor(RECT cursorRct, DWORD cursorShape, bool cross)
{
	//Save the DC state
	int DCState=SaveDC(m_wndDC);
	//Set the NOT ROP2
	SetROP2(m_wndDC,R2_NOT);
	//Remove any clipping region
	SelectClipRgn(m_wndDC,NULL);
	//Select a null brush
	SelectBrush(m_wndDC,GetStockBrush(NULL_BRUSH));
	//Draw the cursor
	switch(cursorShape)
	{
	case PS_ENDCAP_ROUND:
		Ellipse(m_wndDC,EXPANDRECT_C(cursorRct));
		break;
	case PS_ENDCAP_SQUARE:
		Rectangle(m_wndDC,EXPANDRECT_C(cursorRct));
		break;
	default:
		break;
	}
	//Eventually draw the cross
	if(cross)
	{
		//Find the medium point between the center and the pixel next to it
		POINT pos=m_position,pos2=m_position;
		pos2.x++;
		pos2.y++;
		DIB2IVWndPoint(&pos);
		DIB2IVWndPoint(&pos2);
		pos.x=(pos.x+pos2.x)/2;
		pos.y=(pos.y+pos2.y)/2;
		//Draw the cross
		MoveToEx(m_wndDC,pos.x-PREC_CURSOR_CROSS_SIZE,pos.y-PREC_CURSOR_CROSS_SIZE,NULL);
		LineTo(m_wndDC,pos.x+PREC_CURSOR_CROSS_SIZE,pos.y+PREC_CURSOR_CROSS_SIZE);
		MoveToEx(m_wndDC,pos.x+PREC_CURSOR_CROSS_SIZE,pos.y-PREC_CURSOR_CROSS_SIZE,NULL);
		LineTo(m_wndDC,pos.x-PREC_CURSOR_CROSS_SIZE,pos.y+PREC_CURSOR_CROSS_SIZE);
	}
	//Restore the DC state
	RestoreDC(m_wndDC,DCState);
}