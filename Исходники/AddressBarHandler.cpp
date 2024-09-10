void Explorerplusplus::CreateAddressBar(void)
{
	m_hAddressBar = CreateComboBox(m_hMainRebar,WS_CHILD|WS_VISIBLE|WS_TABSTOP|
		CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);

	HIMAGELIST SmallIcons;
	Shell_GetImageLists(NULL,&SmallIcons);
	SendMessage(m_hAddressBar,CBEM_SETIMAGELIST,0,reinterpret_cast<LPARAM>(SmallIcons));

	HWND hEdit = reinterpret_cast<HWND>(SendMessage(m_hAddressBar,CBEM_GETEDITCONTROL,0,0));
	SetWindowSubclass(hEdit,EditSubclassStub,0,reinterpret_cast<DWORD_PTR>(this));

	/* Turn on auto complete for the edit control within the combobox.
	This will let the os complete paths as they are typed. */
	SHAutoComplete(hEdit,SHACF_FILESYSTEM|SHACF_AUTOSUGGEST_FORCE_ON);
}