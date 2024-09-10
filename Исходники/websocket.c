/**
 * Main Websockets thread
 *
 * @param data pointer to Websockets thread
 * @return 0 when success, otherwise error number
 */
int WebsocketThread( FThread *data )
{
	int cnt = 0;
	WebSocket *ws = (WebSocket *)data->t_Data;
	if( ws->ws_Context == NULL )
	{
		FERROR("WsContext is empty\n");
		return 0;
	}
	
	DEBUG1("[WS] Websocket thread started\n");
	
	//signal( SIGPIPE, SIG_IGN );
	//signal( SIGPIPE, hand );

	//lws_set_log_level( LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG , NULL );
	
	Log( FLOG_INFO, "[WS] Service will be started now\n" );

	while( TRUE )
	{
		int n = lws_service( ws->ws_Context, 500 );
		
		if( ws->ws_Quit == TRUE && WSThreadNum <= 0 )
		{
			break;
		}
		else if( ws->ws_Quit == TRUE )
		{
			cnt++;
			
			if( cnt > 500 )
			{
				Log( FLOG_INFO, "[WS] Service stopping threads: %d\n", WSThreadNum );
				cnt = 0;
			}
		}
	}
	Log( FLOG_INFO, "[WS] Service stopped\n" );

done:
	data->t_Launched = FALSE;
	return 0;
}