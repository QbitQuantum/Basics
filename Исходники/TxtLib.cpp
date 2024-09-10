std::list<std::string*>* CSpeechSynthesizer::GetAvailableVoices()
{
	std::list<std::string*>* namelist = new std::list<std::string*>();
	// if we're not initialized return an empty list
	if (!m_initialized)
		return namelist;

	if (m_tokenMap->size() < 1)
	{
		for (std::map<std::string*, std::string*>::iterator mit = m_registryList->begin(); mit != m_registryList->end(); mit++)
		{
			std::string regToken = (*mit).first->c_str();
			regToken.append("\\");
			regToken.append((*mit).second->c_str());
			// Enumerate voice tokens
			const char* text = regToken.c_str();
			int size_needed = MultiByteToWideChar(CP_UTF8, 0, &text[0], (int)strlen(text), NULL, 0);
			TCHAR tokenId[1024] = { 0 };
			MultiByteToWideChar(CP_UTF8, 0, &text[0], (int)strlen(text), &tokenId[0], size_needed);
			CComPtr<ISpObjectToken> cpTokenObj;
			HRESULT hr = SpGetTokenFromId(tokenId, &cpTokenObj, false);
			if (SUCCEEDED(hr))
			{
				wchar_t* desc = new wchar_t[256];
				SpGetDescription(cpTokenObj, &desc);
				char desctext[256] = { 0 };
				wcstombs(desctext, desc, 256);
				std::string* voiceName = new std::string(desctext);
				namelist->push_back(voiceName);
				m_tokenMap->insert(std::pair<std::string*, std::string*>(voiceName, new std::string(regToken.c_str())));
			}
			if (cpTokenObj != NULL)
				cpTokenObj.Release();
		}
	}
	else
	{
		for (std::map<std::string*, std::string*>::iterator mit = m_tokenMap->begin(); mit != m_tokenMap->end(); mit++)
		{
			namelist->push_back((*mit).first);
		}
	}

	return namelist;
}