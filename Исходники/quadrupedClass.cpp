void quadrupedClass::Draw(HDC hdc)const{
	
	/*//DEBUGGING CODE: draw the redraw box. 
	//note: the box is not erased due to how this works (drawing what it would be the previous frame...), 
	//but it's a decent indicator of where the erasing will happen, to be sure it works properly
	HBRUSH brushRed = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
	FillRect(hdc, &RedrawArea(true), brushRed);
	//END debugging*/


	HPEN penFront = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HPEN penBack = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//different colors for the legs
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//basic pen is black
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);//store the original pen

	//head
	Ellipse(hdc, Head.left, Head.top, Head.right, Head.bottom);
	//back
	DrawLine(hdc, Back.Start, Back.End);
	//legs
		//back
	SelectObject(hdc, penBack);//change the pen
	DrawLine(hdc, LegBB.Start, LegBB.End);
	DrawLine(hdc, LegFB.Start, LegFB.End);
		//front
	SelectObject(hdc, penFront);//change the pen
	DrawLine(hdc, LegFF.Start, LegFF.End);
	DrawLine(hdc, LegBF.Start, LegBF.End);


	//reset hdc
	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	DeleteObject(penFront);
	DeleteObject(penBack);

}