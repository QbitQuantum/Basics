void BaseMainPage::focusNextLeftChild()
{
	if(!m_pCtrlPage)
		return;

	if(isNavigatorMode())
	{
		if(m_nNavigatorCnt <= 0)
			return;

		int tIndex = 0;
		m_nCurrentNavigator == 0 ? tIndex = m_nNavigatorCnt-1 : tIndex = m_nCurrentNavigator-1;
		navigatorPageAt(tIndex);
		return;
	}

	QObjectList &list = m_pCtrlPage->xList;
	if(list.length() == 0)
		return;

	QObject *obj = m_pCtrlPage->focusWidget();
	int index = list.indexOf(obj);
	if(index == -1)
		index = 0;
	if(index == 0)
	{
		index = list.length();
	}
	index--;
	QWidget *tab =static_cast<QWidget *>(list.at(index));
	tab->setFocus();
}