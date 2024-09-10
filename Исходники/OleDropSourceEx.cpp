// Set the drag image cursor and text according to the drop effect and redraw.
// Cursor and description text (if enabled) are shown according to the passed drop effect
// when dwEffect is valid and a DropDescription data object does not exist or has the 
// DROPIMAGE_INVALID image type set. 
//
//  DDWM_SETCURSOR (WM_USER + 2)
//   WPARAM:  Cursor type
//    0 = Get type and text from DropDescription data object (behaviour is identical to DDWM_UPDATEWINDOW message)
//    1 = Can't drop (Stop sign)
//    2 = Move (Arrow)
//    3 = Copy (Plus sign)
//    4 = Link (Curved arrow)
//   LPARAM: 0
//  Set the drag image cursor and use the associated default text if no drop description
//   present or it has the invalid image type.
//  NOTE: When a drop description object is present and has not the DROPIMAGE_INVALID type
//   set, it is used regardless of the WPARAM value.
bool COleDropSourceEx::SetDragImageCursor(DROPEFFECT dwEffect)
{
	// Stored data is always a DWORD even with 64-bit apps.
	HWND hWnd = (HWND)ULongToHandle(CDragDropHelper::GetGlobalDataDWord(m_pIDataObj, _T("DragWindow")));
	if (hWnd)
	{
		WPARAM wParam = 0;								// Use DropDescription to get type and optional text
		switch (dwEffect & ~DROPEFFECT_SCROLL)
		{
		case DROPEFFECT_NONE : wParam = 1; break;
		case DROPEFFECT_COPY : wParam = 3; break;		// The order is not as for DROPEEFECT values!
		case DROPEFFECT_MOVE : wParam = 2; break;
		case DROPEFFECT_LINK : wParam = 4; break;
		}
		::SendMessage(hWnd, DDWM_SETCURSOR, wParam, 0);
	}
	return NULL != hWnd;
}