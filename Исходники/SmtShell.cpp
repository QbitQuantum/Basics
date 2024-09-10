HRESULT STDMETHODCALLTYPE CSmtShell::QueryContextMenu(THIS_ HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{ 
	HMENU SubMenu = CreatePopupMenu();
	memset(m_EnvPath, 0, sizeof(m_EnvPath));

	if(!IsWorkEvn(m_szFile[0], m_EnvPath)){
		if(FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(m_szFile[0])){
			if(m_NumFiles <= 1){
				InsertMenu(SubMenu, 0, MF_STRING | MF_BYPOSITION, idCmdFirst +101, _T("Set Environment"));
				
				InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
				InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
				InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
			}
		}
	}
	else{
		if(IsProductEnv()){
			int i = 0;
			InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +103, _T("Update"));
			
			InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
			InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
			InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
		}
		else{
			if(!IsInCtr()){
				int i = 0;
				if(!IsHaveEnvPath()){
					if(m_FathAddFlag){
						if(m_CouldAdd){
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +107, _T("Add"));
						}
						else{
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +108, _T("Revert"));
						}
					}
					else{
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +102, _T("Check out"));
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +103, _T("Update"));
						if(IsFatherInCtr()){
							InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +107, _T("Add"));
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +108, _T("Revert"));
						}
					}

					//InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +110, _T("Import"));
					
					InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
					InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
					InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
				}
			}
			else{
				int i = 0;
				if(!IsHaveEnvPath()){
					InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +104, _T("Commit"));
					InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +105, _T("Check in"));
					InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
					if(!m_AddFlag){
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +103, _T("Update"));
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +106, _T("Cancel"));
						InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +109, _T("Merge"));
					}
					InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +108, _T("Revert"));
					
					InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
					InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
					InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
				}
			}
		}
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(109 + 1));
}