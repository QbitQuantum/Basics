LRESULT CBeikeSafeSoftmgrNecessHandler::OnListBoxGetDispInfo( LPNMHDR pnmh )
{
	BKLBMGETDISPINFO* pdi = (BKLBMGETDISPINFO*)pnmh;

	if ( pdi->nListItemID >= m_arrRightList.GetSize() )
		return 0;

	NECESS_SOFT_LIST_DATA&	datalist = m_arrRightList[pdi->nListItemID];

	if (datalist.bTitle)
	{
		// 标题的绘制

		pdi->nHeight = SOFT_LIST_TITLE_HEIGHT;

		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_TITLE,TRUE);
		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_ITEM,FALSE);

		m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_TITLE_NAME,datalist.strTitleName);
	}
	else
	{
		// 里面软件list的绘制

		pdi->nHeight = SOFT_LIST_ITEM_HEIGHT;
		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_TITLE,FALSE);
		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_ITEM,TRUE);

		m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_DIV_ITEM,"crbg",pdi->bSelect?"EBF5FF":"FFFFFF");

		CSoftListItemData* pSoftData = GetSoftDataByID(datalist.strSoftId);

		int nPosX = 0;
		Gdiplus::Image *pImage = NULL;
		{
			CDC dcx = GetDC(m_pMainDlg->m_hWnd);
			HFONT			hFntTmp;

			int nTypeWidth = 0;
			if (m_bShowType)
			{
				hFntTmp = dcx.SelectFont(BkFontPool::GetFont(BKF_DEFAULTFONT));
				CRect rcType;
				CString strType;
				strType.Format(L"[%s]", pSoftData->m_strTypeShort);
				dcx.DrawText(strType, -1, &rcType, DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);
				nTypeWidth = rcType.Width();
				dcx.SelectFont(hFntTmp);
			}

			hFntTmp = dcx.SelectFont(BkFontPool::GetFont(BKF_BOLDFONT));
			CRect rcProb;
			dcx.DrawText(pSoftData->m_strName, -1, &rcProb, DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);
			dcx.SelectFont(hFntTmp);

			ReleaseDC(m_pMainDlg->m_hWnd, dcx);

			CRect rcWin;
			GetWindowRect(m_necessList->m_hWnd, &rcWin);

			int nLablesWidth = 0;
			if ((pSoftData->m_attri&SA_Green) == SA_Green)
			{
				pImage = BkPngPool::Get(IDP_SOFTMGR_GREEN_SOFT);
				nLablesWidth += pImage->GetWidth();
			}
			if (pSoftData->m_bCharge == TRUE)
			{
				if (nLablesWidth != 0)
					nLablesWidth += 2;
				pImage = BkPngPool::Get(IDP_SOFTMGR_CHARGE_SOFT);
				nLablesWidth += pImage->GetWidth();
			}
			if (pSoftData->m_bPlug == TRUE)
			{
				if (nLablesWidth != 0)
					nLablesWidth += 2;
				pImage = BkPngPool::Get(IDP_SOFTMGR_PLUGIN_SOFT);
				nLablesWidth += pImage->GetWidth();
			}
			if ((pSoftData->m_attri&SA_New) == SA_New)
			{
				if (nLablesWidth != 0)
					nLablesWidth += 2;
				pImage = BkPngPool::Get(IDP_SOFTMGR_NEW_SOFT);
				nLablesWidth += pImage->GetWidth();
			}

			int nLeft = 50 + nTypeWidth;
			nPosX = rcWin.Width() - 310 - nLablesWidth;
			if (rcProb.Width() < rcWin.Width() - 310 - nLablesWidth - nLeft)
				nPosX = nLeft + rcProb.Width();
		
			CStringA strPosA;
			strPosA.Format("%d,12,%d,27", nLeft, nPosX);
			m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_TXT_SOFT_TITLE, "pos", strPosA);

			if (m_bShowType)
			{
				CString strTypeShort;
				strTypeShort.Format(L"[%s]", pSoftData->m_strTypeShort);
				m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_TYPE, strTypeShort);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_TYPE,TRUE);
			}
			else
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_TYPE,FALSE);
		}

		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_GREEN,FALSE);
		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_CHARGE,FALSE);
		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_PLUGIN,FALSE);
		m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_NEW,FALSE);
		int nPosY = 10;
		if ((pSoftData->m_attri&SA_Green) == SA_Green)
		{
			nPosX += 2;
			CStringA strPosA;
			strPosA.Format("%d,%d", nPosX, nPosY);
			m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_GREEN, "pos", strPosA);
			m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_GREEN,TRUE);
			nPosX += 45;
		}
		if (pSoftData->m_bCharge == TRUE)
		{
			nPosX += 2;
			CStringA strPosA;
			strPosA.Format("%d,%d", nPosX, nPosY);
			m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_CHARGE, "pos", strPosA);
			m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_CHARGE,TRUE);
			nPosX += 45;
		}
		if (pSoftData->m_bPlug == TRUE)
		{
			nPosX += 2;
			CStringA strPosA;
			strPosA.Format("%d,%d", nPosX, nPosY);
			m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_PLUGIN, "pos", strPosA);
			m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_PLUGIN,TRUE);
			nPosX += 45;
		}
		if ((pSoftData->m_attri&SA_New) == SA_New)
		{
			nPosX += 2;
			CStringA strPosA;
			strPosA.Format("%d,%d", nPosX, nPosY);
			m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_NEW, "pos", strPosA);
			m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_NEW,TRUE);
		}

		if (pSoftData != NULL)
		{
			// 图标的绘制
			if (TRUE)
			{
				CStringA	strMem;
				strMem.Format("%d",pSoftData->m_pImage);
				m_necessList->SetItemAttribute( IDC_SOFTMGR_LISTTMP_ICON_SOFT, "mempointer",strMem );
			}
			
			//画评分
			for (int i = IDC_SOFTMGR_LISTTMP_STAR_ONE; i <= IDC_SOFTMGR_LISTTMP_STAR_FIVE; i++)
			{
				CStringA strSkin;
				if ((i - IDC_SOFTMGR_LISTTMP_STAR_ONE + 1)*2 <= pSoftData->m_fMark)
					strSkin = "star";
				else if ((i - IDC_SOFTMGR_LISTTMP_STAR_ONE + 1)*2 - 1 <= pSoftData->m_fMark)
					strSkin = "star_half";
				else
					strSkin = "star_off";
				
				m_necessList->SetItemAttribute(i, "skin", strSkin);
			}

			CString strMark;
			strMark.Format(L"%.1f分 投票", pSoftData->m_fMark);
			m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_MARK, strMark);

			// 下载图标
			if (!pSoftData->m_bIcon)
				m_pSoftMgrMainUI->OnDownLoadIcon( pSoftData->m_strSoftID );

			// 标题，描述，大小
			m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_TITLE, pSoftData->m_strName);
			m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_DESC, pSoftData->m_strDescription);
			m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_SIZE, pSoftData->m_strSize);
			m_necessList->SetItemStringAttribute(IDC_SOFTMGR_LISTTMP_TXT_SOFT_DESC,"tip",pSoftData->m_strDescription);
			m_necessList->SetItemStringAttribute(IDC_SOFTMGR_LISTTMP_TXT_SOFT_TITLE,"tip",BkString::Get(IDS_SOFTMGR_8100));
			m_necessList->SetItemStringAttribute(IDC_SOFTMGR_LISTTMP_ICON_SOFT,"tip",BkString::Get(IDS_SOFTMGR_8100));

			if (pSoftData->m_bUpdate)
			{
				CDC dcx = GetDC(m_pMainDlg->m_hWnd);
				HFONT			hFntTmp;
				hFntTmp = dcx.SelectFont(BkFontPool::GetFont(BKF_DEFAULTFONT));

				CRect rcProb;
				dcx.DrawText(pSoftData->m_strDescription, -1, &rcProb, DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);

				dcx.SelectFont(hFntTmp);
				ReleaseDC(m_pMainDlg->m_hWnd, dcx);

				CRect rcWin;
				GetWindowRect(m_necessList->m_hWnd, &rcWin);

				int nPos = 0;
				CStringA strPosDes;
				CStringA strPosNew;
				if (rcProb.Width() > rcWin.Width() - 50 - 310 - 50 - 2)
				{
					strPosDes = "50,32,-52,47";
					strPosNew = "-50,32,-0,47";
				}
				else
				{
					strPosDes.Format("50,32,%d,47", 50 + rcProb.Width());
					strPosNew.Format("%d,32,-0,47", 50 + rcProb.Width() + 2);
				}
				m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_TXT_SOFT_DESC, "pos", strPosDes);
				m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_TXT_SOFT_NEW, "pos", strPosNew);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_NEW,TRUE);
			}
			else
			{
				m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_TXT_SOFT_DESC, "pos", "50,32,-0,47");
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_NEW,FALSE);
			}

			if ( /*!pSoftData->m_bSetup && */pSoftData->m_bDownloading && !pSoftData->m_bWaitDownload && !pSoftData->m_bUsingForOneKey )
			{
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_SIZE,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_MARK,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_MARK,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_DOWN,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_UPDATE,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_REINST,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_USE_ONKEY,FALSE);

				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_PROG_DOWN_DOWNING,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_DOWN_PROG,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_SOFT_DOWNING_DOWN,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_SOFT_DOWNING_DOWNED,FALSE);

				CStringA	strProg;
				strProg.Format("%d",pSoftData->m_dwProgress);
				m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_PROG_DOWN_DOWNING,"value",strProg);

				if (pSoftData->m_bLinking)
				{				 
					if (pSoftData->m_bLinkFailed)
						m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_DOWN_PROG,BkString::Get(IDS_SOFTMGR_8089));
					else
						m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_DOWN_PROG,BkString::Get(IDS_SOFTMGR_8090));				
				}
				else
				{
					strProg += "%";
					m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_DOWN_PROG, CA2W(strProg) );
				}

				if ( !pSoftData->m_bDownLoad )
				{
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_PROG_DOWN_DOWNING,TRUE);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_DOWN_PROG,TRUE);
					// 正在下载中的
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_SOFT_DOWNING_DOWN,TRUE);

					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_LNK_SOFT_RETRY,FALSE);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_FEEDBACK,FALSE);
					if (pSoftData->m_bLinking)
					{
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_DOWN_STATE,FALSE);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWN_PAUSE,FALSE);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWN_CONTINUE,FALSE);

						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWN_STOP,!pSoftData->m_bLinkFailed);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_LNK_SOFT_RETRY,pSoftData->m_bLinkFailed);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_FEEDBACK,pSoftData->m_bLinkFailed);
					}
					else
					{
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_DOWN_STATE,TRUE);
						if (pSoftData->m_bPause)
							m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_DOWN_STATE,BkString::Get(IDS_SOFTMGR_8091));				
						else 
							m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_DOWN_STATE,pSoftData->m_strSpeed);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWN_PAUSE,!pSoftData->m_bPause);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWN_CONTINUE,pSoftData->m_bPause);
					}
				}
				else
				{
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_SIZE,TRUE);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_MARK,TRUE);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_MARK,TRUE);

					// 已下载完毕的
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_SOFT_DOWNING_DOWNED,TRUE);

					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWNED_INSTALL,FALSE);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_INST_STATE,TRUE);

					if (pSoftData->m_bWaitInstall)
						m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_INST_STATE,BkString::Get(IDS_SOFTMGR_8102));
					else if (pSoftData->m_bInstalling)
						m_necessList->SetItemText(IDC_SOFTMGR_LISTTMP_TXT_SOFT_INST_STATE,BkString::Get(IDS_SOFTMGR_8085));
					else
					{
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_INST_STATE,FALSE);
						m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_DOWNED_INSTALL,TRUE);
					}

					if ((pSoftData->m_attri&SA_Green) == SA_Green)
					{
						m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_BTN_DOWNED_INSTALL, "class", "btndetaildownloaded");
					}
					else
					{
						m_necessList->SetItemAttribute(IDC_SOFTMGR_LISTTMP_BTN_DOWNED_INSTALL, "class", "btndetaildown");
					}
				}
			}
			else
			{
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_SIZE,TRUE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_MARK,TRUE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_MARK,TRUE);

				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_PROG_DOWN_DOWNING,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_DOWN_PROG,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_SOFT_DOWNING_DOWN,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_DIV_SOFT_DOWNING_DOWNED,FALSE);

				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_DOWN,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_UPDATE,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_REINST,FALSE);
				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_USE_ONKEY,FALSE);

				if (!pSoftData->m_bUsingForOneKey)
				{
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_DOWN,!pSoftData->m_bUpdate&&!pSoftData->m_bSetup);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_UPDATE,pSoftData->m_bUpdate);
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_BTN_SOFT_REINST,pSoftData->m_bSetup&&!pSoftData->m_bUpdate);
				}
				else
				{
					m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_USE_ONKEY,TRUE);
				}

				m_necessList->SetItemVisible(IDC_SOFTMGR_LISTTMP_TXT_SOFT_CHARGE,FALSE);
			}
		}	
	}
	

	return 0;
}