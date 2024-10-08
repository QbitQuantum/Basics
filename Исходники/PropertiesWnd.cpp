void CPropertiesWnd::SetUIValue(CMFCPropertyGridProperty* pProp,int nTag)
{
	CControlUI* pControl = m_wndUIProperties.GetCurUI();
	if(pControl == NULL)
		return;

	int nUpdate=UPDATE_REDRAW_CONTROL;
	CString strName=pProp->GetName();
	strName.MakeLower();
	CString strNewVal;
	CString strOldVal;
	strNewVal = pProp->FormatProperty();
	strOldVal = m_wndUIProperties.FormatOrigProperty(pProp);
	if(nTag!=tagName && nTag!=tagText && strName.Find(_T("image"))==-1)
	{
		strNewVal.MakeLower();
		strOldVal.MakeLower();
	}

	switch(nTag)
	{
	case tagName:
		{
			CPaintManagerUI* pManager = g_pMainFrame->GetActiveUIView()->GetPaintManager();
			if(strNewVal.IsEmpty() || pManager->FindControl(strNewVal))
			{
				if(!strNewVal.IsEmpty())
					MessageBox(strNewVal + _T(" 名称已被其他控件使用！"));
				pProp->SetValue((_variant_t)pControl->GetName());
				return;
			}
			else
				pManager->ReapObjects(pControl);

			g_pClassView->RenameUITreeItem(pControl, strNewVal);
			break;
		}
	case tagPos:
	case tagPadding:
		SetPropValue(pControl,tagSize);

		nUpdate=UPDATE_POS;
		break;
	case tagSize:
	case tagMinSize:
	case tagMaxSize:
	case tagMinMax:
		SetUIValue(pProp->GetSubItem(0),-1);
		SetUIValue(pProp->GetSubItem(1),-1);
		SetPropValue(pControl,tagPos);

		nUpdate=UPDATE_POS;
		break;
	case tagFloat:
	case tagColumns:
		nUpdate=UPDATE_POS;
		break;
	case tagVisible:
		nUpdate=UPDATE_REDRAW_PARENT;
		break;
	case tagListHeader:
		if (strNewVal.Compare(_T("false"))==0)
		{
			strNewVal = _T("hidden");
		}
		break;
	case tagAlpha:
		{
			int alpha=_ttoi(strNewVal);
			if (alpha<0)
			{
				strNewVal=_T("0");
				pProp->SetValue((_variant_t)(LONG)0);
			}
			else
			{
				strNewVal=_T("255");
				pProp->SetValue((_variant_t)(LONG)255);
			}
			break;
		}
	}

	CUIDesignerView* pUIView=g_pMainFrame->GetActiveUIView();
	ASSERT(pUIView);
	TNotifyUI Msg;
	UIAttribute oldAttrib = {strName, strOldVal};
	Msg.pSender=pControl;
	Msg.sType=_T("PropertyBeginChanged");
	Msg.wParam=0;
	Msg.lParam=(LPARAM)&oldAttrib;
	pUIView->Notify(Msg);

	pControl->SetAttribute(strName,strNewVal);
	pProp->SetOriginalValue(pProp->GetValue());

	UIAttribute newAttrib = {strName, strNewVal};
	Msg.sType = _T("PropertyEndChanged");
	Msg.lParam = (LPARAM)&newAttrib;
	pUIView->Notify(Msg);

	if(nTag==tagWindowSize)
	{
		Msg.sType=_T("formsize");
		Msg.lParam = NULL;
		pUIView->Notify(Msg);
	}
	else if(nTag == tagName)
	{
		CPaintManagerUI* pManager = pUIView->GetPaintManager();
		pManager->InitControls(pControl);
	}

	CControlUI* pParent=pControl->GetParent();
	if(pParent==NULL)
		pParent=pControl;
	switch(nUpdate)
	{
	case UPDATE_POS:
		pParent->SetPos(pParent->GetPos());

		break;
	case UPDATE_REDRAW_CONTROL:
		pControl->NeedUpdate();

		break;
	case UPDATE_REDRAW_PARENT:
		pParent->NeedUpdate();
	}
}