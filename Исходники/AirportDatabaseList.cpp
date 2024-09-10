bool CAirportDatabaseList::updateShareTemplateDatabase()
{
	for (int i = 0; i < (int)m_vAirportDB.size(); i++)
	{
		CShareTemplateDatabase* pShareTemplateDatabase = m_vAirportDB.at(i);
		CString strSharePath(_T(""));
		strSharePath.Format(_T("%s\\ImportDb\\%s.mdb"),PROJMANAGER->GetAppPath(),pShareTemplateDatabase->getName());
		if (PathFileExists(strSharePath))
		{
			/*CString strPartsSourceFile(_T(""));

			strPartsSourceFile.Format(_T("%s\\ArctermDB\\temp\\project.mdb"),PROJMANAGER->GetAppPath());
			CopyFile(strPartsSourceFile,strSharePath,FALSE);*/
			AirportDatabaseConnection pConnectionPtr(strSharePath);
			CPartsAndShareTemplateUpdate shareTemplateDataBaseUpdater;
			if(!shareTemplateDataBaseUpdater.Update(&pConnectionPtr)) 
			{
				CString strError(_T(""));
				strError.Format(_T("Update the Share Template DataBase error."));
				MessageBox(NULL,strError,"Warning",MB_OK);
				return false;
			}
		}
	}
	return true;
}