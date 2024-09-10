bool CMapiMessage::CopyBinAttachToFile(LPATTACH lpAttach,
                                       nsIFile **tmp_file)
{
  nsCOMPtr<nsIFile> _tmp_file;
  nsresult rv = GetSpecialDirectoryWithFileName(NS_OS_TEMP_DIR,
    "mapiattach.tmp",
    getter_AddRefs(_tmp_file));
  NS_ENSURE_SUCCESS(rv, false);

  rv = _tmp_file->CreateUnique(nsIFile::NORMAL_FILE_TYPE, 00600);
  NS_ENSURE_SUCCESS(rv, false);

  nsCString tmpPath;
  _tmp_file->GetNativePath(tmpPath);
  LPSTREAM lpStreamFile;
  HRESULT hr = CMapiApi::OpenStreamOnFile(gpMapiAllocateBuffer, gpMapiFreeBuffer, STGM_READWRITE | STGM_CREATE,
    const_cast<char*>(tmpPath.get()), NULL, &lpStreamFile);
  if (HR_FAILED(hr)) {
    MAPI_TRACE1("~~ERROR~~ OpenStreamOnFile failed - temp path: %s\r\n",
                tmpPath.get());
    return false;
  }

  bool bResult = true;
  LPSTREAM lpAttachStream;
  hr = lpAttach->OpenProperty(PR_ATTACH_DATA_BIN, &IID_IStream, 0, 0, (LPUNKNOWN *)&lpAttachStream);

  if (HR_FAILED(hr)) {
    MAPI_TRACE0("~~ERROR~~ OpenProperty failed for PR_ATTACH_DATA_BIN.\r\n");
    lpAttachStream = NULL;
    bResult = false;
  }
  else {
    STATSTG st;
    hr = lpAttachStream->Stat(&st, STATFLAG_NONAME);
    if (HR_FAILED(hr)) {
      MAPI_TRACE0("~~ERROR~~ Stat failed for attachment stream\r\n");
      bResult = false;
    }
    else {
      hr = lpAttachStream->CopyTo(lpStreamFile, st.cbSize, NULL, NULL);
      if (HR_FAILED(hr)) {
        MAPI_TRACE0("~~ERROR~~ Attach Stream CopyTo temp file failed.\r\n");
        bResult = false;
      }
    }
  }

  if (lpAttachStream)
    lpAttachStream->Release();
  lpStreamFile->Release();
  if (!bResult)
    _tmp_file->Remove(false);
  else
    CallQueryInterface(_tmp_file, tmp_file);

  return bResult;
}