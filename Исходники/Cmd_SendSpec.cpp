void CCmd_SendSpec::OnOutputInfo(char level, LPCTSTR data, LPCTSTR msg)
{
    //i18n: completion message in data
	BOOL processedMessage=FALSE;

	switch(m_SpecType)
	{
	case P4BRANCH_SPEC:
		if(StrNCmp(data, _T("Branch "), 7) == 0)
		{
			TheApp()->StatusAdd(msg, SV_COMPLETION);
			processedMessage=TRUE;
		}
		break;

	case P4CLIENT_SPEC:
		if(StrNCmp(data, _T("Client "), 7) == 0)
		{
			TheApp()->StatusAdd(msg, SV_COMPLETION);
			processedMessage=TRUE;
		}
		break;

	case P4JOB_SPEC:
		if(StrNCmp(data, _T("Job "), 4) == 0)
		{
			// Extract the new job name
            LPCTSTR pRest = StrChr(data+4, _T(' '));
            if(pRest && (!StrCmp(pRest+1, _T("saved.")) || 
                         !StrCmp(pRest+1, _T("not changed."))))
			{
                CString temp(data + 4);
				temp=temp.Left(temp.Find(_T(' ')));
				m_NewJobName= temp;
			}

			TheApp()->StatusAdd(msg, SV_COMPLETION);
			processedMessage=TRUE;
		}
		break;

	case P4LABEL_SPEC:
		if(StrNCmp(data, _T("Label "), 6) == 0)
		{
			TheApp()->StatusAdd(msg, SV_COMPLETION);
			processedMessage=TRUE;
		}
		break;

	case P4USER_SPEC:
		if(StrNCmp(data, _T("User "), 5) == 0)
		{
			TheApp()->StatusAdd(msg, SV_COMPLETION);
			processedMessage=TRUE;
		}
		break;
	
	case P4CHANGE_SPEC:
		if(!m_Submit)
		{
			if(StrNCmp(data, _T("Change"), 6) ==0 )
			{
				m_NewChangeNum= _ttol(data+7);
				ASSERT(m_NewChangeNum);
				processedMessage=TRUE;
			}
			break;
		}
		else
		{
			// Typically many lines are returned - The only thing we need is the new
			// change number
            
            static TCHAR rc[] = _T("renamed change ");
            static TCHAR sc[] = _T("Submitting change ");

            if(!StrNCmp(data, _T("Change"), 6) && !StrStr(data, _T("updated")))
			{
				// Its either 'Change n1 renamed change n2 and submitted'
				//         or 'Change n1 submitted'
				m_NewChangeNum = _ttol(data+7);
                LPCTSTR pRenamed = StrStr(data+7, rc);
				if(pRenamed)
					m_NewChangeNum = _ttol(pRenamed + StrLen(rc));
				ASSERT(m_NewChangeNum);
			}
			else if(!StrNCmp(data, sc, StrLen(sc)))
            {
                // It's 'Submitting change n1'
    			m_NewChangeNum = _ttol(data+StrLen(sc));
				ASSERT(m_NewChangeNum);
            }
			else if(StrStr(data, _T(" - must get")) || StrStr(data, _T(" - must resolve")))
				TheApp()->StatusAdd(msg, SV_WARNING);
			else if(StrCmp(data, _T("Specification not corrected -- giving up.")) == 0)
				TheApp()->StatusAdd(msg, SV_WARNING);
			else
				TheApp()->StatusAdd(msg);

			processedMessage=TRUE;
			break;
		}

	default:
			ASSERT(0);
	}

	if(!processedMessage)
		CP4Command::OnOutputInfo( level, data, msg);
}