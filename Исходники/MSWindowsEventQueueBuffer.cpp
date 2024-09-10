bool
CMSWindowsEventQueueBuffer::isEmpty() const
{
	return (HIWORD(GetQueueStatus(QS_ALLINPUT)) == 0);
}