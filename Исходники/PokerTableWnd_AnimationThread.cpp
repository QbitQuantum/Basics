bool	
PokerTableWnd::AnimateCollectChips(WinThread* pThread, CollectChipsAnimationInfo* pAnimationInfo){
	int 			nSecAnimate	= pAnimationInfo->m_nAnimationSec;
	int 			nFrameCt	= 15;
	int				nSkipFrames	= 0;
	int 			nLoop		= 0;
	int 			nCt			= m_nMaxPlayerCt;
	int 			nMainChips	= pAnimationInfo->m_nMainChipsAmount;
	int				nChipsCt	= 0;

	float			fArrPosX[]	= {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float			fArrPosY[]	= {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	CRect			rcChips	[]	= {CRect(0, 0, 0, 0), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0),
								   CRect(0, 0, 0, 0), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0)};

	// Collect chips controls.
	ESChildControlChips* pMainChips = GetMainChipsControl();
	ESChildControlChips* ppChips[]	= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

// Crush
//	pMainChips = NULL;

	while( nLoop < nCt ){
		PokerTableSeatInfo* pSeat = GetSeatInfo(nLoop);
		if( !pSeat || pSeat->GetPotAmount() <= 0 ){
			nLoop ++;
			continue;
			}

		ppChips[nLoop] = GetChipsControl(nLoop);
		if( ppChips[nLoop] ){
			if( ppChips[nLoop]->GetAmount() <= 0 ){
				ppChips[nLoop] = NULL;
				}
			else{
				rcChips[nLoop]	= ppChips[nLoop]->GetClientRect();
				fArrPosX[nLoop] = ppChips[nLoop]->GetLogicalPosX();
				fArrPosY[nLoop] = ppChips[nLoop]->GetLogicalPosY();
				nChipsCt		++;
				}
			}
		
		nLoop ++;
		}
	// }}

	if( !nChipsCt ){
		PostMessage(WM_COLLECT_CHIPS_FINISHED, 0, 0);
		return true; // Stop animation.
		}

	// Collect chips sound.
	PokerGUI::GetInstance()->PlaySoundByType(SoundTypes::Sound_ChipsMovedToPot, 1, 0);

	// Animation movement(s)
	int		nFrame = 0;
	CRect	rcChipsBound;
	float	fDelay		= 1000.0f / ((float)(nFrameCt / ((float)nSecAnimate)));
	float   fAccelerate = 0.97f;

	while( nFrame < nFrameCt ){
		int nLoop1 = 0;
		if( (nFrame + nSkipFrames) == nFrameCt )
			break;

		rcChipsBound.SetRect(MAXINT,MAXINT,MAXINT,MAXINT);

		CPtrArray* pArrRects = new CPtrArray();
		while( nLoop1 < nCt ){
			if( !ppChips[nLoop1] ){
				nLoop1 ++;
				continue;
				}

			if( pThread->IsStopEventSignaled() ){
				// Finished.
				PostMessage(WM_COLLECT_CHIPS_FINISHED, 0, 0);
				return true; // Stop animation.
				}

			CRect	rcMainChips	= pMainChips->GetClientRect();
			CPoint	ptMiddle(rcMainChips.left + rcMainChips.Width()/2, rcMainChips.top + rcMainChips.Height()/2);

			ESChildControlChips*	pChips		= ppChips[nLoop1];
			CRect					rcRectChips	= pChips->GetClientRect();
			CRect					rcChipOrig	= rcChips[nLoop1];
			CPoint					ptMiddleChips (rcChipOrig.left + rcChipOrig.Width()/2, rcChipOrig.top + rcChipOrig.Height()/2);
			int						nMoveCY		= ptMiddle.y - ptMiddleChips.y;
			int						nMoveCX		= ptMiddle.x - ptMiddleChips.x;
			int						nOffsetY	= rcChipOrig.top + (nMoveCY / nFrameCt)*(nFrame + 1);
			int						nOffsetX	= rcChipOrig.left + (nMoveCX / nFrameCt)*(nFrame + 1);

			CRect rcTableWnd;
			GetClientRect(rcTableWnd);

			float fY = (nOffsetY*1.0f) / ((float)rcTableWnd.Height());
			float fX = (nOffsetX*1.0f) / ((float)rcTableWnd.Width());

			pChips->SetLogicalPos			(fX, fY);
			pChips->OwnerWindowSizeChanged	(rcTableWnd.Width(), rcTableWnd.Height());
			
			rcRectChips |= pChips->GetClientRect();
			pThread->Lock(); // Lock
			pArrRects->Add(new CRect(rcRectChips.left, rcRectChips.top, rcRectChips.right, rcRectChips.bottom));
			pThread->Unlock(); // Unlock

			rcChipsBound |= rcRectChips;
			nLoop1 ++;
			}

		if( rcChipsBound.Width() < 300 ){
			for(int i=0; i<pArrRects->GetCount(); i++){
				CRect* pRect = (CRect*)pArrRects->GetAt(i);
				delete pRect;
				}
			pArrRects->RemoveAll();
			CRect* pRectBound = new CRect(rcChipsBound);
			pArrRects->Add(pRectBound);
			::PostMessage(GetSafeHwnd(), WM_REDRAW_RECT, 1, (LPARAM)pArrRects);
			}
		else{
			::PostMessage(GetSafeHwnd(), WM_REDRAW_RECT, 1, (LPARAM)pArrRects);
			}
		
//		int nSleep = (int)(fDelay*fAccelerate);
		Sleep(30);
//		fAccelerate *= fAccelerate;
		nFrame		++;
		}

	// Wait
	Sleep(10);

	// Clear seat pot amounts.
	int nLoop1 = 0;
	while( nLoop1 < nCt ){
		if( !ppChips[nLoop1] ){
			nLoop1 ++;
			continue;
			}

		ESChildControlChips*	pChips		= ppChips[nLoop1];
		CRect					rcRectChips	= pChips->GetClientRect();

		CRect rcTableWnd;
		GetClientRect(rcTableWnd);
		
		pChips->SetAmount				(0, false);
		pChips->SetLogicalPos			(fArrPosX[nLoop1], fArrPosY[nLoop1]);
		pChips->OwnerWindowSizeChanged	(rcTableWnd.Width(), rcTableWnd.Height());
		nLoop1 ++;
		}

	if( pThread->IsStopEventSignaled() ){
		PostMessage(WM_COLLECT_CHIPS_FINISHED, 0, 0);
		return true; // Stop animation.
		}

	pThread->Lock(); // Lock
	// Redraw all chips area at once.
	CPtrArray* pArrRects = new CPtrArray();
	pArrRects->Add(new CRect(rcChipsBound.left, rcChipsBound.top, rcChipsBound.right, rcChipsBound.bottom));
	CRect	rcMainChips	= pMainChips->GetClientRect();
	pArrRects->Add(new CRect(rcMainChips.left, rcMainChips.top, rcMainChips.right, rcMainChips.bottom));
	SetMainPotAmount	(nMainChips, false);
	::PostMessage(GetSafeHwnd(), WM_REDRAW_RECT, 1, (LPARAM)pArrRects);
	pThread->Unlock(); // Unlock

	Sleep(100);

	PostMessage(WM_COLLECT_CHIPS_FINISHED, 0, 0);
	return true;
	}