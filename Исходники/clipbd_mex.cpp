/* interface between MATLAB and the C function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	/* declare variables */
	int ns, n2, m, n, put = 0;
	char *str;
	char *pchData;
	HGLOBAL hClipboardData;

	if ( !OpenClipboard(NULL) )
		mexErrMsgTxt("CLIPBD ERROR: Error while opening clipboard.\n");

	put = nrhs;

	EmptyClipboard();

	if (put && mxIsChar(prhs[0])) {
		str = (char *)mxArrayToString(prhs[0]);
		ns = strlen(str) + 1;

		hClipboardData = GlobalAlloc(GMEM_DDESHARE, ns);

		pchData = (char*)GlobalLock(hClipboardData);
		  
		strcpy(pchData, str);
		  
		GlobalUnlock(hClipboardData);
		  
		SetClipboardData(CF_TEXT,hClipboardData);
		  
	}
	else if (put && mxIsNumeric(prhs[0])) {
		UINT format = RegisterClipboardFormat("000_FMT");
		int is_single = 0, is_double = 0;
		clip_matFormat data; 

		if (mxIsSingle(prhs[0]))
			is_single = 1;

		else if (mxIsDouble(prhs[0]))
			is_double = 1;

		data.ny = mxGetM(prhs[0]);	data.nx = mxGetN(prhs[0]);
		if (nrhs == 2) {
			if ( mxGetM(prhs[1]) == 9 || mxGetN(prhs[1]) == 9 )
				data.head = mxGetPr(prhs[1]);
		}

		if (is_single)
			data.z_s = (float *)mxGetData(prhs[0]);
		else
			data.z_d = mxGetPr(prhs[0]);

		hClipboardData = GlobalAlloc(GMEM_DDESHARE, sizeof(clip_matFormat));
		clip_matFormat *buffer = (clip_matFormat *)GlobalLock(hClipboardData);

		/* put the data into that memory */
		*buffer = data;

		/* Put it on the clipboard */
		GlobalUnlock(hClipboardData);
		SetClipboardData(format,hClipboardData);
		mexPrintf("FFSSS %d\n;", format);
		mexPrintf("FDS %d\n", IsClipboardFormatAvailable(format));
	}
	else if (!put) {
		UINT format = RegisterClipboardFormat("000_FMT");

		/* No idea why it is not working. The 'format' is no
		   longer recognized as a registered one .*/
		mexPrintf("FDS %d\n", IsClipboardFormatAvailable(format));
		if ( !IsClipboardFormatAvailable(format) )
			mexErrMsgTxt("fd-se.\n");

		clip_matFormat data; 
		HANDLE hData = GetClipboardData(format);
		clip_matFormat *buffer = (clip_matFormat *)GlobalLock(hData);

		/* make a local copy */
		data = *buffer;

		mexPrintf("mmm %d\n", (buffer->ny));

		GlobalUnlock( hData );
	}

	CloseClipboard();
}