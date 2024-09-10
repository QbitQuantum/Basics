void CSDKWithoutLoginStartJoinMeetingUIGroup::DoWithoutLoginStartJoinMeetingBtnClick()
{
	if(NULL == m_editMeetingNumber  || NULL == m_editMeetingPassword || NULL == m_editScreenName )
		return;
	ZOOM_SDK_NAMESPACE::tagJoinParam joinParam;
	joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_WITHOUT_LOGIN;
	ZOOM_SDK_NAMESPACE::JoinParam4WithoutLogin& withoutloginParam = joinParam.param.withoutloginuserJoin;
	std::wstring MeetingNumber = m_editMeetingNumber->GetText().GetData();
	std::wstring MeetingPassword = m_editMeetingPassword->GetText().GetData();
	std::wstring ScreenName = m_editScreenName->GetText().GetData();
	withoutloginParam.meetingNumber = _wtoi64(MeetingNumber.c_str());
	withoutloginParam.vanityID = NULL;
	withoutloginParam.userName = ScreenName.c_str();
	withoutloginParam.psw = MeetingPassword.c_str();
	withoutloginParam.hDirectShareAppWnd = NULL;
	withoutloginParam.toke4enfrocelogin = NULL;
	withoutloginParam.participantId = NULL;
	withoutloginParam.webinarToken = NULL;
	withoutloginParam.isDirectShareDesktop = false;
	withoutloginParam.isVideoOff = false;
	withoutloginParam.isAudioOff = false;

	if(MeetingNumber.size() > 0)
	{
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
			m_parentFrame->SwitchToWaitingPage(_T("waiting to join meeting..."),true);
		}
		
		if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode())
		{
			CSDKDemoAppEvent* pAppEvent = m_parentFrame->GetAppEvent();
			if(pAppEvent)
				pAppEvent->InitCustomizedUI();
		}
		
		bool ret = m_withoutLoginJoinMeetingWorkFlow.JoinMeeting(joinParam);
		if(ret)
		{
			m_bInMeeting = true;
		}
		return;
	}
	if (m_parentFrame)
	{
		if(MeetingNumber.size() <=0)
		{
			m_parentFrame->ShowErrorMessage(_T("Meeting number could not be NULL!"));
			m_editMeetingNumber->SetFocus();
		}
		else
		{
			m_parentFrame->ShowErrorMessage(_T("Join meeting failed!"));
		}
		m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
		m_parentFrame->SwitchToWaitingPage(_T("waiting to join meeting...."), false);
		m_bInMeeting = false;
	}
}