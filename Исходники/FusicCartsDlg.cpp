BOOL CFusicCartsDlg::OnInitDialog()
{
	mysqlpp::StoreQueryResult resFuse;
	mysqlpp::StoreQueryResult resUser;
	CDialog::OnInitDialog();

	//set the stop all button dialog pointer:
	m_ctlBtnStopall.fnSetCartsDialogPointer((void*)this);

	//set up button maps:
	fnSetupButtonMaps();

	//set up all nav buttons:
	for(mapNav::iterator i = m_mapBtnNavBottom.begin(); i != m_mapBtnNavBottom.end();
		i++)
	{
		i->second->fnSetupNavButtonForPage(i->first, USERCARTS, (void*)this);
	}

	for(mapNav::iterator i = m_mapBtnNavTop.begin(); i != m_mapBtnNavTop.end();
		i++)
	{
		i->second->fnSetupNavButtonForPage(i->first, FUSECARTS, (void*)this);
	}

	//setup all carts buttons:
	for(mapCart::iterator i = m_mapBtnCartBottom.begin(); i != m_mapBtnCartBottom.end();
		i++)
	{
		i->second->fnSetDefaultButton();
	}

	for(mapCart::iterator i = m_mapBtnCartTop.begin(); i != m_mapBtnCartTop.end();
		i++)
	{
		i->second->fnSetDefaultButton();
	}



	//setup stopall button:
	m_ctlBtnStopall.fnSetBackColour(255,0,0, true);
	m_ctlBtnStopall.fnSetFontColour(255,255,0);
	m_ctlBtnStopall.fnSetEdgeColour(255,255,0);
	m_ctlBtnStopall.fnSetClickColourChange(true);

	//setup logout button:
	m_ctlBtnLogout.fnSetBackColour(255,0,0,true);
	m_ctlBtnLogout.fnSetFontColour(255,255,0);
	m_ctlBtnLogout.fnSetEdgeColour(255,255,0);
	m_ctlBtnLogout.fnSetClickColourChange(true);

	//setup reconnect button:
	m_ctlBtnReconnect.fnSetBackColour(255,0,0,true);
	m_ctlBtnReconnect.fnSetFontColour(255,255,0);
	m_ctlBtnReconnect.fnSetEdgeColour(255,255,0);
	m_ctlBtnReconnect.fnSetClickColourChange(true);

	//setup refresh button:
	m_ctlBtnRefresh.fnSetBackColour(255,0,0,true);
	m_ctlBtnRefresh.fnSetFontColour(255,255,0);
	m_ctlBtnRefresh.fnSetEdgeColour(255,255,0);
	m_ctlBtnRefresh.fnSetClickColourChange(true);


	//create the connection to mysql:
	if(!connect())
	{
		//we didnt connect:
		CString strError;
		strError = "Error: could not connecto the mysql database: ";
		strError += m_PMYSQLConn->error();
		strError += ".";
		MessageBox(strError, "Carts Pane", MB_OK | MB_ICONERROR);
	}

	//need to get all fuse carts:
	resFuse = fnGetResultSetForQuery("SELECT * FROM tbl_carts where Show_ID = 0 and Cart_ID like '1%'");

	//setup fuse carts:
	fnSetupButtonForPageData(resFuse, FUSECARTS);

	//do the query for user carts:
	CString strQuery;
	CString strShowID;
	strShowID.Format("%d", g_intShowID);
	strQuery = "SELECT * FROM tbl_carts where Show_ID = ";
	strQuery += strShowID;
	strQuery += " and Cart_ID like '1%'";

	//do the query:
	resUser = fnGetResultSetForQuery(strQuery);

	//setup the user buttons:
	fnSetupButtonForPageData(resUser, USERCARTS);

	//we need now to get carts that where left playing on logout:
	for(std::vector<SCartsList>::iterator i = m_pLoginDlg->m_vecCartsList.begin();
		i != m_pLoginDlg->m_vecCartsList.end(); i++)
	{
		//we want to set all current first buttons up (as these will be displaied first):
		//get the button we firstly need to change:
		CCartsButton* curBtn = NULL;
		if(i->intPageNumber == 1)
		{
			curBtn = m_mapBtnCartTop[i->strCartPosistion];
			if(curBtn == NULL)
				break;

			for(T_mapCallback::iterator j = g_mapCartCallbacks.begin(); j != g_mapCartCallbacks.end();
				j++)
			{
				if(j->first == i->hsyCartsSync)
				{
					g_mapCartCallbacks.erase(j);
					break;
				}
			}


			//set all settings back;
			curBtn->fnPageMoveOn(i->hstCartsStream, i->hsyCartsSync);

			//also reset the callback:
			BASS_ChannelRemoveSync(i->hstCartsStream, i->hsyCartsSync);

			//set the new callback for the button:
			HSYNC callback = BASS_ChannelSetSync(i->hstCartsStream, BASS_SYNC_END, 0, 
				&CCallbackButton::fnEndCallback, 0);

			//add to the callback map:
			g_mapCartCallbacks[callback] = (CCallbackButton*)curBtn;
		}
		else
		{
			//the other buttons arn't on the first page.
			//so we need to put them back into the Navigation stream vector:
			//fist find the nav button that this cart will corrispond to:
			CNavigationButton* navBtn = m_mapBtnNavTop[i->intPageNumber];

			//remove the callback before we change it from the map:
			for(T_mapCallback::iterator j = g_mapCartCallbacks.begin();
				j != g_mapCartCallbacks.end(); j++)
			{
				if(j->first == i->hsyCartsSync)
				{
					g_mapCartCallbacks.erase(j);
					break;
				}
			}

			BASS_ChannelRemoveSync(i->hstCartsStream, i->hsyCartsSync);
			HSYNC synx = BASS_ChannelSetSync(i->hstCartsStream, BASS_SYNC_END,0,
				&CCallbackButton::fnEndCallback, 0);

			SNavigationStreams sNav;
			sNav.intPageNumber = i->intPageNumber;
			sNav.stream = i->hstCartsStream;
			sNav.syncHandle = i->hsyCartsSync;
			sNav.syncHandle = synx;
			//sNav.

			//now the tricky part, we need to create a std::mapCart::iterator for the
			//button that we can store in the struct; the only way I can see of doing this
			//is to iterate over the buttons untill we find one with the appropriate ID:
			for(mapCart::iterator ii = m_mapBtnCartTop.begin(); ii != m_mapBtnCartTop.end();
				ii++)
			{
				if(ii->first == i->strCartPosistion)
				{
					sNav.btnIterator = ii;
					break;
				}
			}

			//reset the callback:
			g_mapCartCallbacks[i->hsyCartsSync] = navBtn;

			//incrase the reference count on the nav button (to start it flashing):
			navBtn->fnIncreasePlayCount();

			//also add to the nav stream map:
			m_vecNavStreamsTop.push_back(sNav);
		}

	}

	//allow the window to be changed.
	AllowSetForegroundWindow(ASFW_ANY);

	//clear out the vector on the login dialog for the next logout population:
	m_pLoginDlg->m_vecCartsList.clear();

	//begin the fader start timer:
	SetTimer(WM_USER + 10, 10, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
}