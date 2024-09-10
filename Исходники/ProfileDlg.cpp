void ProfileDlg::OnImportProfile() 
{
	CString name;
	CString tmp;
	tmp.LoadString(IDS_PROFILE_FILEDIALOG);
	CFileDialog fd( TRUE, _T("prf"), NULL, OFN_ENABLESIZING|OFN_FILEMUSTEXIST, tmp + _T(" (*.xpas)|*.xpas||"), this);
	tmp.LoadString(IDS_PROFILE_LOAD);
	fd.m_ofn.lpstrTitle = tmp;
	if(fd.DoModal() == IDOK)
	{
		StringVec profiles = GetExistingProfiles();
		for(int i = 0; i < profiles.size(); ++i)
		{
			profiles[i].MakeLower();
			fd.GetFileName().MakeLower();
			if(profiles[i] == fd.GetFileTitle())
			{
				CString tmp;
				tmp.LoadString(IDS_PROFILE_EXISTS);
				if(MessageBox(tmp, NULL, MB_YESNO) == IDNO)
				{
					return;
				}
				else
				{
					DeleteProfile(fd.GetFileTitle());
				}
			}
		}

		CFile file(fd.GetPathName(), CFile::modeRead);
		SettingVec vec;
		
		CArchive* ar=new CArchive(&file,CArchive::load);
		try
		{
			while(1)
			{
				SETTING set;
				*ar>>set.settingID;
				*ar>>set.checked;
				if((set.settingID <= ITEMCOUNT && set.settingID >= 0)
					|| (set.checked >= 0 && set.checked <= 1))
				{
					vec.push_back(set);
				}
			}
		}
		catch(CArchiveException* e)
		{
			e->Delete();
			if(vec.size() > 0)
				CreateProfile(fd.GetFileTitle(),vec);
			else
			{
				CString tmp;
				tmp.LoadString(IDS_PROFILE_ERROR);
				AfxMessageBox(tmp);
			}
		}
		ar->Close();
		if(ar) delete ar;
		file.Close();
	}