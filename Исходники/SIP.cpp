/**
*  \author Darryn Campbell (DCC, JRQ768)
*  \date February 2010 (Initial Creation, DCC)
*/
void HideSIPButton()
{
	HWND hg_sipbut = FindWindow(L"MS_SIPBUTTON", NULL);
	if (hg_sipbut)
		ShowWindow(hg_sipbut, SW_HIDE);
}