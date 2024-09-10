void CFileDetailDialogInfo::RefreshData()
{
	CString str;

	if (m_paFiles->GetSize() == 1)
	{
		CPartFile* file = STATIC_DOWNCAST(CPartFile, (*m_paFiles)[0]);

		// if file is completed, we output the 'file path' and not the 'part.met file path'
		if (file->GetStatus(true) == PS_COMPLETE)
			GetDlgItem(IDC_FD_X2)->SetWindowText(GetResString(IDS_DL_FILENAME));

		SetDlgItemText(IDC_FNAME, file->GetFileName());
		SetDlgItemText(IDC_METFILE, file->GetFullName());
		SetDlgItemText(IDC_FHASH, md4str(file->GetFileHash()));

		if (file->GetTransferringSrcCount() > 0)
			str.Format(GetResString(IDS_PARTINFOS2), file->GetTransferringSrcCount());
		else
			str = file->getPartfileStatus();
		SetDlgItemText(IDC_PFSTATUS, str);

		str.Format(_T("%u;  %s: %u (%.1f%%)"), file->GetPartCount(), GetResString(IDS_AVAILABLE) , file->GetAvailablePartCount(), (float)((file->GetAvailablePartCount()*100)/file->GetPartCount()));
		SetDlgItemText(IDC_PARTCOUNT, str);

		// date created
		if (file->GetCrFileDate() != 0) {
			str.Format(_T("%s   ") + GetResString(IDS_TIMEBEFORE),
						file->GetCrCFileDate().Format(thePrefs.GetDateTimeFormat()),
						CastSecondsToLngHM(time(NULL) - file->GetCrFileDate()));
		}
		else
			str = GetResString(IDS_UNKNOWN);
		SetDlgItemText(IDC_FILECREATED, str);

		// active download time
		time_t nDlActiveTime = file->GetDlActiveTime(); //vs2005
		if (nDlActiveTime)
			str = CastSecondsToLngHM(nDlActiveTime);
		else
			str = GetResString(IDS_UNKNOWN);
		SetDlgItemText(IDC_DL_ACTIVE_TIME, str);

		// last seen complete
		struct tm tmTemp;
		struct tm* ptimLastSeenComplete = file->lastseencomplete.GetLocalTm(&tmTemp);
		if (file->lastseencomplete == NULL || ptimLastSeenComplete == NULL)
			str.Format(GetResString(IDS_NEVER));
		else {
			str.Format(_T("%s   ") + GetResString(IDS_TIMEBEFORE),
						file->lastseencomplete.Format(thePrefs.GetDateTimeFormat()),
						CastSecondsToLngHM(time(NULL) - safe_mktime(ptimLastSeenComplete)));
		}
		SetDlgItemText(IDC_LASTSEENCOMPL, str);

		// last receive
		if (file->GetFileDate() != 0 && file->GetRealFileSize() > (uint64)0)
		{
			// 'Last Modified' sometimes is up to 2 seconds greater than the current time ???
			// If it's related to the FAT32 seconds time resolution the max. failure should still be only 1 sec.
			// Happens at least on FAT32 with very high download speed.
			uint32 tLastModified = file->GetFileDate();
			time_t tNow = time(NULL); //vs2005
			uint32 tAgo;
			if (tNow >= tLastModified)
				tAgo = tNow - tLastModified;
			else{
				TRACE("tNow = %s\n", CTime(tNow).Format("%X"));
				TRACE("tLMd = %s, +%u\n", CTime(tLastModified).Format("%X"), tLastModified - tNow);
				TRACE("\n");
				tAgo = 0;
			}
			str.Format(_T("%s   ") + GetResString(IDS_TIMEBEFORE),
						file->GetCFileDate().Format(thePrefs.GetDateTimeFormat()),
						CastSecondsToLngHM(tAgo));
		}
		else
			str = GetResString(IDS_NEVER);
		SetDlgItemText(IDC_LASTRECEIVED, str);

		// AICH Hash
		switch (file->GetAICHRecoveryHashSet()->GetStatus()) {
			case AICH_TRUSTED:
			case AICH_VERIFIED:
			case AICH_HASHSETCOMPLETE:
				if (file->GetAICHRecoveryHashSet()->HasValidMasterHash()) {
					SetDlgItemText(IDC_FD_AICHHASH, file->GetAICHRecoveryHashSet()->GetMasterHash().GetString());
					break;
				}
			default:
				SetDlgItemText(IDC_FD_AICHHASH, GetResString(IDS_UNKNOWN));
		}

		// file type
		CString ext;
		bool showwarning = false;
		int pos = file->GetFileName().ReverseFind(_T('.'));
		if (file->GetFileName().ReverseFind(_T('\\')) < pos) {
			ext = file->GetFileName().Mid(pos + 1);
			ext.MakeUpper();
		}
		
		EFileType bycontent = GetFileTypeEx((CKnownFile *)file, false, true);
		if (bycontent != FILETYPE_UNKNOWN) {
			str = GetFileTypeName(bycontent) + _T("  (");
			str.Append(GetResString(IDS_VERIFIED) + _T(')'));

			int extLevel = IsExtensionTypeOf(bycontent, ext);
			if (extLevel == -1) {
				showwarning = true;
				str.Append(_T(" - "));
				str.Append(GetResString(IDS_INVALIDFILEEXT) + _T(": "));
				str.Append(ext);
			}
			else if (extLevel == 0) {
				str.Append(_T(" - "));
				str.Append(GetResString(IDS_UNKNOWNFILEEXT) + _T(": "));
				str.Append(ext);
			}
		}
		else {
			// not verified
			if (pos != -1) {
				str =file->GetFileName().Mid(pos + 1);
				str.MakeUpper();
				str.Append(_T("  (") );
				str.Append( GetResString(IDS_UNVERIFIED) + _T(')'));
			}
			else
				str = GetResString(IDS_UNKNOWN);
		}
		m_bShowFileTypeWarning = showwarning;
		SetDlgItemText(IDC_FD_X11,str);
	}
	else
	{
		SetDlgItemText(IDC_FNAME, sm_pszNotAvail);
		SetDlgItemText(IDC_METFILE, sm_pszNotAvail);
		SetDlgItemText(IDC_FHASH, sm_pszNotAvail);

		SetDlgItemText(IDC_PFSTATUS, sm_pszNotAvail);
		SetDlgItemText(IDC_PARTCOUNT, sm_pszNotAvail);
		SetDlgItemText(IDC_FD_X11, sm_pszNotAvail);

		SetDlgItemText(IDC_FILECREATED, sm_pszNotAvail);
		SetDlgItemText(IDC_DL_ACTIVE_TIME, sm_pszNotAvail);
		SetDlgItemText(IDC_LASTSEENCOMPL, sm_pszNotAvail);
		SetDlgItemText(IDC_LASTRECEIVED, sm_pszNotAvail);
		SetDlgItemText(IDC_FD_AICHHASH, sm_pszNotAvail);
	}

	uint64 uFileSize = 0;
	uint64 uRealFileSize = 0;
	uint64 uTransferred = 0;
	uint64 uCorrupted = 0;
	uint32 uRecoveredParts = 0;
	uint64 uCompression = 0;
	uint64 uCompleted = 0;
	int iMD4HashsetAvailable = 0;
	int iAICHHashsetAvailable = 0;
	uint32 uDataRate = 0;
	UINT uSources = 0;
	UINT uValidSources = 0;
	UINT uNNPSources = 0;
	UINT uA4AFSources = 0;
	for (int i = 0; i < m_paFiles->GetSize(); i++)
	{
		CPartFile* file = STATIC_DOWNCAST(CPartFile, (*m_paFiles)[i]);

		uFileSize += (uint64)file->GetFileSize();
		uRealFileSize += (uint64)file->GetRealFileSize();
		uTransferred += (uint64)file->GetTransferred();
		uCorrupted += file->GetCorruptionLoss();
		uRecoveredParts += file->GetRecoveredPartsByICH();
		uCompression += file->GetCompressionGain();
		uDataRate += file->GetDatarate();
		uCompleted += (uint64)file->GetCompletedSize();
		iMD4HashsetAvailable += (file->GetFileIdentifier().HasExpectedMD4HashCount()) ? 1 : 0;
		iAICHHashsetAvailable += (file->GetFileIdentifier().HasExpectedAICHHashCount()) ? 1 : 0;

		if (file->IsPartFile())
		{
			uSources += file->GetSourceCount();
			uValidSources += file->GetValidSourcesCount();
			uNNPSources += file->GetSrcStatisticsValue(DS_NONEEDEDPARTS);
			uA4AFSources += file->GetSrcA4AFCount();
		}
	}

	str.Format(_T("%s  (%s %s);  %s %s"), CastItoXBytes(uFileSize, false, false), GetFormatedUInt64(uFileSize), GetResString(IDS_BYTES), GetResString(IDS_ONDISK), CastItoXBytes(uRealFileSize, false, false));
	SetDlgItemText(IDC_FSIZE, str);

	if (m_paFiles->GetSize() == 1)
	{
		if (iAICHHashsetAvailable == 0 && iMD4HashsetAvailable == 0)
			SetDlgItemText(IDC_HASHSET, GetResString(IDS_NO));
		else if (iAICHHashsetAvailable == 1 && iMD4HashsetAvailable == 1)
			SetDlgItemText(IDC_HASHSET, GetResString(IDS_YES) + _T(" (eD2K + AICH)"));
		else if (iAICHHashsetAvailable == 1)
			SetDlgItemText(IDC_HASHSET, GetResString(IDS_YES) + _T(" (AICH)"));
		else if (iMD4HashsetAvailable == 1)
			SetDlgItemText(IDC_HASHSET, GetResString(IDS_YES) + _T(" (eD2K)"));
	}
	else
	{
		if (iAICHHashsetAvailable == 0 && iMD4HashsetAvailable == 0)
			SetDlgItemText(IDC_HASHSET, GetResString(IDS_NO));
		else if (iMD4HashsetAvailable == m_paFiles->GetSize() && iAICHHashsetAvailable == m_paFiles->GetSize())
			SetDlgItemText(IDC_HASHSET, GetResString(IDS_YES) +  + _T(" (eD2K + AICH)"));
		else
			SetDlgItemText(IDC_HASHSET, _T(""));
	}

	str.Format(GetResString(IDS_SOURCESINFO), uSources, uValidSources, uNNPSources, uA4AFSources);
	SetDlgItemText(IDC_SOURCECOUNT, str);

	SetDlgItemText(IDC_DATARATE, CastItoXBytes(uDataRate, false, true));

	SetDlgItemText(IDC_TRANSFERRED, CastItoXBytes(uTransferred, false, false));

	str.Format(_T("%s (%.1f%%)"), CastItoXBytes(uCompleted, false, false), uFileSize!=0 ? (uCompleted * 100.0 / uFileSize) : 0.0);
	SetDlgItemText(IDC_COMPLSIZE, str);

	str.Format(_T("%s (%.1f%%)"), CastItoXBytes(uCorrupted, false, false), uTransferred!=0 ? (uCorrupted * 100.0 / uTransferred) : 0.0);
	SetDlgItemText(IDC_CORRUPTED, str);

	str.Format(_T("%s (%.1f%%)"), CastItoXBytes(uFileSize - uCompleted, false, false), uFileSize!=0 ? ((uFileSize - uCompleted) * 100.0 / uFileSize) : 0.0);
	SetDlgItemText(IDC_REMAINING, str);

	str.Format(_T("%u %s"), uRecoveredParts, GetResString(IDS_FD_PARTS));
	SetDlgItemText(IDC_RECOVERED, str);

	str.Format(_T("%s (%.1f%%)"), CastItoXBytes(uCompression, false, false), uTransferred!=0 ? (uCompression * 100.0 / uTransferred) : 0.0);
	SetDlgItemText(IDC_COMPRESSION, str);
}