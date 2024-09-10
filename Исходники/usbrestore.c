/**************************************************************************
* Function: GetDirSizeandFiles

* Functionality: Get the total files and total file size of a directory

* @IN :srcname: the directory path name.
* @OUT: 
	totalSize: total file size
	filenum: total files
	0 OK else error 

* Date: 20080312
* Changed history:
* Date          Who             Reason
* 20080312  sandy           First  creation
***************************************************************************/ 
int GetDirSizeandFiles( const char * srcname, long long *totalSize, int *filenum)
{
	DIR *Psdir = NULL;
	DIR *PchilDir = NULL;
	struct stat filestat;
	char srcfile[FILE_PATH_LEN] = {0};
	struct dirent *srcdir;
	int iRet = 0;
	int isDir;
	
	if(!srcname || strlen(srcname) < 0){
		fprintf(stderr,"src dir is null\n");
		iRet = -1;
		goto Funcout;
	}
	if(!CheckFilePresent(srcname, &isDir)){
		return -1;
	}
	
	if(!isDir){
		*totalSize += getFileSize((char *)srcname);
		(*filenum) ++;
	}
	else{
		if((Psdir = opendir(srcname)) == NULL){
			fprintf(stderr,"open src dir failed\n");
			iRet = -1;
			goto Funcout;
		}
		while((srcdir = readdir(Psdir)) != NULL)
		{
			if(srcdir->d_ino == 0)
				continue;
			
			memset(srcfile, 0, FILE_PATH_LEN);
			strcpy(srcfile,srcname);
			strcat(srcfile, "/");
			strcat(srcfile, srcdir->d_name);
			
			if((lstat(srcfile, &filestat)) < 0)
			{
				continue;
			}
			
			if(((filestat.st_mode & S_IFMT) != S_IFLNK) && ((filestat.st_mode & S_IFMT) == S_IFDIR) && (strcmp(srcdir->d_name, ".") != 0) && (strcmp(srcdir->d_name, "..") != 0))
			{
				if((PchilDir = opendir(srcfile)) == NULL)
				{
					fprintf(stderr,"can not enter the dir %s\n", srcfile);
					iRet = -1;
					goto Funcout;
				}
			
				*totalSize += 1;
				GetDirSizeandFiles((const char *)srcfile, totalSize,filenum);
				closedir(PchilDir);
			}
			
			else if(((filestat.st_mode & S_IFMT) != S_IFLNK) && ((filestat.st_mode & S_IFMT) == S_IFREG) && (strcmp(srcdir->d_name, ".") != 0) && (strcmp(srcdir->d_name, "..") != 0))
			{
				*totalSize += filestat.st_size/(1024*1024);
				(*filenum) ++;
			}
		}
	}
	Funcout:
			if(Psdir)
			closedir(Psdir);
	
	return iRet;
}