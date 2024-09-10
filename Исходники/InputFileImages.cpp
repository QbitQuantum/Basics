void VDInputFileImages::Init(const wchar_t *szFile) {
	// Attempt to discern path format.
	//
	// First, find the start of the filename.  Then skip
	// backwards until the first period is found, then to the
	// beginning of the first number.

	mBaseName = szFile;
	const wchar_t *pszBaseFormat = mBaseName.c_str();

	const wchar_t *pszFileBase = VDFileSplitPath(pszBaseFormat);
	const wchar_t *s = pszFileBase;

	mLastDigitPos = -1;

	while(*s)
		++s;

	while(s > pszFileBase && s[-1] != L'.')
		--s;

	while(s > pszFileBase) {
		--s;

		if (iswdigit(*s)) {
			mLastDigitPos = s - pszBaseFormat;
			break;
		}
	}

	mFrames = 1;

	// Make sure the first file exists.
	vdfastvector<wchar_t> namebuf;
	if (!VDDoesPathExist(ComputeFilename(namebuf, 0)))
		throw MyError("File \"%ls\" does not exist.", namebuf.data());

	// Stat as many files as we can until we get an error.
	if (mLastDigitPos >= 0) {
		vdfastvector<wchar_t> namebuf;

		ProgressDialog pd(g_hWnd, "Image import filter", "Scanning for images", 0x3FFFFFFF, true);

		pd.setValueFormat("Scanning frame %lu");

		while(VDDoesPathExist(ComputeFilename(namebuf, mFrames))) {
			++mFrames;
			pd.advance((long)mFrames);
		}
	}

	// make sure the first frame is valid
	vdrefptr<IVDVideoSource> vs;
	GetVideoSource(0, ~vs);
}