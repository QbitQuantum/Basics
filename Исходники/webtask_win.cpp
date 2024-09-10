WebTask::WebTask( void )
{
	//	コンストラクタ
	//
	str_agent = NULL;
	mode = CZHTTP_MODE_NONE;
	hSession = NULL;
	proxy_local = 0;
	proxy_url[0] = 0;
	req_header = NULL;
	vardata = NULL;
	postdata = NULL;

	//	接続可能か?
	if( InternetAttemptConnect(0) ){
		SetError( "ネット接続が確認できませんでした" ); return;
	}

	//	初期化を行う
	Reset();
}