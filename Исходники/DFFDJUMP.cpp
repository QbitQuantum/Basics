BOOL CDFFDJump::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(AfxGetApp()->LoadIcon(IDI_JUMP), TRUE);

	// If window position specified
	if (pos_.y != -30000)
	{
		CRect rr;               // Rectangle where we will put the dialog
		GetWindowRect(&rr);

		// Move to where it was when it was last closed
		rr.OffsetRect(pos_.x - rr.left, pos_.y - rr.top);
		(void)::NeedsFix(rr);  // Make sure its visible

		MoveWindow(&rr);
	}

	if (!show_prev_next_)
	{
		// Hide << and >> (previous/next) buttons
		ctl_prev_.ShowWindow(SW_HIDE);
		ctl_next_.ShowWindow(SW_HIDE);
	}
	else
	{
		CXmlTree::CElt ee;
		if (parent_type_ == CHexEditDoc::DF_SWITCH)
			ee = pelt_->GetParent();
		else
			ee = *pelt_;
		ee--;
		ctl_prev_.EnableWindow(!ee.IsEmpty());

		if (parent_type_ == CHexEditDoc::DF_SWITCH)
			ee = pelt_->GetParent();
		else
			ee = *pelt_;
		++ee;
		ctl_next_.EnableWindow(!ee.IsEmpty());
	}

	load_data();

	// Setup menu button that allows replace of struct/for/if/data
	VERIFY(button_menu_.LoadMenu(IDR_DFFD));
	CString strTemp;
	ASSERT((button_menu_.GetMenuString(4, strTemp, MF_BYPOSITION), strTemp == "ButtonReplace"));

	// Disable insertion of jump within a jump
	button_menu_.GetSubMenu(4)->EnableMenuItem(ID_DFFD_INSERT_JUMP, MF_BYCOMMAND | MF_GRAYED);

	ctl_replace_.m_hMenu = button_menu_.GetSubMenu(4)->GetSafeHmenu();
//    ctl_replace_.SizeToContent();
	ctl_replace_.m_bOSMenu = TRUE;
	ctl_replace_.m_bStayPressed = TRUE;
	ctl_replace_.m_bRightArrow = TRUE;

	// Set up menu that allows the user to choose any valid variable name
	poffset_menu_ = make_var_menu_tree(*pelt_);
	ctl_offset_var_.m_hMenu = poffset_menu_->GetSafeHmenu();
	ctl_offset_var_.m_bOSMenu = TRUE;
	ctl_offset_var_.m_bStayPressed = TRUE;
	ctl_offset_var_.m_bRightArrow = TRUE;
	ctl_offset_.SetSel(0, -1);           // Select all so a var selection (see OnGetOffsetVar) replaces current contents
	return TRUE;
}