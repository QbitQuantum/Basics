// 根据半径、中心点和类型画四分之一圆弧
void DrawQuarterArc(HDC hdc, int radius, int xPoint, int yPoint, int style)
{
	POINT p1, p2, p3, p4, pStart, pEnd;
	p1.x = xPoint + radius;
	p1.y = yPoint;
	p2.x = xPoint;
	p2.y = yPoint - radius;
	p3.x = xPoint - radius;
	p3.y = yPoint;
	p4.x = xPoint;
	p4.y = yPoint + radius;
	switch (style)
	{
	case 0:
		pStart = p1;
		pEnd = p2;
		break;
	case 1:
		pStart = p2;
		pEnd = p3;
		break;
	case 2:
		pStart  = p3;
		pEnd = p4;
		break;
	case 3:
		pStart = p4;
		pEnd = p1;
		break;
	default:
		return;
	}

	Arc(hdc, xPoint - radius, yPoint - radius, xPoint + radius, yPoint + radius, pStart.x, pStart.y, pEnd.x, pEnd.y);
}