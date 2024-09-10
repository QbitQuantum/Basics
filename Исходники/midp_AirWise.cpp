void com_wise_sys_Win32Peer::showContextMenu(
	javax_microedition_lcdui_Command_ap  aCommand1,
	jint  x,
	jint  y
) {
	if (aCommand1 == FASTIVA_NULL) {
		return;
	}

	MainFrame* pFrame = (MainFrame*)this->m_handle;
	HMENU hMenu = ::CreatePopupMenu();//
	pFrame->m_hPopupMenu = hMenu;
	for (int i = 0; i < aCommand1->length(); i ++) {
		Byte_A::Buffer cmd(aCommand1->get$(i)->getLabel()->getBytes());
		AppendMenuA(hMenu, MF_STRING, i, (char*)(jbyte*)cmd);
	}
	TrackPopupMenu(
		hMenu,
		TPM_LEFTALIGN,
		x,
		y,
		0,
		*pFrame,
		NULL
	);
}