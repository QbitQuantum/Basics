// todo: find out how this works (DECLARE_HANDLE(HDC); 
// ::GetClientRect(m_hDC, &rect); is a compiler-time error, which is pretty cool
RECT TimelineDC::GetClientArea() const
{
	RECT rect;
	GetClipBox(&rect);
	return rect;
}