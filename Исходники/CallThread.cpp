/*
呼叫业务顾问
*/
void CCallThread::OnCallBusc(CallerCmd& callerCmd)
{
	UINT winID = callerCmd.GetWindowId();//窗口ID
	callerCmd.SetSuccess(TRUE);
	//playsound,display
	SLZWindow Window; 
	BOOL flag = m_rInlineQueData.m_rWindowTable.QueryWindowById(winID,Window);
	if(!flag)return;
	CString callName = Window.GetWindowCallName();
	CString strMsg;
	callName.Remove(_T('号'));
	callName.Remove(_T('窗'));
	callName.Remove(_T('口'));
	strMsg.Format(_T("#请#业务顾问#到#%s#号窗口"),callName);
	theApp.m_Controller.m_pPlaySound->DataPlay(strMsg);
}