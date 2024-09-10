void CCollectionCreateDialog::OnBnClickedOk()
{
	//Some users have noted that the collection can at times
	//save a collection with a invalid name...
	OnEnKillFocusCollectionName();

	CString sFileName;
	m_CollectionNameEdit.GetWindowText(sFileName);
	if (!sFileName.IsEmpty())
	{
		m_pCollection->m_sCollectionAuthorName.Empty();
		m_pCollection->SetCollectionAuthorKey(NULL, 0);
		m_pCollection->m_sCollectionName = sFileName;
		m_pCollection->m_bTextFormat = (m_CollectionCreateFormatCheck.GetCheck() == BST_CHECKED);

		CString sFilePath;
		sFilePath.Format(_T("%s\\%s.emulecollection"), thePrefs.GetMuleDirectory(EMULE_INCOMINGDIR), m_pCollection->m_sCollectionName);

		using namespace CryptoPP;
		RSASSA_PKCS1v15_SHA_Signer* pSignkey = NULL;
		if (m_CollectionCreateSignNameKeyCheck.GetCheck())
		{
			bool bCreateNewKey = false;
			HANDLE hKeyFile = ::CreateFile(thePrefs.GetMuleDirectory(EMULE_CONFIGDIR) + _T("collectioncryptkey.dat"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hKeyFile != INVALID_HANDLE_VALUE)
			{
				if (::GetFileSize(hKeyFile, NULL) == 0)
					bCreateNewKey = true;
				::CloseHandle(hKeyFile);
			}
			else
				bCreateNewKey = true;

			if (bCreateNewKey)
			{
				try
				{
					AutoSeededRandomPool rng;
					InvertibleRSAFunction privkey;
					privkey.Initialize(rng, 1024);
					Base64Encoder privkeysink(new FileSink(CStringA(thePrefs.GetMuleDirectory(EMULE_CONFIGDIR) + _T("collectioncryptkey.dat"))));
					privkey.DEREncode(privkeysink);
					privkeysink.MessageEnd();
				}
				catch(...)
				{
					ASSERT(0);
				}
			}

			try
			{
				FileSource filesource(CStringA(thePrefs.GetMuleDirectory(EMULE_CONFIGDIR) + _T("collectioncryptkey.dat")), true,new Base64Decoder);
				pSignkey = new RSASSA_PKCS1v15_SHA_Signer(filesource);
				RSASSA_PKCS1v15_SHA_Verifier pubkey(*pSignkey);
				byte abyMyPublicKey[1000];
				ArraySink asink(abyMyPublicKey, 1000);
				pubkey.DEREncode(asink);
				int nLen = asink.TotalPutLength();
				asink.MessageEnd();
				m_pCollection->SetCollectionAuthorKey(abyMyPublicKey, nLen);
			}
			catch(...)
			{
				ASSERT(0);
			}

			m_pCollection->m_sCollectionAuthorName = thePrefs.GetUserNick();
		}

		if (!PathFileExists(sFilePath))
		{
			m_pCollection->WriteToFileAddShared(pSignkey);
		}
		else
		{
			if (AfxMessageBox(GetResString(IDS_COLL_REPLACEEXISTING), MB_ICONWARNING | MB_ICONQUESTION | MB_DEFBUTTON2 | MB_YESNO) == IDNO)
				return;

			bool bDeleteSuccessful = ShellDeleteFile(sFilePath);
			if (bDeleteSuccessful)
			{
				CKnownFile* pKnownFile = theApp.knownfiles->FindKnownFileByPath(sFilePath);
				if (pKnownFile)
				{
					theApp.sharedfiles->RemoveFile(pKnownFile, true);
					if (pKnownFile->IsKindOf(RUNTIME_CLASS(CPartFile)))
						theApp.emuledlg->transferwnd->GetDownloadList()->ClearCompleted(static_cast<CPartFile*>(pKnownFile));
				}
				m_pCollection->WriteToFileAddShared(pSignkey);
			}
			else
			{
				AfxMessageBox(GetResString(IDS_COLL_ERR_DELETING),MB_ICONWARNING | MB_ICONQUESTION | MB_DEFBUTTON2 | MB_YESNO);
			}
		}
		
		delete pSignkey;
		pSignkey = NULL;

		OnOK();
	}
}