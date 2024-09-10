void CursorManager::SetCursor(cursor_which which)
{
	Lock();

	DisplayDriver *driver = desktop->ActiveScreen()->DDriver();
	switch(which)
	{
		case B_CURSOR_DEFAULT:
		{
			driver->SetCursor(fDefaultCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_TEXT:
		{
			driver->SetCursor(fTextCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_MOVE:
		{
			driver->SetCursor(fMoveCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_DRAG:
		{
			driver->SetCursor(fDragCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_RESIZE:
		{
			driver->SetCursor(fResizeCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_RESIZE_NWSE:
		{
			driver->SetCursor(fNWSECursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_RESIZE_NESW:
		{
			driver->SetCursor(fNESWCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_RESIZE_NS:
		{
			driver->SetCursor(fNSCursor);
			fCurrentWhich=which;
			break;
		}
		case B_CURSOR_RESIZE_EW:
		{
			driver->SetCursor(fEWCursor);
			fCurrentWhich=which;
			break;
		}
		default:
			break;
	}

	Unlock();
}