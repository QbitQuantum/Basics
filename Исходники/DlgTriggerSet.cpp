void CDlgTriggerSet::SelectCase(int nIndex, BOOL bShowImage)
{
	CBitmap bitmap;  // CBitmap对象，用于加载位图   
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄
    CString str;
    BOOL bUseHSC = FALSE;
	BOOL bTimeDelay = FALSE;
    m_CkTriggerMode.EnableWindow(TRUE);
    SetDlgItemText(IDC_STATIC_WAVECNT, "抓拍个数");
	switch(nIndex)
	{
	case 0:
		bitmap.LoadBitmap(IDB_BITMAP_CASE1);
        bUseHSC = TRUE;
		break;
	case 1:
		bitmap.LoadBitmap(IDB_BITMAP_CASE2);
		bTimeDelay = TRUE;
		break;
	case 2:
		bitmap.LoadBitmap(IDB_BITMAP_CASE3);
		bTimeDelay = TRUE;
		break;
	case 3:
		bitmap.LoadBitmap(IDB_BITMAP_CASE4);
        bUseHSC = TRUE;
		break;
	case 4:
		bitmap.LoadBitmap(IDB_BITMAP_CASE5);
        bUseHSC = TRUE;
		break;
	case 5:
		bitmap.LoadBitmap(IDB_BITMAP_CASE6);
		bTimeDelay = TRUE;
		break;
	case 6:
        bUseHSC = TRUE;
		bTimeDelay = TRUE;
		bitmap.LoadBitmap(IDB_BITMAP_CASE7);
		break;
	default:
        bUseHSC = TRUE;
		bitmap.LoadBitmap(IDB_BITMAP_CASE1);
		break;
	}
    m_EditInfo.SetWindowText(g_CaseDescribe[nIndex]);
    m_ComBoWaveFrq.EnableWindow(bUseHSC);
    m_EditWaveCnt.EnableWindow(bUseHSC);
	m_EditTimeDelay.EnableWindow(bTimeDelay);
	m_EditDBClkFreq.EnableWindow(nIndex == 1);
    m_EditDBClkTimes.EnableWindow(nIndex == 1);

    if(nIndex == 1 || nIndex == 3 || nIndex == 4){                            // 1 快击 3 预览延迟 4 帧率
        m_CkTriggerMode.EnableWindow(FALSE);
    }else if(nIndex == 6){                                                    // 6 连续拍照
        SetDlgItemText(IDC_STATIC_WAVECNT, "持续时间(x10ms)");
        m_CkTriggerMode.EnableWindow(FALSE);
        m_ComBoWaveFrq.EnableWindow(FALSE);
    }

	ModuleTriggerMode *pTriggerModeSet = (ModuleTriggerMode*)m_pModuleData->pData;
    char chTemp[100];
    int nValue;
    str.Format("TRIGGERCASE%d", nIndex);
    m_CkTriggerMode.SetCheck(pTriggerModeSet->nTriggerMode);
	sprintf(chTemp, "%d", pTriggerModeSet->nTimeDelay);
    m_EditTimeDelay.SetWindowText(chTemp);
    m_ComBoWaveFrq.SetCurSel(pTriggerModeSet->nWaveFrq);
    sprintf(chTemp, "%d", pTriggerModeSet->nWaveCnt);
    m_EditWaveCnt.SetWindowText(chTemp);
	sprintf(chTemp, "%d", pTriggerModeSet->nDBClkFrq);
    m_EditDBClkFreq.SetWindowText(chTemp);
	sprintf(chTemp, "%d", pTriggerModeSet->nDBClkCnt);
    m_EditDBClkTimes.SetWindowText(chTemp);

    if(bShowImage){
	    hBmp = (HBITMAP)bitmap.GetSafeHandle();
        BITMAP bmpInfo;
        bitmap.GetObject(sizeof(bmpInfo),&bmpInfo);
        int nWidthImg = bmpInfo.bmWidth;
        int nHeightImg = bmpInfo.bmHeight;

	    //CDC *pDC = m_StaticPicture.GetDC();
        CDC *pDC = GetDC();
	    CRect rect;
        CRect rectClient;
	    m_StaticPicture.GetWindowRect(rect);
        rectClient = rect;
        ScreenToClient(&rectClient);
	    CDC DCCompatible;
	    DCCompatible.CreateCompatibleDC(pDC);
	    CBitmap *pOldBmp = DCCompatible.SelectObject(&bitmap);
    
        int nWidthRc = rect.Width();
        int nHeightRc = rect.Height();
        int nShowWd, nShowHt, nPosX, nPosY;
        if((nWidthImg > nWidthRc ) || (nHeightImg > nHeightRc)){            // 需要伸缩
            // need strech
            if(nHeightImg*nWidthRc > nWidthImg*nHeightRc){                  // 水平方向伸缩
                nShowHt = nHeightRc;
                nShowWd = nShowHt*nWidthImg/nHeightImg;
                nPosX = (nWidthRc - nShowWd)/2;
                nPosY = 0;
            }else{
                nShowWd = nWidthRc;
                nShowHt = nShowWd*nHeightImg/nWidthImg;
                nPosX = 0;
                nPosY = (nHeightRc - nShowHt)/2;
            }
        }else{
            nPosX = (nWidthRc - nWidthImg)/2;
            nPosY = (nHeightRc - nHeightImg)/2;
            nShowWd = nWidthImg;
            nShowHt = nHeightImg;
        }

        pDC->FillSolidRect(rectClient.left, rectClient.top, rect.Width(), rect.Height(), RGB(105,105,105));
        //pDC->Rectangle(0, 0, rect.Width(), rect.Height());
        //DCCompatible.FillRect(&rect, &m_brHatch);
	    pDC->SetStretchBltMode( HALFTONE );
	    pDC->StretchBlt(rectClient.left+nPosX, rectClient.top+nPosY, nShowWd, nShowHt, &DCCompatible, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY );

	    DCCompatible.SelectObject(pOldBmp);
    }
}