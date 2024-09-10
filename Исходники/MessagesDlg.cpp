void MessagesDlg::UpdateHoldButton(pjsua_call_info *call_info)
{
#ifndef _GLOBAL_NO_HOLD
	MessagesContact* messagesContact = GetMessageContact();
	if (messagesContact) {
		CButton* button = (CButton*)GetDlgItem(IDC_HOLD);
		CButton* buttonTransfer = (CButton*)GetDlgItem(IDC_TRANSFER);
		CButton* buttonDialer = (CButton*)microsipDlg->pageDialer->GetDlgItem(IDC_HOLD);
		CButton* buttonTransferDialer = (CButton*)microsipDlg->pageDialer->GetDlgItem(IDC_TRANSFER);
		if (messagesContact->callId != -1) {
			if (call_info && messagesContact->callId == call_info->id && call_info->media_cnt>0) {
				buttonTransfer->ShowWindow(SW_SHOW);
				buttonTransferDialer->EnableWindow(TRUE);
				if (call_info->media_status == PJSUA_CALL_MEDIA_ACTIVE
					|| call_info->media_status == PJSUA_CALL_MEDIA_REMOTE_HOLD
					) {
						button->ShowWindow(SW_SHOW);
						button->SetCheck(BST_UNCHECKED);
						buttonDialer->EnableWindow(TRUE);
						buttonDialer->SetCheck(BST_UNCHECKED);
						return;
				} else if (call_info->media_status == PJSUA_CALL_MEDIA_LOCAL_HOLD
					|| call_info->media_status == PJSUA_CALL_MEDIA_NONE) {
						button->ShowWindow(SW_SHOW);
						button->SetCheck(BST_CHECKED);
						buttonDialer->EnableWindow(TRUE);
						buttonDialer->SetCheck(BST_CHECKED);
						return;
				}
			}
		} else {
			button->ShowWindow(SW_HIDE);
			button->SetCheck(BST_UNCHECKED);
			buttonDialer->EnableWindow(FALSE);
			buttonDialer->SetCheck(BST_UNCHECKED);
			buttonTransfer->ShowWindow(SW_HIDE);
			buttonTransferDialer->EnableWindow(FALSE);
		}
	}
#endif
}