void CBitmapListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->CtlType==ODT_LISTVIEW)
	{
		//TCHAR sz[100];
		//wsprintf(sz,"%d",(lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top));
		//MessageBox(sz);
		//获取数据
		UINT iWidth=0;
		TCHAR szBuffer[30];
		memset(szBuffer,0,sizeof(szBuffer));
		CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
		UserItemStruct * pUserItem=(UserItemStruct *)GetItemData(lpDrawItemStruct->itemID);
		CFont font;
		font.CreateFont(-12,0,0,0,700,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
		
		CFont *pOldFont = pDC->SelectObject(&font);	///< Modified by zxd 20100709 旧字体保存下来。

		//设置颜色
//		COLORREF crTextColor,crBackColor;
		bool bSelect=(lpDrawItemStruct->itemState&ODS_SELECTED)||(lpDrawItemStruct->itemState&ODS_FOCUS);
		//GetDrawColor(crTextColor,crBackColor,pUserItem,0,bSelect);
		//pDC->SetBkColor(crBackColor);
		//pDC->SetTextColor(crTextColor);
		pDC->SetBkMode(TRANSPARENT);
		//绘画信息
		CSize TextSize;
		CRect rect1;
		TCHAR szname[300];
		for (int i=0;i<m_ListHeader.GetItemCount();i++)
		{
			int iTemp=GetColumnWidth(i);
			TextSize=pDC->GetTextExtent(szBuffer,lstrlen(szBuffer));
			GetItemText(lpDrawItemStruct->itemID,i,szBuffer,sizeof(szBuffer));
			CRect TextRect(lpDrawItemStruct->rcItem.left+iWidth,lpDrawItemStruct->rcItem.top,lpDrawItemStruct->rcItem.left+iWidth+iTemp,lpDrawItemStruct->rcItem.bottom);
			CGameImageHelper help(&m_itembk);
			help.BitBlt(pDC->GetSafeHdc(),TextRect.left,TextRect.top);
			//头像
			rect1=m_rlog;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			CGameImage log;
			wsprintf(szname,".\\image\\log\\roomlistlog%d.bmp",pUserItem->GameUserInfo.bLogoID);
			//lstrcpy(szname,".\\image\\log\\log1.bmp");
			log.SetLoadInfo(szname,CGameImageLink::m_bAutoLock);
			CGameImageHelper helper(&log);
			//AFCStretchImage(pDC,rect1.left,rect1.top,rect1.Width(),rect1.Height(),helper,0,0,log.GetWidth(),log.GetHeight(),log.GetPixel(1,1));
			helper.BitBlt(pDC->GetSafeHdc(),rect1.left,rect1.top);
			helper.CloseGDIHandle();
			//名字
			rect1=m_rname;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			lstrcpy(szname,pUserItem->GameUserInfo.nickName);
			DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			//等级
			lstrcpy(szname,m_pGetOrderFun(pUserItem->GameUserInfo.dwPoint,0));
			rect1=m_rorder;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			//金币
			lstrcpy(szname,m_sztitle);
			rect1=m_rcoin;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			//经验值
			wsprintf(szname,"%d",pUserItem->GameUserInfo.dwPoint-GetNormalOrderBasePoint(pUserItem->GameUserInfo.dwPoint));
			rect1=m_rcoinc;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			//赢
			wsprintf(szname,"赢 %d",pUserItem->GameUserInfo.uWinCount);
			rect1=m_rwin;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			//输
			wsprintf(szname,"输 %d",pUserItem->GameUserInfo.uLostCount);
			rect1=m_rloss;
			rect1.OffsetRect(TextRect.left,TextRect.top);
			DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			//桌号
			if(pUserItem->GameUserInfo.bDeskNO!=255&&m_uComType!=TY_MATCH_GAME)
			{
				wsprintf(szname,"%d\n号\n桌",pUserItem->GameUserInfo.bDeskNO+1);
				rect1=m_rdesk;
				rect1.OffsetRect(TextRect.left,TextRect.top);
				DrawText(pDC->GetSafeHdc(),szname,lstrlen(szname),rect1,DT_CENTER|DT_VCENTER);
			}

			
			if(bSelect)
				PatBlt(pDC->GetSafeHdc(),TextRect.left,TextRect.top,TextRect.Width(),TextRect.Height(),DSTINVERT);
/*
			pDC->DrawText(szBuffer,lstrlen(szBuffer),&TextRect,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
			if (TextSize.cx<iTemp) 
			{
				pDC->FillSolidRect(lpDrawItemStruct->rcItem.left+iWidth+TextSize.cx,lpDrawItemStruct->rcItem.top,
					iTemp-TextSize.cx,lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top,crBackColor);
			}
			iWidth+=iTemp;*/
		}

		/// {{Added by zxd 20100709 释放GDI资源
		pDC->SelectObject(pOldFont);
		font.DeleteObject();
		/// Added by zxd 20100709 释放GDI资源}}
	}
	return;	
}