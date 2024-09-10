DllExport int FAR PASCAL VBCubeArrayDraw(HDC hDC, int N)
{

int j;

	//Cube CubeObject;
	RECT r;

	GetClipBox(hDC, &r);
	
	//	Height should be set by drawing program
	CubeObject.Transform.Height = r.bottom - r.top;
	CubeObject.SetOrigin( 100, 100, 0);
	CubeObject.SetScale( 2, 2 );
	
	j=N;
	if(j<1)
		j=1;
	
	//	Colour should be set by the drawing program!
	HPEN NewPen = CreatePen(PS_SOLID, 0, RGB(0,0,255));		//	create blue pen color
	HBRUSH NewBrush = CreateSolidBrush(RGB(255,255,255));	//	create brush (white)

	HGDIOBJ OldPen = GetCurrentObject(hDC, OBJ_PEN);		//	remember old colour
	HGDIOBJ OldBrush = GetCurrentObject(hDC, OBJ_BRUSH);	//	remember old brush
	
	//	Set colours
	SelectObject(hDC, NewPen);
	SelectObject(hDC, NewBrush);

	CubeObject.DrawNCubehDC(hDC, j);

	//	Return Colours
	SelectObject(hDC, OldPen);
	SelectObject(hDC, OldBrush);

	//	Delete all unnecessary objects
	DeleteObject(NewPen);
	DeleteObject(NewBrush);

return j;
}