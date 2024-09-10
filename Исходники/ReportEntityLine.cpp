void CReportEntityLine::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityLine::Draw
	Description :	Draws the object.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to
					CRect rect	-	True (zoomed) rectangle to 
									draw to.
					
	Usage :			Called from "CDiagramEditor::DrawObjects".

   ============================================================*/
{
	CPen pen;
	const float* table = Drawer::GetColorByIndex(GetBorderColor());
	COLORREF clr = RGB((int)(table[0]*255.0f),(int)(table[1]*255.0f),(int)(table[2]*255.0f));
	pen.CreatePen( PS_SOLID, GetBorderThickness(), clr );
	dc->SelectObject( &pen );

	dc->MoveTo( rect.TopLeft() );
	dc->LineTo( rect.BottomRight() );

	dc->SelectStockObject( BLACK_PEN );

}