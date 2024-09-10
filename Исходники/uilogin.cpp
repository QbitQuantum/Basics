void UILogin::onLogin()
{
	QString qstrName = m_pLedit->text();
	strcpy_s(g_name,CONST_MAX_NAME_LEN,qstrName.toLocal8Bit());
	CPReqLogin rlogin;
	INIT_CP(rlogin);
	strcpy_s(rlogin.name,CONST_MAX_NAME_LEN,g_name);
	client.Send(EPReq_Login,rlogin);
	//emit onLoginClicked(qstrName);
}