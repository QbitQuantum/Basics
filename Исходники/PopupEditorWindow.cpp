void SinglePopupEditor::testPopup()
{

	if(m_pTestPopup)
		delete m_pTestPopup;
	m_pTestPopup = getMenu();
	if(!m_pTestPopup)
		return;
	connect(m_pTestPopup, SIGNAL(testModeItemClicked(KviKvsPopupMenuItem *)), this, SLOT(testModeMenuItemClicked(KviKvsPopupMenuItem *)));
	QPoint pnt = m_pMenuButton->mapToGlobal(QPoint(0, m_pMenuButton->height()));
	KviKvsVariantList * parms = new KviKvsVariantList();
	parms->append(new KviKvsVariant(QString("test1")));
	parms->append(new KviKvsVariant(QString("test2")));
	parms->append(new KviKvsVariant(QString("test3")));
	parms->append(new KviKvsVariant(QString("test4")));
	m_pTestPopup->doPopup(pnt, g_pActiveWindow, parms, true);
}