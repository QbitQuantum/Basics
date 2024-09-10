//########################################################################
// Sets TrackMouseEvent subclassing to all the buttons children of the specified window
//########################################################################
BOOL TME(HWND hwnd)
{
	treMouse_minimize.cbSize		= sizeof(TRACKMOUSEEVENT);
	treMouse_minimize.hwndTrack		= hwndMinimize;
	treMouse_minimize.dwFlags		= TME_HOVER | TME_LEAVE ;
	treMouse_minimize.dwHoverTime	= 10000;
	_TrackMouseEvent(&treMouse_minimize);
#include "push_gwlp.h"
	btnOld_minimize = (WNDPROC)SetWindowLongPtr(hwndMinimize, GWLP_WNDPROC, (LONG_PTR)minimizeButtonSubclassProc);
#include "pop_gwlp.h"



	treMouse_close.cbSize	= sizeof(TRACKMOUSEEVENT);
	treMouse_close.hwndTrack	= hwndClose;
	treMouse_close.dwFlags	= TME_HOVER | TME_LEAVE ;
	treMouse_close.dwHoverTime	= 10000;
	_TrackMouseEvent(&treMouse_close);
#include "push_gwlp.h"
	btnOld_close = (WNDPROC)SetWindowLongPtr(hwndClose, GWLP_WNDPROC, (LONG_PTR)closeButtonSubclassProc);
#include "pop_gwlp.h"



	treMouse_StartGame.cbSize		= sizeof(TRACKMOUSEEVENT);
	treMouse_StartGame.hwndTrack	= hwndStartGame;
	treMouse_StartGame.dwFlags		= TME_HOVER | TME_LEAVE ;
	treMouse_StartGame.dwHoverTime	= 10000;
	_TrackMouseEvent(&treMouse_StartGame);
#include "push_gwlp.h"
	btnOld_StartGame = (WNDPROC)SetWindowLongPtr(hwndStartGame, GWLP_WNDPROC, (LONG_PTR)StartGameButtonSubclassProc);
#include "pop_gwlp.h"

	treMouse_Register.cbSize		= sizeof(TRACKMOUSEEVENT);
	treMouse_Register.hwndTrack		= hwndRegister;
	treMouse_Register.dwFlags		= TME_HOVER | TME_LEAVE ;
	treMouse_Register.dwHoverTime	= 10000;
	_TrackMouseEvent(&treMouse_Register);
#include "push_gwlp.h"
	btnOld_Register = (WNDPROC)SetWindowLongPtr(hwndRegister, GWLP_WNDPROC, (LONG_PTR)RegisterButtonSubclassProc);
#include "pop_gwlp.h"

	treMouse_Cancel.cbSize		= sizeof(TRACKMOUSEEVENT);
	treMouse_Cancel.hwndTrack		= hwndCancel;
	treMouse_Cancel.dwFlags		= TME_HOVER | TME_LEAVE ;
	treMouse_Cancel.dwHoverTime	= 10000;
	_TrackMouseEvent(&treMouse_Cancel);
#include "push_gwlp.h"
	btnOld_Cancel = (WNDPROC)SetWindowLongPtr(hwndCancel, GWLP_WNDPROC, (LONG_PTR)CancelButtonSubclassProc);
#include "pop_gwlp.h"


	return TRUE;
}