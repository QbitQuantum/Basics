int CTriangleObj::LoadFile(const char *fname)
{
	FILE *fp;
	char filename[512];
	char * strExtensions[] = {".PLT", ".PLY", ".TXT", ".STL", ".OFF", ""};
	char * ftype = NULL;
	int i, flag;

	fp = fopen(fname, _RA_);
	if (fp==NULL) return 0;

	int len = strlen(fname);
	assert(len<512);
	filename[0]= fname[len-4];
	for (i=1; i<4; i++){
		int j = len-4+i;
#ifdef WIN32
		filename[i] = _toupper(fname[j]);
#else
		filename[i] = toupper(fname[j]);
#endif

	}
	filename[4]=0;

	for (i=0; strExtensions[i][0]!=0; i++){
		if (strcmp(filename, strExtensions[i])==0){
			ftype = strExtensions[i];
			break;
		}
	}

	flag = 0;	
	if (ftype)
		flag = LoadFile(fp, ftype);

	fclose(fp);
	return flag;
}