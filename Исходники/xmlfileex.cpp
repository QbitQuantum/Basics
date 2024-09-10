BOOL CXmlFileEx::Decrypt(LPCTSTR szPassword)
{
	if (!IsEncrypted())
		return TRUE; // nothing to do
    
	// we don't try to decrypt if no encryption capabilities
	if (!CanEncrypt())
	{
		m_nFileError = XFL_NOENCRYPTIONDLL;
		return FALSE;
	}
	
	// use existing password if required
	if (!szPassword)
		szPassword = m_sPassword;

	CXmlItem* pXI = GetEncryptedBlock();
    
	if (pXI && !pXI->GetSibling())
	{
		// else keep getting password till success or user cancels
		while (TRUE)
		{
			CString sPassword(szPassword);
			
			if (sPassword.IsEmpty())
			{
				CString sExplanation(s_sPasswordExplanation);

				if (sExplanation.Find(_T("%s")) != -1)
					sExplanation.Format(s_sPasswordExplanation, GetFileName());
				
				if (!CPasswordDialog::RetrievePassword(FALSE, sPassword, sExplanation))
				{
					// RB - Set m_nFileError to avoid "The selected task list could not be opened..." message when cancelling
					m_nFileError = XFL_CANCELLED;
					return FALSE;
				}
			}
			
			CString sFile;
			
			if (Decrypt(pXI->GetValue(), sFile, sPassword))
			{
				m_sPassword = sPassword;
				
				sFile.TrimLeft();
				sFile.TrimRight();
				sFile = _T("<ROOT>") + sFile + _T("</ROOT>");
				
				// delete the cdata item
				m_xiRoot.DeleteItem(pXI);
				
				try
				{
					CXmlDocumentWrapper doc;
					
					// reparse decrypted xml
					if (doc.LoadXML(sFile))
					{
						CXmlNodeWrapper node(doc.AsNode());
						
						return ParseItem(m_xiRoot, &node);
					}
				}
				catch (...)
				{
					m_nFileError = XFL_BADMSXML;
				}
				
				return FALSE;
			}
			// RB - Added code to format the error message before calling AfxMessage
			else
			{
				CEnString sMessage(s_sDecryptFailed, GetFileName());

				if (IDNO == AfxMessageBox(sMessage, MB_YESNO))
				{
					m_nFileError = XFL_CANCELLED;
					return FALSE;
				}
				// else user will try again
			}
		}
	}
    
	// else
	m_nFileError = XFL_UNKNOWNENCRYPTION;
	return FALSE;
}