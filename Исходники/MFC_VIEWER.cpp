void MFC_VIEWER::DrawLine(int x1,int y1,int x2,int y2,int width,int r,int g,int b)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,width,RGB(r,g,b));
	dcbmp.SelectObject(&pen);
	dcbmp.MoveTo(x1,y1);
	dcbmp.LineTo(x2,y2);
	pen.DeleteObject();
}