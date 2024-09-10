void ChatDialog::OnExit(TNotifyUI& msg)
{
	thelockChatDlgList.Lock();
	POSITION pos,temp;
	for (pos=theChatDialogList.GetHeadPosition();pos!=NULL;)
	{
		temp = pos;
		ChatDialog* pDlg = (ChatDialog*)theChatDialogList.GetNext(pos);
		if (pDlg&&pDlg==this)
		{
			theChatDialogList.RemoveAt(temp);
		}
	}
	thelockChatDlgList.UnLock();
	Close();
}