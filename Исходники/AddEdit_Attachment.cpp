void CAddEdit_Attachment::ShowPreview()
{
  CItemAtt &att = M_attachment();
  HRESULT hr(S_OK);

  int rc(0);

  // Assume not an image
  m_attType = ATTACHMENT_NOT_IMAGE;

  if (!att.HasContent()) {
    // No content so filename must not be empty
    if (m_AttFileName.IsEmpty())
      return;

    int status = att.Import(LPCWSTR(m_AttFileName));
    if (status != PWScore::SUCCESS) {
      // most likely file error - TBD better error reporting
      rc = 1;
      goto load_error;
    }

    // Get media type before we find we can't load it
    m_csMediaType = att.GetMediaType().c_str();

    // Get other properties
    wchar_t szFileSize[256];
    StrFormatByteSize(att.GetContentSize(), szFileSize, 256);
    m_csSize = szFileSize;
    m_csFileCTime = att.GetFileCTime().c_str();
    if (m_csFileCTime.IsEmpty())
      m_csFileCTime.LoadString(IDS_NA);
    m_csFileMTime = att.GetFileMTime().c_str();
    if (m_csFileMTime.IsEmpty())
      m_csFileMTime.LoadString(IDS_NA);

    if (m_csMediaType.Left(5) == L"image") {
      // Should be an image file - but may not be supported by CImage - try..
      hr = m_AttImage.Load(m_AttFileName);
      if (SUCCEEDED(hr)) {
        hr = m_stImgAttachment.Load(m_AttFileName);
      } 

      if (SUCCEEDED(hr)) {
        // Success - was an image
        m_attType = ATTACHMENT_IS_IMAGE;
      }
    }

    // Create UUID if not already present
    if (!att.HasUUID())
      att.CreateUUID();
  } else {// att.HasContent()
    // This should only be the case during the InitDialog - maybe m_bInitDone
    // in the logic for this processing rather than att.HasContent
    ASSERT(!m_bInitdone);

    if (m_csMediaType.Left(5) == L"image") {
      // Should be an image file - but may not be supported by CImage - try..
      // Allocate attachment buffer
      UINT imagesize = (UINT)att.GetContentSize();
      HGLOBAL gMemory = GlobalAlloc(GMEM_MOVEABLE, imagesize);
      ASSERT(gMemory);

      if (gMemory == NULL) {
        rc = 2;
        goto load_error;
      }

      BYTE *pBuffer = (BYTE *)GlobalLock(gMemory);
      ASSERT(pBuffer);

      if (pBuffer == NULL) {
        rc = 3;
        GlobalFree(gMemory);
        goto load_error;
      }

      // Load image into buffer
      att.GetContent(pBuffer, imagesize);

      // Put it into a IStream
      IStream *pStream = NULL;
      hr = CreateStreamOnHGlobal(gMemory, FALSE, &pStream);
      if (SUCCEEDED(hr)) {
        // Load it
        hr = m_AttImage.Load(pStream);
        if (SUCCEEDED(hr)) {
          hr = m_stImgAttachment.Load(pStream);
        }
      }

      // Clean up - no real need to trash the buffer
      if (pStream != NULL)
        pStream->Release();

      GlobalUnlock(gMemory);
      GlobalFree(gMemory);

      // Check image load (or previous error of putting content into an IStream)
      if (FAILED(hr)) {
        goto load_error;
      }

      // Success - was an image
      m_attType = ATTACHMENT_IS_IMAGE;
    }
  }

  return;

load_error:
  // Ooops???
  m_stImgAttachment.IssueError(rc, hr);
}