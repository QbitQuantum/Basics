static void
DrawStuff(BView *view)
{
	// StrokeShape
	BShape shape;
	BPoint bezier[3] = {BPoint(100,0), BPoint(100, 100), BPoint(25, 50)};
	shape.MoveTo(BPoint(150,0));
	shape.LineTo(BPoint(200,100));
	shape.BezierTo(bezier);
	shape.Close();
	view->StrokeShape(&shape);
	
	// Stroke/FillRect, Push/PopState, SetHighColor, SetLineMode, SetPenSize
	view->PushState();
	const rgb_color blue = { 0, 0, 240, 0 };
	view->SetHighColor(blue);
	view->SetLineMode(B_BUTT_CAP, B_BEVEL_JOIN);
	view->SetPenSize(7);
	view->StrokeRect(BRect(10, 220, 50, 260));
	view->FillRect(BRect(65, 245, 120, 300));
	view->PopState();
	
	// Stroke/FillEllipse
	view->StrokeEllipse(BPoint(50, 150), 50, 50);
	view->FillEllipse(BPoint(100, 120), 50, 50);
	
	// Stroke/FillArc
	view->StrokeArc(BRect(0, 200, 50, 250), 180, 180);
	view->FillArc(BPoint(150, 250), 50, 50, 0, 125);
	
	// DrawString, SetHighColor, SetFontSize
	const rgb_color red = { 240, 0, 0, 0 };
	view->SetHighColor(red);
	view->SetFontSize(20);
	view->DrawString("BPicture ", BPoint(30, 20));
	view->DrawString("test");

	// DrawLine with pen position
	const rgb_color purple = { 200, 0, 220, 0 };
	view->SetHighColor(purple);
	view->StrokeLine(BPoint(50, 30), BPoint(30, 50));
	view->StrokeLine(BPoint(80, 50));
	view->StrokeLine(BPoint(50, 30));
}