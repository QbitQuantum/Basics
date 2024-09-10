//

#include "stdafx.h"
#include "WinApi-Right.h"
#include "Snake.h"
#include <time.h>

#define MAX_LOADSTRING 100
#define TIMER 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
vector<Snake*> snakes;
HPEN hPen = CreatePen(PS_SOLID, 20, RGB(0, 0, 0));	//pióro o gruboœci 20 mm
HPEN hRedPen = CreatePen(PS_SOLID, 20, RGB(255, 0, 0));	//pióro o gruboœci 20 mm
Berry *berry;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);