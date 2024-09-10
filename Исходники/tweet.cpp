/*
	別窓を表示させる
	childwindowをどうするか
	HWNDを持ってこれるかどうか
*/
ATOM InitApp(HINSTANCE hInst, WNDPROC Proc, LPCSTR szClassName)
{
	WNDCLASSEX wc;
	
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = hInst;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	wc.hIcon = (HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wc.hIconSm = wc.hIcon;

	//現在のテーマ
	if(!IsThemeActive()) wc.hbrBackground = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENU));
	else wc.hbrBackground = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENUBAR));

	return (RegisterClassEx(&wc));
}