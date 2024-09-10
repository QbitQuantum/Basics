static void postKeyMessage(int x, int y, unsigned int msg)
{
	SetForegroundWindow(windowFromPoint(x, y));
	switch(msg)
	{
	case 'a' : pressKey(A); break;
	case 'b' : pressKey(B); break;
	case 'A' : pressShifted(A);break;
	case '1' : pressKey(ONE); break;
	case '2' : pressKey(TWO); break;
	case '3' : pressKey(THREE); break;
	case '4' : pressKey(FOUR); break;
	case '5' : pressKey(FIVE); break;
	case '6' : pressKey(SIX); break;
	case '7' : pressKey(SEVEN); break;
	case '8' : pressKey(EIGHT); break;
	case '9' : pressKey(NINE); break;
	case '0' : pressKey(ZERO); break;
	case '\t' : pressKey(TAB); break;
	case '\n' : pressKey(ENTER); break;
	}
	
}