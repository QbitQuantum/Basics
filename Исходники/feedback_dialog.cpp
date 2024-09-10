BOOL CFeedbackDialog::OnFeedbackClick()
{



 

  wstring wstrOtherReason;
  wstrOtherReason.resize(1024);
  int char_count = GetDlgItemTextW(IDC_REASON_EDIT, &wstrOtherReason[0], wstrOtherReason.length());

  if (char_count <= 0){
	  //进行响应提示
	  drawRectBorder(m_otherReasonEditCtrl.m_hWnd, RGB(255, 0, 0));
	  //
	  m_feedBackBtnCtrl.SetFocus();
	  m_otherReasonStaticCtrl.ShowWindow(SW_HIDE);
	  SetDlgItemText(IDC_OTHER_REASON_STATIC, L"你还没有输入反馈意见哦...");
	  have_feedback_num_ = false;
	  m_otherReasonStaticCtrl.ShowWindow(SW_SHOWNORMAL);
	  return TRUE;
  }

  have_feedback_num_ = true;
 std::string eid = YE_UNINSTALL_PREFIX "OtherReasonContent";
 std::string content;
 if (!YGW2A(wstrOtherReason, content, CP_UTF8))
		 content.clear();
 ygdata_report::SendCustomEvent(eid, GetEidDesc(eid), content);
  EndDialog(IDCLOSE);
  return TRUE;
}