void COpenCVInterfaceDlg::OnToolsGraylevelcolumn()
{
	if(mainImage.empty())
		MessageBox("No image loaded");
	else
	{
		CMenu* menu = GetMenu();
		CMenu* submenu = menu->GetSubMenu(1);
		UINT state = submenu->GetMenuState(ID_TOOLS_GRAYLEVELCOLUMN,MF_BYCOMMAND);
		ASSERT(state != 0xFFFFFFFF);
		if(state & MF_CHECKED)
			submenu->CheckMenuItem(ID_TOOLS_GRAYLEVELCOLUMN,MF_UNCHECKED | MF_BYCOMMAND);
		else
		{
			submenu->CheckMenuItem(ID_TOOLS_GRAYLEVELCOLUMN,MF_CHECKED | MF_BYCOMMAND);
			//creez pointer-ul
			Invalidate();
			gr= GrayRowPtr(new GrayRow(mainImage,this));
			//creez caseta
			gr->Create(GrayRow::IDD,0);
			//afisez caseta
			gr->ShowWindow(SW_SHOW);
		}
	}
}