void PLWEMFDecoder::Open (PLDataSource * pDataSrc)
{
	PLASSERT_VALID(this);
  PLASSERT(m_bm == 0);
  PLASSERT(m_memdc == 0);
  PLASSERT(m_hemf == 0);

	SAPMFILEHEADER* pplaceablehdr = NULL;
	bool isadobe = false;
      bool isemf;

	// Get the type of the file (WMF or EMF) from the file name
      if (pDataSrc->NameIsWide()){
        wchar_t* strname = _wcsdup(pDataSrc->GetNameW());
        PLASSERT(strname);
        if (strname == NULL) {
                // This should never happen under 32-Bit, but who knows?
                PLASSERT(false);
                raiseError (PL_ERRNO_MEMORY,"Out of memory during strdup.");
        }
        _wcsupr(strname);
        isemf = wcsstr(strname,L".EMF") != NULL;
        free(strname);
      }
      else{
	char* strname = _strdup(pDataSrc->GetName());
	PLASSERT(strname);
	if (strname == NULL) {
		// This should never happen under 32-Bit, but who knows?
		PLASSERT(false);
		raiseError (PL_ERRNO_MEMORY,"Out of memory during strdup.");
	}
	_strupr(strname);
	bool isemf = strstr(strname,".EMF") != NULL;
	free(strname);
      }

	// Get a DC for the display
	m_dc = ::GetDC(NULL);
	PLASSERT(m_dc);
	if (m_dc == NULL) {
		PLASSERT(false);
		raiseError (PL_ERRNO_MEMORY,"Cannot allocate device context.");
	}

	if (isemf) {
		// We have an enhanced meta file which makes it alot easier
		m_hemf = SetEnhMetaFileBits(pDataSrc->GetFileSize(),pDataSrc->ReadEverything());
	}
	else {
		// Buh, old 16-Bit WMF, Convert it to an enhanced metafile before proceeding.
		// Also, check if this is a placeable metafile with an Adobe Placeable header
		pplaceablehdr = (SAPMFILEHEADER*)pDataSrc->ReadEverything();
		PLBYTE* p = NULL;
		UINT size;
		// If we have an adobe header, skip it to use only the real windows-conform data
		if (pplaceablehdr->key == ALDUSKEY) {
			isadobe = true;
			p = pDataSrc->ReadEverything()+sizeof(SAPMFILEHEADER);
			size = pDataSrc->GetFileSize() - sizeof(SAPMFILEHEADER);
		}
		else {
			// Else use the whole file contents as the metafile and assume
			// a native 16-Bit Windows-conform WMF
			p = pDataSrc->ReadEverything();
			size = pDataSrc->GetFileSize();
		}
		#ifdef _MFC_VER
		PLASSERT(AfxIsValidAddress(p,size,false));
		#endif
		m_hemf = SetWinMetaFileBits(size,p,m_dc,NULL);
	}

	// If m_hemf is NULL, windows refused to load the metafile. If this is
	// the case, we're done. Notify the caller
	if (m_hemf == NULL) {
		raiseError (PL_ERRFORMAT_NOT_SUPPORTED,"Windows Metafile functions failed to load this image.");
	}

	// Get the header from the enhanced metafile, It contains some
	// useful information which will aid us during constuction of
	// the bitmap.
	// The header is of variable length. First get the amount of
	//  memory required for the header
	UINT sizeneeded = GetEnhMetaFileHeader(m_hemf,0,NULL);
	if (sizeneeded == 0) {
		raiseError (PL_ERRFORMAT_UNKNOWN,"No header information in metafile");
	}

	// Allocate storage for the header and read it in
	m_phdr = (LPENHMETAHEADER) new PLBYTE[sizeneeded];
	if (m_phdr == NULL) {
		PLASSERT(false);
		raiseError (PL_ERRNO_MEMORY,"Out of memory during allocation of header.");
	}
	m_phdr->iType = EMR_HEADER;
	m_phdr->nSize = sizeneeded;
	#ifdef _MFC_VER
	PLASSERT(AfxIsValidAddress(m_phdr,sizeneeded,true));
	#endif
	GetEnhMetaFileHeader(m_hemf,sizeneeded,m_phdr);

	int bpp = GetDeviceCaps(m_dc,BITSPIXEL);

	// Calculate the dimensions of the final bitmap. If we have
	// a placeable header in the WMF, we use the dimensions of
	// that image, else we use the calculated dimensions in the
	// EMF
	int width,height;
	if (isadobe) {
		PLASSERT(pplaceablehdr);
		int lpx = GetDeviceCaps(m_dc,LOGPIXELSX);
		int lpy = GetDeviceCaps(m_dc,LOGPIXELSY);
		// Calculate the absolute with and height and transform from twips to pixel
		width  = (int) (pplaceablehdr->Right-pplaceablehdr->Left) * lpx / pplaceablehdr->inch;
		height = (int) (pplaceablehdr->Bottom-pplaceablehdr->Top) * lpy / pplaceablehdr->inch;
	}
	else {
		// Use the rclFrame of the header because it is the true device independent
		// information and also some applications (e.g. Corel) don't fill the
		// rclBounds correctly
		// Using:
		//     MetaPixelsX = MetaWidthMM * MetaPixels / (MetaMM * 100);
		// where:
		//     MetaWidthMM = metafile width in 0.01mm units
		//     MetaPixels  = width in pixels of the reference device
		//     MetaMM      = width in millimeters of the reference device
		// Same applies to the Y axis
		width  = ((m_phdr->rclFrame.right  - m_phdr->rclFrame.left) * m_phdr->szlDevice.cx) / (m_phdr->szlMillimeters.cx*100);
		height = ((m_phdr->rclFrame.bottom  - m_phdr->rclFrame.top) * m_phdr->szlDevice.cy) / (m_phdr->szlMillimeters.cy*100);
	}

	// If this is a very old WMF without a PLACEABLE info,
	// we use somewhat meaningful defaults. Also, if the header was
	// not written correctly, we use this as a fallback
	if (width <= 0) {
		width = 320;
	}
	if (height <= 0) {
		height = 200;
	}

	// Create a device content for the screen, and a memory device
	// content to play the metafile to

	m_memdc = CreateCompatibleDC(m_dc);
	PLASSERT(m_memdc);
	if (m_memdc == NULL) {
		PLASSERT(false);
		raiseError (PL_ERRNO_MEMORY,"Cannot allocate device context.");
	}

	m_bm = CreateCompatibleBitmap(m_dc,width,height);
	if (m_bm == NULL) {
		PLASSERT(false);
		raiseError (PL_ERRNO_MEMORY,"Cannot allocate memory bitmap.");
	}

	m_holdbm = SelectObject(m_memdc,m_bm);

	// If the metafile has a palette, read it in
	UINT pe = GetEnhMetaFilePaletteEntries(m_hemf, 0, NULL);

	// pe is the real number of palette entries. To make the resulting
	// bitmap more useful, we always setup a 256 color palette if the
	// metafile has a palette
  if (pe>0 && pe<256)
  {
    SetBmpInfo (PLPoint (width, height), PLPoint(0,0), 
             PLPixelFormat::L8);
	}
	else 
  {
    SetBmpInfo (PLPoint (width, height), PLPoint(0,0), 
            PLPixelFormat::B8G8R8A8);
  }
}