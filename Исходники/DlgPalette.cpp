void DlgPalette::DrawCell(CDC *pDC, long index)
{
	CRect rect;
	if (!GetCellRect(index, rect)) return;

	CBrush brush;
	
	if (m_editalpha){
		brush.CreateSolidBrush(RGB(m_pal[index].rgbReserved,
					 m_pal[index].rgbReserved ,
					 m_pal[index].rgbReserved ));
	}else{
		brush.CreateSolidBrush(RGB(m_pal[index].rgbRed ,
					 m_pal[index].rgbGreen ,
					 m_pal[index].rgbBlue ));
	}

	CPen   pen;
	if (index==m_selected)
		pen.CreatePen(PS_SOLID, 2, ::GetSysColor(COLOR_3DDKSHADOW));
	else
		pen.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

	CBrush* pOldBrush = (CBrush*) pDC->SelectObject(&brush);
	CPen*   pOldPen   = (CPen*)   pDC->SelectObject(&pen);

	// Draw the cell colour
	pDC->Rectangle(rect);

	// restore DC and cleanup
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}