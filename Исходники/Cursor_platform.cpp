void CursorTerminate_platform()
{
	if (hcArrowCopy)
		SetSystemCursor(hcArrowCopy, OCR_NORMAL);
	//Add any platform-specific termination code here
}