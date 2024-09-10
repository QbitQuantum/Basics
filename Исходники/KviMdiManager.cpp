void KviMdiManager::fillWindowPopup()
{
	m_pWindowPopup->clear();

	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::CascadeWindows)),(__tr2qs("&Cascade Windows")),this,SLOT(cascadeWindows()));
	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::CascadeWindows)),(__tr2qs("Cascade &Maximized")),this,SLOT(cascadeMaximized()));

    m_pWindowPopup->addSeparator();
	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("&Tile Windows")),this,SLOT(tile()));

	m_pTileMethodPopup->clear();
    QAction * pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::AutoTileWindows)),(__tr2qs("&Auto Tile")),this,SLOT(toggleAutoTile()));
    pAction->setCheckable(true);
    pAction->setChecked(KVI_OPTION_BOOL(KviOption_boolAutoTileWindows));
    pAction->setData(-1);
    m_pTileMethodPopup->addSeparator();

    if(KVI_OPTION_UINT(KviOption_uintTileMethod) >= KVI_NUM_TILE_METHODS)
        KVI_OPTION_UINT(KviOption_uintTileMethod) = KVI_TILE_METHOD_PRAGMA9HOR;

    uint uSelectedMethod= KVI_OPTION_UINT(KviOption_uintTileMethod);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Anodine's Full Grid")));
    pAction->setData(KVI_TILE_METHOD_ANODINE);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_ANODINE) pAction->setChecked(true);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Pragma's Horizontal 4-Grid")));
    pAction->setData(KVI_TILE_METHOD_PRAGMA4HOR);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_PRAGMA4HOR) pAction->setChecked(true);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Pragma's Vertical 4-Grid")));
    pAction->setData(KVI_TILE_METHOD_PRAGMA4VER);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_PRAGMA4VER) pAction->setChecked(true);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Pragma's Horizontal 6-Grid")));
    pAction->setData(KVI_TILE_METHOD_PRAGMA6HOR);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_PRAGMA6HOR) pAction->setChecked(true);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Pragma's Vertical 6-Grid")));
    pAction->setData(KVI_TILE_METHOD_PRAGMA6VER);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_PRAGMA6VER) pAction->setChecked(true);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Pragma's Horizontal 9-Grid")));
    pAction->setData(KVI_TILE_METHOD_PRAGMA9HOR);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_PRAGMA9HOR) pAction->setChecked(true);
    pAction = m_pTileMethodPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Pragma's Vertical 9-Grid")));
    pAction->setData(KVI_TILE_METHOD_PRAGMA9VER);
    pAction->setCheckable(true);
    if(uSelectedMethod==KVI_TILE_METHOD_PRAGMA9VER) pAction->setChecked(true);

    pAction = m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::TileWindows)),(__tr2qs("Tile Met&hod")));
    pAction->setMenu(m_pTileMethodPopup);

    m_pWindowPopup->addSeparator();
	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::MaxVertical)),(__tr2qs("Expand &Vertically")),this,SLOT(expandVertical()));
	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::MaxHorizontal)),(__tr2qs("Expand &Horizontally")),this,SLOT(expandHorizontal()));

    m_pWindowPopup->addSeparator();
	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::Minimize)),(__tr2qs("Mi&nimize All")),this,SLOT(minimizeAll()));
	m_pWindowPopup->addAction(*(g_pIconManager->getSmallIcon(KviIconManager::Restore)),(__tr2qs("&Restore all")),this,SLOT(restoreAll()));

    m_pWindowPopup->addSeparator();
	int i = 100;
	QString szItem;
	QString szCaption;
	QList<QMdiSubWindow*> tmp = subWindowList(QMdiArea::StackingOrder);
	QListIterator<QMdiSubWindow*> it(tmp);

	KviMdiChild * lpC;

	while (it.hasNext())
	{
		lpC = (KviMdiChild *) it.next();

		if (!lpC->inherits("KviMdiChild"))
		{
			i++;
			continue;
		}

		szItem.setNum(((uint)i)-99);
		szItem+=". ";

		szCaption = lpC->windowTitle();
		if(szCaption.length() > 30)
		{
			QString trail = szCaption.right(12);
			szCaption.truncate(12);
			szCaption+="...";
			szCaption+=trail;
		}

		if(lpC->state()==KviMdiChild::Minimized)
		{
			szItem+="(";
			szItem+=szCaption;
			szItem+=")";
		} else szItem+=szCaption;

		const QPixmap * pix = lpC->icon();

		if (pix && !(pix->isNull()))
		{
            pAction = m_pWindowPopup->addAction(*pix, szItem);
            pAction->setData(i);
		} else {
            pAction = m_pWindowPopup->addAction(szItem);
            pAction->setData(i);
        }

		//this is useless, since the windows are listed in stacking order, the active one
		//will always be the last anyway.
		//if(lpC==currentSubWindow())
		//	m_pWindowPopup->setItemChecked(i, true );
		i++;
	}
}