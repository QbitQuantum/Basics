int main(void)
{
	RGBQUAD Buffer[300*300];
	HDC MyDC=GetDC(FindWindow("ConsoleWindowClass", NULL)), DesktopDC=GetDC(0);
	SetConsoleTitle("CHDC2DIB Example");
	system("mode con:cols=36 lines=18");
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible=FALSE;
	cci.dwSize=10;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	CHDC2DIB h2d;
	POINT Point;
	while(true)
	{
		GetCursorPos(&Point);
		h2d.HDC2DIB(DesktopDC, Buffer, Point.x-150, Point.y-150, 300, 300);
		for(int i=0;i<300;i++)
		{
			for(int j=0;j<300;j++)
			{
				int t=(300-j-1)*300+i;
				Buffer[t].rgbRed=255-Buffer[t].rgbRed;
				Buffer[t].rgbGreen=255-Buffer[t].rgbGreen;
				Buffer[t].rgbBlue=255-Buffer[t].rgbBlue;
			}
		}
		h2d.DIB2HDC(MyDC, Buffer, 0, 0, 300, 300);
		Sleep(10);
	}
	return 0;
}