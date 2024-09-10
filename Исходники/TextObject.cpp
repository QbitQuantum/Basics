void CTextObject::ReleaseObjectText()
{
	FireDataStop();
	if (OleIsCurrentClipboard(this) == S_OK)
		OleFlushClipboard();
}