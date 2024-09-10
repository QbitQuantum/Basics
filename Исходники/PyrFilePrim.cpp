int prFileOpen(struct VMGlobals *g, int numArgsPushed)
{
	PyrSlot *a, *b, *c;
	char filename[PATH_MAX];
	char mode[12];
	PyrFile *pfile;
	FILE *file;

	a = g->sp - 2;
	b = g->sp - 1;
	c = g->sp;
	if (NotObj(c) || !isKindOf(slotRawObject(c), class_string)
		|| NotObj(b) || !isKindOf(slotRawObject(b), class_string))
		return errWrongType;
	if (slotRawObject(b)->size > PATH_MAX - 1) return errFailed;
	if (slotRawObject(c)->size > 11) return errFailed;
	pfile = (PyrFile*)slotRawObject(a);

	memcpy(filename, slotRawString(b)->s, slotRawObject(b)->size);
	filename[slotRawString(b)->size] = 0;

	memcpy(mode, slotRawString(c)->s, slotRawObject(c)->size);
	mode[slotRawString(c)->size] = 0;

#ifdef SC_WIN32
	win32_ReplaceCharInString(filename,PATH_MAX,'/','\\');
	if(strcmp(mode,"w") == 0)
	strcpy(mode,"wb");
	if(strcmp(mode,"r") == 0)
	strcpy(mode,"rb");
#endif
	//SC_WIN32
	file = fopen(filename, mode);
	if (file) {
		SetPtr(&pfile->fileptr, file);
		SetTrue(a);
	} else {
#ifdef SC_WIN32
		// check if directory exisits
		// create a temporary file (somewhere) for a handle
		// the file is deleted automatically when closed
		if (sc_DirectoryExists(filename)) {
			int err;
#ifdef _MSC_VER
			err = tmpfile_s(&file);
			if (!err) {
				SetPtr(&pfile->fileptr, file);
				SetTrue(a);
				return errNone;
			}
#elif defined(__MINGW32__)
			file = tmpfile();
			if (file) {
				SetPtr(&pfile->fileptr, file);
				SetTrue(a);
				return errNone;
			}
#else
#error compiler unsupported
#endif
		}
#endif
		SetNil(a);
		SetFalse(a);
	}
	return errNone;
}