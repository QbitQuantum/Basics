bool CModeratePostsBuilder::Build(CWholePage* pWholePage)
{
	InitPage(pWholePage, "POST-MODERATION", true);
	bool bSuccess = true;

	// do an error page if not an editor or moderator.
	CUser* pViewer = m_InputContext.GetCurrentUser();
	if (pViewer == NULL || !(pViewer->GetIsEditor() || pViewer->GetIsModerator()) )
	{
		bSuccess = bSuccess && pWholePage->SetPageType("ERROR");
		bSuccess = bSuccess && pWholePage->AddInside("H2G2", "<ERROR TYPE='NOT-EDITOR'>You cannot perform moderation unless you are logged in as an Editor or Moderator.</ERROR>");
		return true;
	}

	//Process Actions.
	if ( ! Process(pWholePage,pViewer) )
	{
		SetDNALastError("CModeratePostsBuilder::Build","Build","Unable to process");
		pWholePage->AddInside("H2G2",GetLastErrorAsXMLString());
	}

	//Handle s_returnto.
	if ( bSuccess && CheckAndUseRedirectIfGiven(pWholePage) )
		return bSuccess;

	//Handle 'Oldstyle' redirect - necessary to handle multiple submit buttons for the same form.  
	if ( m_InputContext.ParamExists("Done") )
	{
		CTDVString sRedirect = "Moderate?newstyle=1";
		if ( m_InputContext.GetParamInt("fastmod") == 1 )
			sRedirect += "&fastmod=1";
		return pWholePage->Redirect(sRedirect);
	}

	//Produce XML for page.

	// find out if we are processing referrals or not
	bool bReferrals = m_InputContext.GetParamInt("Referrals") == 1;
	bool bAlerts = m_InputContext.GetParamInt("Alerts") == 1;
	bool bLockedItems = m_InputContext.GetParamInt("Locked") == 1; //Viewing users locked items only.
	bool bHeldItems = m_InputContext.GetParamInt("Held") == 1;
	int iShow = 10;
	if ( m_InputContext.ParamExists("show") )
		iShow = m_InputContext.GetParamInt("show");
	
	bool bFastMod = m_InputContext.GetParamInt("fastmod") != 0;

	int iModClassId = 0;
	if ( m_InputContext.ParamExists("ModClassId") )
		iModClassId = m_InputContext.GetParamInt("ModClassId");

	//Filter on moderation items for a specific post.
	int iPostId = 0;
	if ( m_InputContext.ParamExists("PostFilterId") )
		iPostId = m_InputContext.GetParamInt("PostFilterId");

	//Add Moderation Classes
	CModerationClasses modclasses(m_InputContext);
	if ( modclasses.GetModerationClasses() )
		bSuccess = bSuccess && pWholePage->AddInside("H2G2",&modclasses);
	else if ( modclasses.ErrorReported() )
		bSuccess && bSuccess && pWholePage->AddInside("H2G2",modclasses.GetLastErrorAsXMLString() );

	//Add Moderation Failure - Reasons
	CModReasons reasons(m_InputContext);
	if ( reasons.GetModReasons(iModClassId) )
		bSuccess = bSuccess && pWholePage->AddInside("H2G2",&reasons);

	//Add Refereee List
	CRefereeList referees(m_InputContext);
	if ( referees.FetchTheList() )
		bSuccess = bSuccess && pWholePage->AddInside("H2G2",&referees);

	//Add Site List
	//CTDVString sSiteXML;
	//bSuccess = bSuccess && m_InputContext.GetSiteListAsXML(&sSiteXML, 2);
	//bSuccess = bSuccess && pWholePage->AddInside("H2G2", sSiteXML);
	CBasicSiteList sitelist(m_InputContext);
	if ( !sitelist.PopulateList() )
		pWholePage->AddInside("H2G2",sitelist.GetLastErrorAsXMLString());
	else
		bSuccess = bSuccess && pWholePage->AddInside("H2G2",sitelist.GetAsXML2());

	//Add User Moderation Statuses
	CUserStatuses modstatuses(m_InputContext);
	if ( modstatuses.GetUserStatuses() )
		pWholePage->AddInside("H2G2",&modstatuses);
	else if ( modstatuses.ErrorReported() )
		pWholePage->AddInside("H2G2",modstatuses.GetLastErrorAsXMLString());

	//Add Distress Messages
	CModerationDistressMessages distressmsgs(m_InputContext);
	if ( distressmsgs.GetDistressMessages(iModClassId) )
		pWholePage->AddInside("H2G2",&distressmsgs);
	else
		pWholePage->AddInside("H2G2",distressmsgs.GetLastErrorAsXMLString() );


	CModeratePosts moderate(m_InputContext);
	if ( !moderate.GetPosts( pViewer->GetUserID(), bAlerts, bReferrals, bLockedItems, bHeldItems, iModClassId, iPostId,  iShow, bFastMod ) )
		pWholePage->AddInside("H2G2",moderate.GetLastErrorAsXMLString() );
	else
		pWholePage->AddInside("H2G2",&moderate);
	

	TDVASSERT(bSuccess, "CModeratePostsBuilder::Build() failed");
	return bSuccess;
}