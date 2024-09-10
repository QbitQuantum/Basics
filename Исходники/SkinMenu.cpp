//绘画函数
VOID CSkinMenuKernel::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//效验参数
	ASSERT(lpDrawItemStruct->CtlType==ODT_MENU);
	if (lpDrawItemStruct->CtlType!=ODT_MENU) return;

	//变量定义
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CSkinMenuItem * pSkinMenuItem=(CSkinMenuItem *)lpDrawItemStruct->itemData;

	//自绘框架
	if(m_bRemoveBorder==TRUE)
	{
		//区域偏移
		rcItem.OffsetRect(FRAME_OUT_CX+FRAME_IN_CX,FRAME_OUT_CY+FRAME_IN_CY);

		//变量定义
		CRect rcClient(0,0,0,0);		
		GetClientRect(m_hWnd,rcClient);

		//绘制外框
		pDC->FillSolidRect(0,0,rcClient.Width(),FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);
		pDC->FillSolidRect(rcClient.right-FRAME_OUT_CX,FRAME_OUT_CY,FRAME_OUT_CX,rcClient.Height()-FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);
		pDC->FillSolidRect(0,rcClient.Height()-FRAME_OUT_CY,rcClient.Width()-FRAME_OUT_CX,FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);
		pDC->FillSolidRect(0,FRAME_OUT_CY,FRAME_OUT_CX,rcClient.Height()-FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);

		//绘制内框
		pDC->FillSolidRect(FRAME_OUT_CX,FRAME_OUT_CY,rcClient.Width()-2*FRAME_OUT_CX,FRAME_IN_CY,m_SkinAttribute.m_crInFrame);
		pDC->FillSolidRect(rcClient.right-FRAME_OUT_CX-FRAME_IN_CX,FRAME_OUT_CY,FRAME_IN_CX,rcClient.Height()-2*FRAME_OUT_CY,m_SkinAttribute.m_crInFrame);
		pDC->FillSolidRect(FRAME_OUT_CX,rcClient.Height()-FRAME_OUT_CY-FRAME_IN_CY,rcClient.Width()-2*FRAME_OUT_CX,FRAME_IN_CY,m_SkinAttribute.m_crInFrame);
		pDC->FillSolidRect(FRAME_OUT_CX,FRAME_OUT_CY,FRAME_IN_CX,rcClient.Height()-2*FRAME_OUT_CY,m_SkinAttribute.m_crInFrame);
	}

	//状态变量
	bool bChecked=((lpDrawItemStruct->itemState&ODS_CHECKED)!=0);
	bool bSelected=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0);
	bool bGrayed=((lpDrawItemStruct->itemState&ODS_DISABLED)||(lpDrawItemStruct->itemState&ODS_GRAYED));

	//绘画背景
	COLORREF crMenuBar=m_SkinAttribute.m_crMenuBar;
	COLORREF crBorder=m_SkinAttribute.m_crSelectBorder;
	COLORREF crNormalBack=m_SkinAttribute.m_crNormalBack;
	pDC->FillSolidRect(rcItem.left,rcItem.top,MENU_BAR_CX,rcItem.Height(),m_SkinAttribute.m_crMenuBar);
	pDC->FillSolidRect(rcItem.left+MENU_BAR_CX,rcItem.top,rcItem.Width()-MENU_BAR_CX,rcItem.Height(),m_SkinAttribute.m_crNormalBack);	

	//焦点边框
	if ((bSelected==true)&&(bGrayed==false)&&(pSkinMenuItem!=NULL)&&(pSkinMenuItem->m_MenuItemType!=MenuItemType_Separator))
	{
		pDC->Draw3dRect(rcItem.left+1,rcItem.top+1,rcItem.Width()-2,rcItem.Height()-2,crBorder,crBorder);
		pDC->FillSolidRect(rcItem.left+2,rcItem.top+2,rcItem.Width()-4,rcItem.Height()-4,m_SkinAttribute.m_crSelectBack);
	}

	//选择标志
	if (bChecked==true)
	{
		//加载资源
		CBitImage ImageMenuFlags;
		ImageMenuFlags.LoadFromResource(GetModuleHandle(SKIN_CONTROL_DLL_NAME),IDB_SKIN_MENU_FLAGS);

		//渲染资源
		CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();
		if (pSkinRenderManager!=NULL) pSkinRenderManager->RenderImage(ImageMenuFlags);

		//绘画界面
		ImageMenuFlags.BitBlt(pDC->m_hDC,rcItem.left+1,rcItem.top+1,ImageMenuFlags.GetWidth()/2,
			ImageMenuFlags.GetHeight(),((bSelected==true)&&(bGrayed==false))?ImageMenuFlags.GetWidth()/2:0,0);
	}

	//其他菜单
	if (pSkinMenuItem==NULL)
	{
		//获取信息
		MENUITEMINFO MenuItemInfo;
		MenuItemInfo.cbSize=sizeof(MenuItemInfo);
		MenuItemInfo.fMask=MIIM_FTYPE|MIIM_BITMAP;
		GetMenuItemInfo(lpDrawItemStruct->itemID,&MenuItemInfo);

		return;
	}

	//界面菜单
	switch (pSkinMenuItem->m_MenuItemType)
	{
	case MenuItemType_Image:		//图形菜单
		{
			//变量定义
			CSkinMenuImage * pSkinMenuImage=(CSkinMenuImage *)pSkinMenuItem;

			//创建 DC
			CDC ImageDC;
			ImageDC.CreateCompatibleDC(pDC);
			ImageDC.SelectObject(pSkinMenuImage->m_hBitmap);

			//获取信息
			BITMAP BitmapInfo;
			GetObject(pSkinMenuImage->m_hBitmap,sizeof(BitmapInfo),&BitmapInfo);

			//绘画位图
			INT nYPos=rcItem.top+3;
			INT nXPos=rcItem.left+MENU_BAR_CX+SPACE_LEFT;
			pDC->BitBlt(nXPos,nYPos,BitmapInfo.bmWidth,BitmapInfo.bmHeight,&ImageDC,0,0,SRCCOPY);

			//释放 DC
			ImageDC.DeleteDC();

			break;
		}
	case MenuItemType_String:		//字符菜单
		{
			//变量定义
			CSkinMenuString * pSkinMenuString=(CSkinMenuString *)pSkinMenuItem;

			//设置颜色
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

			//设置颜色
			if (bGrayed==true) pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
			else if (bSelected==true) pDC->SetTextColor(m_SkinAttribute.m_crSelectText);
			else pDC->SetTextColor(m_SkinAttribute.m_crNormalText);

			//绘画字符
			CRect rcString;
			rcString.top=rcItem.top;
			rcString.bottom=rcItem.bottom;
			rcString.right=rcItem.right-SPACE_RIGHT;
			rcString.left=rcItem.left+MENU_BAR_CX+SPACE_LEFT;
			pDC->DrawText(pSkinMenuString->m_strString,pSkinMenuString->m_strString.GetLength(),&rcString,DT_SINGLELINE|DT_VCENTER|DT_NOCLIP);

			break;
		}
	case MenuItemType_Separator:	//拆分菜单
		{
			//绘画拆分
			pDC->FillSolidRect(rcItem.left+MENU_BAR_CX+SPACE_LEFT,rcItem.top+1,rcItem.Width()-MENU_BAR_CX-SPACE_LEFT-SPACE_RIGHT,
				rcItem.Height()-2,m_SkinAttribute.m_crSeparator);

			break;
		}
	}

	return;
}