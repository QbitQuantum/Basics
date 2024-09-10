BOOL CMapiMail::SendMail()
{
	_ASSERT(m_hLibMail != NULL);

	BOOL bRet = FALSE;

	if(m_lhSession)
	{
	    MapiMessage msgSend;
	    memset(&msgSend, 0, sizeof(MapiMessage));
		msgSend.lpszSubject = "My Subject";		// LPSTR Message Subject
		msgSend.lpszNoteText = "<html><body><font size=12>Test</font></body></html>";		// LPSTR Message Text
//		msgSend.lpszMessageType;	// LPSTR Message Class
//		msgSend.lpszDateReceived;	// LPSTR in YYYY/MM/DD HH:MM format
//		msgSend.lpszConversationID;	// LPSTR conversation thread ID
//		msgSend.flFlags;			// FLAGS unread,return receipt
//		msgSend.lpOriginator;		// lpMapiRecipDesc Originator descriptor
//		msgSend.nRecipCount;		// ULONG Number of recipients
//		msgSend.lpRecips;			// lpMapiRecipDesc Recipient descriptors
//		msgSend.nFileCount;			// ULONG # of file attachments
//		msgSend.lpFiles;			// lpMapiFileDesc Attachment descriptors
	
	    MAPISendMail(m_lhSession, (ULONG)m_hParentWnd, &msgSend, MAPI_DIALOG, 0L);
		bRet = TRUE;
	} // PR_RTF_COMPRESSED

	return bRet;
}