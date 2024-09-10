void
CMSWindowsClipboard::close() const
{
	LOG((CLOG_DEBUG "close clipboard"));
	CloseClipboard();
}