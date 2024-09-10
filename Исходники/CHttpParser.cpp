bool CHttpParser::setData(const char *pszData, const int iDataLen)
{
	bool bOk = true;
	m_sHttpContent.assign(pszData, iDataLen);
	this->reset();

	string sValue;
	string sName;
	string::size_type pos1 = 0;
	string::size_type pos2 = 0;

	string::size_type headEndPos = m_sHttpContent.find("\r\n\r\n");

	//http command
	pos2 = m_sHttpContent.find(' ', pos1);
	if (pos2 != string::npos)
	{
		sValue = m_sHttpContent.substr(0,pos2);
		if (sValue == "GET")
		{
			m_nCommand = GET;
		}
		else if (sValue == "POST")
		{
			m_nCommand = POST;
		}
		else if (sValue == "HEAD")
		{
			m_nCommand = HEAD;
		}
		else
		{
			snprintf(m_szErrMsg, sizeof(m_szErrMsg), "http command error: %s.", sValue.c_str());
			return false;
		}
	}
	else
	{
		snprintf(m_szErrMsg, sizeof(m_szErrMsg), "parse http command error: can't find space.");
		return false;
	}

	//uri
	pos1 = pos2 + 1;
	pos2 = m_sHttpContent.find(' ', pos1);
	if (string::npos != pos2)
	{
		m_sURI = m_sHttpContent.substr(pos1, pos2-pos1);
		if ( m_sURI.empty() )
		{
			snprintf(m_szErrMsg, sizeof(m_szErrMsg), "URI error: uri is empty.");
			return false;
		}


		if (m_nCommand == GET)
		{
			string::size_type tmpPos = m_sURI.find('?');
			if (tmpPos != string::npos)
			{
				m_sValues = m_sURI.substr(tmpPos+1);
				m_sURI.erase(tmpPos);
			}
		}
		else if ( m_nCommand == POST )
		{
			m_sValues = m_sHttpContent.substr(headEndPos+4);
		}
	}
	else
	{
		snprintf(m_szErrMsg, sizeof(m_szErrMsg), "parse http URI error: can't find space.");
		return false;
	}

	//version
	pos1 = pos2 + 1;
	pos2 = m_sHttpContent.find("\r\n", pos1);
	if (pos2 != string::npos)
	{
		m_sVersion = m_sHttpContent.substr( pos1, pos2 - pos1 );
		if ( m_sVersion.empty() )
		{
			snprintf(m_szErrMsg, sizeof(m_szErrMsg), "version error: version is empty.");
			return false;
		}
	}
	else
	{
		snprintf(m_szErrMsg, sizeof(m_szErrMsg), "parse http version error: can't find <\\r\\n>.");
		return false;
	}

	pos1 = pos2 + 2;
	string sLine;
	string::size_type colonPos = 0;

	string sBoundary;//2010-02-26 解析post 的formdata等
	while ( string::npos != pos1 && pos1 < headEndPos )
	{
		pos2 = m_sHttpContent.find("\r\n", pos1);
		if ( pos2 == string::npos || headEndPos < pos2 )
			break;

		sLine = m_sHttpContent.substr(pos1, pos2-pos1);
		pos1 = pos2 + 2;

		colonPos = sLine.find(": ");
		sName = sLine.substr( 0, colonPos );
		if (sName.empty())
		{
			snprintf(m_szErrMsg, sizeof(m_szErrMsg), "name error: name is empty<pos1=%d, pos2=%d>.", (uint32_t)pos1, (uint32_t)pos2);
			return false;
		}

		sValue = sLine.substr( colonPos+2 );

		static const string BOUNDARY_STR("multipart/form-data; boundary=");
		if(sBoundary.empty() && sName == "Content-Type" && sValue.substr(0, BOUNDARY_STR.length()) == BOUNDARY_STR)
		{
			sBoundary = sValue.substr(BOUNDARY_STR.length());
		}
		else
		{
			m_mapHeadInfo[toLower(sName.c_str())] = sValue;
		}
	}

	this->parseCookies();
	this->parseValues();

	//2010-02-26 解析post 的formdata等
	if(m_nCommand == POST && !sBoundary.empty())
	{
		sBoundary.insert(0, "--");
		this->parsePostFormData(sBoundary, headEndPos);
	}

	return bOk;
}