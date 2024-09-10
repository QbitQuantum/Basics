	CScene* CText2Scene::CreateScene(const char* heading)
	{
		CScene *pScene = new CScene();
		string title(heading);
		pScene->m_Location = m_pParser->GetLocation(title.c_str(), title);
		pScene->m_Time = m_pParser->GetTime(title.c_str(), title);
		Trim(title);
		ToUpper(title);
		pScene->m_Title = title;
		return pScene;
	}