 BOOL CLoginWindow::Receive(SkinChangedParam param)
 {
	 try
	 {
		 if(!IsWindow()) return FALSE;
		 sLog("CLoginWindow::Receive");
		 CDuiString bgimage_ = param.bgimage;
		 DWORD bkcolor_ = param.bkcolor;
		 CControlUI* background = GetPaintMgr()->GetRoot();
		 if (background != NULL&&0!=bgimage_.Compare(background->GetBkImage()))
		 {
			 if (!param.bgimage.IsEmpty())
			 {
				 CDuiString sBkImage = bgimage_;

				 background->SetBkImage(sBkImage);
			 }
			 else
				 background->SetBkImage(_T(""));

			 background->SetBkColor(param.bkcolor);
		 }

		 return TRUE;
	 }
	 catch (...)
	 {
		 sLogError("CLoginWindow::Receive");
		 throw _T("CLoginWindow::Receive");
		 return FALSE;
	 }	
 }