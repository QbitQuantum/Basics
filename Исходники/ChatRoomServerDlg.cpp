/// 接收文本消息
void CChatRoomServerDlg::ReceiveText( CHATROOMMESSAGEINFO CRMInfo, char *pData, DWORD dwTextLength )
{
	pData[ dwTextLength ] = 0;
	for( int nIndex = 1; nIndex < m_arrFriendsInChat.GetSize(); nIndex++ )
	{
		USER userSrc = m_arrFriendsInChat.GetAt( nIndex );
		if( 0 == strcmp( userSrc.strIP, CRMInfo.szSrcIP ) )
		{
			CString strText;
			strText.Format( "%s(%s) %s\r\n  %s\r\n\r\n",
				userSrc.strName,
				userSrc.strIP,
				CRMInfo.szTime,
				pData );
			CString strReceiveText;
			m_editReceived.GetWindowText( strReceiveText );
			m_editReceived.SetWindowText( strReceiveText + strText );
			m_editReceived.LineScroll( m_editReceived.GetLineCount() );
			FlashWindow( TRUE );
			
			CString strSend( pData );

			/// 向所有客户端发送消息
			for( int nIndex1 = 1; nIndex1 < m_arrFriendsInChat.GetSize(); nIndex1++ )
			{
				USER userSend = m_arrFriendsInChat.GetAt( nIndex1 );
				if( 0 == strcmp( userSrc.strIP, userSend.strIP ) )
				{
					continue;
				}
				SendTextToIP( userSend.strIP, CHATROOM_CLIENT_PORT, strSend, userSrc.strIP );
			}
			break;
		}
	}	
}