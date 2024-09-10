LLDir_Solaris::LLDir_Solaris()
{
	mDirDelimiter = "/";
	mCurrentDirIndex = -1;
	mCurrentDirCount = -1;
	mDirp = NULL;

	char tmp_str[LL_MAX_PATH];	/* Flawfinder: ignore */ 
	if (getcwd(tmp_str, LL_MAX_PATH) == NULL)
	{
		strcpy(tmp_str, "/tmp");
		llwarns << "Could not get current directory; changing to "
				<< tmp_str << llendl;
		if (chdir(tmp_str) == -1)
		{
			llerrs << "Could not change directory to " << tmp_str << llendl;
		}
	}

	mExecutableFilename = "";
	mExecutablePathAndName = "";
	mExecutableDir = strdup(tmp_str);
	mWorkingDir = strdup(tmp_str);
	mAppRODataDir = strdup(tmp_str);
	mOSUserDir = getCurrentUserHome(tmp_str);
	mOSUserAppDir = "";
	mLindenUserDir = tmp_str;

	char path [LL_MAX_PATH];	/* Flawfinder: ignore */ 

	sprintf(path, "/proc/%d/psinfo", (int)getpid());
	int proc_fd = -1;
	if((proc_fd = open(path, O_RDONLY)) == -1){
		llwarns << "unable to open " << path << llendl;
		return;
	}
	psinfo_t proc_psinfo;
	if(read(proc_fd, &proc_psinfo, sizeof(psinfo_t)) != sizeof(psinfo_t)){
		llwarns << "Unable to read " << path << llendl;
		close(proc_fd);
		return;
	}

	close(proc_fd);

	mExecutableFilename = strdup(proc_psinfo.pr_fname);
	llinfos << "mExecutableFilename = [" << mExecutableFilename << "]" << llendl;

	sprintf(path, "/proc/%d/path/a.out", (int)getpid());

	char execpath[LL_MAX_PATH];
	if(readlink(path, execpath, LL_MAX_PATH) == -1){
		llwarns << "Unable to read link from " << path << llendl;
		return;
	}

	char *p = execpath;			// nuke trash in link, if any exists
	int i = 0;
	while(*p != NULL && ++i < LL_MAX_PATH && isprint((int)(*p++)));
	*p = NULL;

	mExecutablePathAndName = strdup(execpath);
	llinfos << "mExecutablePathAndName = [" << mExecutablePathAndName << "]" << llendl;

	//NOTE: Why force people to cd into the package directory?
	//      Look for INWORLDZ env variable and use it, if set.

	char *dcf = getenv("INWORLDZ");
	if(dcf != NULL){
		(void)strcpy(path, dcf);
		(void)strcat(path, "/bin");	//NOTE:  make sure we point at the bin
		mExecutableDir = strdup(path);
	}else{
			// plunk a null at last '/' to get exec dir
		char *s = execpath + strlen(execpath) -1;
		while(*s != '/' && s != execpath){
			--s;
		}
	
		if(s != execpath){
			*s = (char)NULL;
	
			mExecutableDir = strdup(execpath);
			llinfos << "mExecutableDir = [" << mExecutableDir << "]" << llendl;
		}
	}
	
	mLLPluginDir = mExecutableDir + mDirDelimiter + "llplugin";

	// *TODO: don't use /tmp, use $HOME/.secondlife/tmp or something.
	mTempDir = "/tmp";
}