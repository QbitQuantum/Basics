void ShowGridArea::showGridArea(CString title,CString name) {
	// TODO: 在此添加命令处理程序代码
	CString OpenFilter = title+_T(+"(*.tab)|*.tab;*.TAB|所有文件(*.*)|*.*||");
	CFileDialog FileDlgOpen(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter);
	FileDlgOpen.m_ofn.lpstrTitle=name.GetBuffer(0);
	if(IDOK == FileDlgOpen.DoModal())
	{
		CString FileName = FileDlgOpen.GetPathName();
		string fileNameString = FileName.GetBuffer(0);
		fileNameString.append(".mif"); 
		//将场强值和颜色进行对应的改变
		//create process
		openProcess();

		//中期数据展示，注释了下面一行
		SetGridColorTool::SetColor(TRUE,title.GetBuffer());
		//MessageBox(_T("，颜色信息已经转换成功!"),_T("通知"),MB_OK);
		//从数据库中取出网格的颜色信息进行展示
		MakeGridFileTool::makeGridFile(fileNameString);

		//在后面加上mif2tab
		Mif2Tab mif2Tab;
		CString path = FileDlgOpen.GetFolderPath();
		mif2Tab.Convert0(path,path);
		//close process
		closeProcess();

		//删除目录中的.mif .mid
		//string cmdLine = "cd " + path;
		//system(cmdLine.c_str());
		//cmdLine = "del *.mif *.mid";
		//system(cmdLine.c_str());
	//	MessageBox(NULL,_T("，已经完成导频污染的判断!"),_T("通知"),MB_OK);
	}
}