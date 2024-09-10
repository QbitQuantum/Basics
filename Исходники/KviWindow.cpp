void KviWindow::createSystemTextEncodingPopup()
{
	if(!g_pMdiWindowSystemTextEncodingPopup)
	{
		// first time called, create the menu
		g_pMdiWindowSystemTextEncodingPopup = new QMenu();
		g_pMdiWindowSystemTextEncodingPopupStandard = new QMenu();
		g_pMdiWindowSystemTextEncodingPopupSmart = new QMenu();
		g_pMdiWindowSystemTextEncodingPopupSmartUtf8 = new QMenu();
		g_pMdiWindowSystemTextEncodingActionGroup = new QActionGroup(g_pMdiWindowSystemTextEncodingPopup);

		//default action
		QTextCodec * pCodec = defaultTextCodec();
		QString szTmp = __tr2qs("Use Default Encoding");
		if(pCodec)
		{
			szTmp += " (";
			szTmp += pCodec->name();
			szTmp += ")";
		}

		g_pMdiWindowSystemTextEncodingDefaultAction = g_pMdiWindowSystemTextEncodingPopup->addAction(szTmp);
		g_pMdiWindowSystemTextEncodingActionGroup->addAction(g_pMdiWindowSystemTextEncodingDefaultAction);
		g_pMdiWindowSystemTextEncodingDefaultAction->setData(-1);
		if(m_szTextEncoding.isEmpty())
		{
			g_pMdiWindowSystemTextEncodingDefaultAction->setCheckable(true);
			g_pMdiWindowSystemTextEncodingDefaultAction->setChecked(true);
		}

		//current action
		g_pMdiWindowSystemTextEncodingCurrentAction = g_pMdiWindowSystemTextEncodingPopup->addAction(__tr2qs("Current: "));
		g_pMdiWindowSystemTextEncodingActionGroup->addAction(g_pMdiWindowSystemTextEncodingCurrentAction);
		g_pMdiWindowSystemTextEncodingCurrentAction->setVisible(false);

		// other first level menus
		g_pMdiWindowSystemTextEncodingPopup->addSeparator();

		QAction * pAction = g_pMdiWindowSystemTextEncodingPopup->addAction(__tr2qs("Standard"));
		pAction->setMenu(g_pMdiWindowSystemTextEncodingPopupStandard);
		pAction = g_pMdiWindowSystemTextEncodingPopup->addAction(__tr2qs("Smart (Send Local)"));
		pAction->setMenu(g_pMdiWindowSystemTextEncodingPopupSmart);
		pAction = g_pMdiWindowSystemTextEncodingPopup->addAction(__tr2qs("Smart (Send UTF-8)"));
		pAction->setMenu(g_pMdiWindowSystemTextEncodingPopupSmartUtf8);

		// second level menus (encoding groups)
		QMenu * pPopupStandard[KVI_NUM_ENCODING_GROUPS];
		QMenu * pPopupSmart[KVI_NUM_ENCODING_GROUPS];
		QMenu * pPopupSmartUtf8[KVI_NUM_ENCODING_GROUPS];

		uint u = 0;
		const char * pcEncodingGroup = KviLocale::instance()->encodingGroup(u);

		while(pcEncodingGroup)
		{
			pPopupStandard[u] = g_pMdiWindowSystemTextEncodingPopupStandard->addMenu(pcEncodingGroup);
			if(u) //only standard popup contains unicode menu
			{
				pPopupSmart[u] = g_pMdiWindowSystemTextEncodingPopupSmart->addMenu(pcEncodingGroup);
				pPopupSmartUtf8[u] = g_pMdiWindowSystemTextEncodingPopupSmartUtf8->addMenu(pcEncodingGroup);
			}

			pcEncodingGroup = KviLocale::instance()->encodingGroup(++u);
		}

		// third level menus (encodings)
		uint i = 0;
		KviLocale::EncodingDescription * pDesc = KviLocale::instance()->encodingDescription(i);
		while(pDesc->pcName)
		{
			szTmp = QString("%1 (%2)").arg(pDesc->pcName, pDesc->pcDescription);
			if(KviQString::equalCI(m_szTextEncoding, pDesc->pcName))
			{
				g_pMdiWindowSystemTextEncodingCurrentAction->setText(__tr2qs("Current: ") + szTmp);
				g_pMdiWindowSystemTextEncodingCurrentAction->setCheckable(true);
				g_pMdiWindowSystemTextEncodingCurrentAction->setChecked(true);
				g_pMdiWindowSystemTextEncodingCurrentAction->setVisible(true);
				g_pMdiWindowSystemTextEncodingCurrentAction->setData(i);
			}

			QMenu * pMenu = pDesc->bSmart ? (pDesc->bSendUtf8 ? pPopupSmartUtf8[pDesc->uGroup] : pPopupSmart[pDesc->uGroup]) : pPopupStandard[pDesc->uGroup];

			QAction * pAction = pMenu->addAction(szTmp);
			pAction->setData(i);
			g_pMdiWindowSystemTextEncodingActionGroup->addAction(pAction);

			pDesc = KviLocale::instance()->encodingDescription(++i);
		}
	}
	else
	{
		//default action: refresh the name
		QTextCodec * pCodec = defaultTextCodec();
		QString szTmp = __tr2qs("Use Default Encoding");
		if(pCodec)
		{
			szTmp += " (";
			szTmp += pCodec->name();
			szTmp += ")";
		}

		disconnect(g_pMdiWindowSystemTextEncodingActionGroup, SIGNAL(triggered(QAction *)), nullptr, nullptr);
		connect(g_pMdiWindowSystemTextEncodingActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(systemTextEncodingPopupActivated(QAction *)));
		g_pMdiWindowSystemTextEncodingDefaultAction->setText(szTmp);

		//menu already exists, choose the right item
		if(m_szTextEncoding.isEmpty())
		{
			//default action; hide the current action
			g_pMdiWindowSystemTextEncodingCurrentAction->setVisible(false);
			g_pMdiWindowSystemTextEncodingDefaultAction->setCheckable(true);
			g_pMdiWindowSystemTextEncodingDefaultAction->setChecked(true);
		}
		else
		{
			int i = 0;
			KviLocale::EncodingDescription * pDesc = KviLocale::instance()->encodingDescription(i);
			while(pDesc->pcName)
			{
				if(KviQString::equalCI(m_szTextEncoding, pDesc->pcName))
				{
					szTmp = QString("%1 (%2)").arg(pDesc->pcName, pDesc->pcDescription);
					g_pMdiWindowSystemTextEncodingCurrentAction->setText(__tr2qs("Current: ") + szTmp);
					g_pMdiWindowSystemTextEncodingCurrentAction->setCheckable(true);
					g_pMdiWindowSystemTextEncodingCurrentAction->setChecked(true);
					g_pMdiWindowSystemTextEncodingCurrentAction->setVisible(true);
					g_pMdiWindowSystemTextEncodingCurrentAction->setData(i);
					break;
				}

				pDesc = KviLocale::instance()->encodingDescription(++i);
			}
		}
	}

	disconnect(g_pMdiWindowSystemTextEncodingActionGroup, SIGNAL(triggered(QAction *)), nullptr, nullptr);
	connect(g_pMdiWindowSystemTextEncodingActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(systemTextEncodingPopupActivated(QAction *)));
}