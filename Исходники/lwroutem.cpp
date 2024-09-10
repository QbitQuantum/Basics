void	LWRouteMain::RefreshButtons()
{
  	if (Todays_Packages.hiwp != UID_Null)
	{
		info_waypoint* wp=*Persons2::ConvertPtrUID(Todays_Packages.hiwp);

		CRButton*	but;
		but = GETDLGITEM(IDC_RBUTTONINSERT);
		if (		(wp->uid.Evaluate() == -SGR_WPP_TakeOff)
				||	(wp->uid.Evaluate() == -SGR_WPP_EscDisperse)
				||	(wp->uid.Evaluate() == -SGR_WPP_BombDisperse)
				||	(wp->uid.Evaluate() == -SGR_WPP_Landing)
				||	(wp->uid.Evaluate() == -SGR_WPC_TakeOff)
				||	(wp->uid.Evaluate() == -SGR_WPC_Landing)

			)
		{
   			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}else
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
			but->SetDisabled(false);
		}


		but = GETDLGITEM(IDC_RBUTTONDELETE);
		if (wp->uid.Evaluate() == GOT_UNDEFINED_VAL)				//user wp
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetDisabled(false);
			but->SetBackColor(RGB(255,255,0));
		}else
		{
   			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}

		but = GETDLGITEM(IDC_RBUTTONCENTRE);
		but->SetForeColor(RGB(255,255,0));
		but->SetBackColor(RGB(255,255,0));
		but->SetDisabled(false);

		but = GETDLGITEM(IDC_RBUTTONNEWDOGLEG);
		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		{
			but->ShowWindow(true);
			if (Todays_Packages.pack[Todays_Packages.hipack].packagestatus < Profile::PS_TAKINGOFF)
			{
				but->SetForeColor(RGB(255,255,0));
				but->SetBackColor(RGB(255,255,0));
				but->SetDisabled(false);
			}else
			{
				but->SetForeColor(RGB(160,160,0));
				but->SetBackColor(RGB(160,160,0));
				but->SetDisabled(true);
			}
		}else
		{
			but->ShowWindow(false);
		}
		but = GETDLGITEM(IDC_RBUTTONAPPLYALT);
		but->SetForeColor(RGB(255,255,0));
		but->SetBackColor(RGB(255,255,0));
		but->SetDisabled(false);

	}else
	{
		CRButton*	but = GETDLGITEM(IDC_RBUTTONINSERT);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONDELETE);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONCENTRE);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONNEWDOGLEG);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONAPPLYALT);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
	}


}