void CGrammarTopicOrderDlg::OnTimer(UINT nIDEvent) 
{
	int j,k,nTreeTop,nTreeHeight,nLeft;
	UINT i;
	UINT* pFlags;
	BOOL b;
	CRect rect;
	HTREEITEM hFirstVisible,hNextVisible,hTest;
	CWnd* pWnd;
	CDC* pDC;
	LPRECT lpRect;
	LPPOINT lpPoint;
	CPoint pt,ptSave;
	HWND  hWnd;            //handle of this window

	lpRect=&rect;
	lpPoint=&pt;
	pFlags=&i;
	pWnd=this;
	hWnd=pWnd->GetSafeHwnd();
	pWnd->GetWindowRect(lpRect);
	nLeft=rect.left;
	pWnd=&m_ctrltreeTopics;
	hWnd=pWnd->GetSafeHwnd();
	pWnd->GetWindowRect(lpRect);
	nTreeTop=rect.top;
	nTreeHeight=rect.bottom-rect.top;
//	nTreeHeight=rect.bottom-rect.top-25;
	GetCursorPos(lpPoint);    //get the mouse's position
	SetTimer (1,400,NULL);     //reset timer to 400 msecs for subsequent scrolls
    // Get the current cursor position and window height.
    // Scroll the window if the cursor is near the top or bottom
	pt.y-=nTreeTop;
	ptSave=pt;
	if (pt.y>=0 && pt.y<=15) //if cursor still in tree but near top
	{
		hFirstVisible=m_pTree->GetFirstVisibleItem();
		hNextVisible=m_pTree->GetPrevSiblingItem(hFirstVisible);
		m_pTree->EnsureVisible(hNextVisible);
		//kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
		if (m_pTree->GetFirstVisibleItem()==hFirstVisible)  //tree didn't scroll
		{
			hNextVisible=m_pTree->GetParentItem(hFirstVisible);  //move up to root node
			m_pTree->EnsureVisible(hNextVisible);
			KillTimer (1);
		}
		else
		{
			pDC=pWnd->GetDC();
			pWnd->RedrawWindow();  //erase the previously drawn drag image
			pt.y-=10;
			pt.x-=nLeft;    //200;
			b=m_pDragImage->Draw(pDC,0,pt,ILD_NORMAL);  //draw the new drag image
			hTest=m_pTree->HitTest(ptSave,pFlags);
			if (hTest!=NULL)
			{
				b=m_pTree->SelectDropTarget(hTest); 
				hDropTarget=hTest;   //save for LButtonUp
				b=m_pDragImage->Draw(pDC,0,pt,ILD_NORMAL);
			}
		}
	}
	else if (pt.y>=nTreeHeight-10 && pt.y<=nTreeHeight)
	{
//		hFirstVisible=m_pTree->GetDropHilightItem( );   //get item currently highlighted
//		hNextVisible=m_pTree->GetNextSiblingItem(hFirstVisible);  //get the next item
		hNextVisible=m_pTree->GetFirstVisibleItem();
		k=m_pTree->GetVisibleCount();
		for (j=0;j<k;j++) hNextVisible=m_pTree->GetNextVisibleItem(hNextVisible);
		m_pTree->EnsureVisible(hNextVisible);           //scroll down to next item
		pDC=pWnd->GetDC();
		pWnd->RedrawWindow();  //erase the previously drawn drag image
		pt.y-=20;
		pt.x-=nLeft;    //200;
		b=m_pDragImage->Draw(pDC,0,pt,ILD_NORMAL);  //draw the new drag image
ptSave.y=pt.y;
		hTest=m_pTree->HitTest(ptSave,pFlags);
//		hTest=m_pTree->HitTest(pt,pFlags);
		if (hTest!=NULL)
		{
			b=m_pTree->SelectDropTarget(hTest); 
			hDropTarget=hTest;   //save for LButtonUp
			b=m_pDragImage->Draw(pDC,0,pt,ILD_NORMAL);
		}
	}
//	CDialog::OnTimer(nIDEvent);
}