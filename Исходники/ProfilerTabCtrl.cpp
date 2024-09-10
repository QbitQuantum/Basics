CProfilerTabCtrl::~CProfilerTabCtrl()
{
	PROFILEBOXVEC::iterator listIter = m_InternalBoxes.begin();
	for (; listIter!=m_InternalBoxes.end(); listIter++)
	{
		CWnd *current = (*listIter);
		current->DestroyWindow();
		delete current;
	}
}