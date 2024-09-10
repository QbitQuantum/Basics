// Draw OfficeManagerASE
void OfficeGSE::DrawOfficeManagerASE(HINSTANCE hinst, HWND hwnd, HDC hdc, ActorRequest* ActReq)
{
	int r = ActReq->GetRequest();
	int c = ActReq->GetActorId();
	int bottom = ActReq->GetIntParam1();
	int top = ActReq->GetIntParam2();
	int right = ActReq->GetIntParam3();
	int left = ActReq->GetIntParam4();

	SetBkMode(hdc, TRANSPARENT);
	HPEN Pen = CreatePen(PS_DOT, 0, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	POINT p[5];
	p[0].x = left;  p[0].y = top;
	p[1].x = right; p[1].y = top;
	p[2].x = right; p[2].y = bottom;
	p[3].x = left;  p[3].y = bottom;
	p[4].x = left;  p[4].y = top;
	Polyline(hdc, p, 5);
	DeleteObject(Pen);
}