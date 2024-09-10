BOOL 
GMDataToPaste (VOID) 
{
	if (IsClipboardFormatAvailable (CF_TEXT)) return TRUE;
	return FALSE;
}