	BOOL WindowImplBase::IsInStaticControl(CControlUI *pControl)
	{
		BOOL bRet = FALSE;
		if (!pControl)
		{
			return bRet;
		}

		CDuiString strClassName;
		std::vector<CDuiString> vctStaticName;

		strClassName = pControl->GetClass();
		strClassName.MakeLower();
		vctStaticName.push_back(_T("controlui"));
		vctStaticName.push_back(_T("textui"));
		vctStaticName.push_back(_T("labelui"));
		vctStaticName.push_back(_T("containerui"));
		vctStaticName.push_back(_T("horizontallayoutui"));
		vctStaticName.push_back(_T("verticallayoutui"));
		vctStaticName.push_back(_T("tablayoutui"));
		vctStaticName.push_back(_T("childlayoutui"));
		vctStaticName.push_back(_T("dialoglayoutui"));
		vctStaticName.push_back(_T("progresscontainerui"));
		std::vector<CDuiString>::iterator it = std::find(vctStaticName.begin(), vctStaticName.end(), strClassName);
		if (vctStaticName.end() != it)
		{
			CControlUI* pParent = pControl->GetParent();
			while (pParent)
			{
				strClassName = pParent->GetClass();
				strClassName.MakeLower();
				it = std::find(vctStaticName.begin(), vctStaticName.end(), strClassName);
				if (vctStaticName.end() == it)
				{
					return bRet;
				}

				pParent = pParent->GetParent();
			}

			bRet = TRUE;
		}

		return bRet;
	}