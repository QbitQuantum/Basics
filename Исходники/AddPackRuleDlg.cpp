void CAddPackRuleDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strItem;
	GetDlgItem(IDC_EDIT_PACK_ITEMNAME)->GetWindowText(strItem);
	if(strItem.IsEmpty())
	{
		MessageBox(_T("没有选择删除项!"));
		return;
	}
	if( IDOK == MessageBox(_T("是否确认删除!")))
	{	
		char strDeleteItemName[20] = {0};
		//Xt: 删除列表中的要删除的值
		CChangeCode::UnicodeToGB2312Code(strDeleteItemName,strItem.GetBuffer());
		if(1 == CGlobalData::m_mapPackRuleFileInfo.erase(strDeleteItemName))
		{	
			//Xt: 创建文件副本以防丢失
			char strDuplicateFile[MAX_PATH] = {0};
			memcpy(strDuplicateFile,CGlobalData::m_strPackRulePath,strlen(CGlobalData::m_strPackRulePath)-4);
			strcat(strDuplicateFile,"Dup.txt");
			MoveFileA(CGlobalData::m_strPackRulePath,strDuplicateFile);

			//Xt: 清空输入列表和控件内容
			ClearControlInfo();
			m_ListCtrl.DeleteAllItems();

			//Xt: 从新创建包规则文件并存入信息
			FILE *file = fopen(CGlobalData::m_strPackRulePath,"a");
			int nRow = 0;
			map<string,PACKRULEFILE>::iterator pPackInfo = CGlobalData::m_mapPackRuleFileInfo.begin();
			for(;pPackInfo != CGlobalData::m_mapPackRuleFileInfo.end(); ++pPackInfo)
			{
				CGlobalData::WritePackRuleFile(&(pPackInfo->second),file);
				AddListInfo(&(pPackInfo->second),nRow);
				nRow++;
			}

			//Xt: 移除副本文件，更新列表控件
			remove(strDuplicateFile);
			fclose(file);
			m_ListCtrl.Update(false);
		}
	}
}