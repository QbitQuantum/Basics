//해당 HDC에 정보 찍기
void timeManager::render(HDC hdc)
{
	char str[256] = {};
	std::string strFrame = "";

	//글자 배경모드 (TRANSPARENT: 투명, QPAQUEL: 불투명)
	SetBkMode(hdc, TRANSPARENT);
	//글자 색상
	SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	if(_timer != NULL)
	{
		//프레임 찍는다
		sprintf_s(str, "framePerSec : %d", _timer->getFrameRate());
		TextOutA(hdc, 0, 0, str, strlen(str));

		//월드 타임 찍는다(경과시간)
		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOutA(hdc, 0, 20, str, strlen(str));

		//갱신 tick 찍는다
		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOutA(hdc, 0, 40, str, strlen(str));
	}
#else
	if(time != NULL)
	{
		//프레임 찍는다
		sprintf(str, "framePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));		
	}
#endif
}