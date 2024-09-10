int main(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    struct passwd *usr;
    struct group *grp;
    struct tm *tme;
    char buf[512];
    char fileperm[512];
    char tmbuf[100];    

	if(argv[1]==NULL){
  		perror("usage ./a.out file/directory_name\n");
  		exit(0);
  	}
  	
  	if((mydir = opendir(argv[1]))==NULL){
  		perror("no such file or directory\n");
  		exit(0);
  	}
  	
	
	usr=getpwuid(mystat.st_mode);
    grp=getgrgid(mystat.st_mode);
    while((myfile = readdir(mydir)) != NULL){
            sprintf(buf, "%s/%s", argv[1], myfile->d_name);   //appends the filename with the path
    		if((lstat(buf, &mystat))<0){
    			perror("stat error\n");
    		}  
    		
	 	    switch (mystat.st_mode & S_IFMT) {
        	    case S_IFDIR:  printf("d ");            break;
        		case S_IFREG:  printf("r ");            break;
        		default:       printf("- ");            break;
    		}
    		
    		tme=localtime(&mystat.st_mtime);
    		strftime(tmbuf,sizeof(tmbuf),"%A %B %H:%M:%S",tme);
    		 
    		sprintf(fileperm,"%c%c%c%c%c%c%c%c%c",
    		(mystat.st_mode)& S_IRUSR ? 'r':'-',
    		(mystat.st_mode)& S_IWUSR ? 'w':'-',
    		(mystat.st_mode)& S_IXUSR ? 'x':'-',
    		(mystat.st_mode)& S_IRGRP ? 'r':'-',
    		(mystat.st_mode)& S_IRGRP ? 'w':'-',
    		(mystat.st_mode)& S_IXGRP ? 'x':'-',
    		(mystat.st_mode)& S_IROTH ? 'r':'-',
    		(mystat.st_mode)& S_IWOTH ? 'w':'-',
    		(mystat.st_mode)& S_IXOTH ? 'x':'-'
    		);
    		
    		printf("%s ",fileperm);
    		printf("%d ",mystat.st_nlink);
    		printf("%s ",usr->pw_name);
    		printf("%s ",grp->gr_name);
    		printf("%s",tmbuf);
    		printf("%d ",mystat.st_size);
    		printf("%s\n", myfile->d_name);
        
    	}
    	closedir(mydir);
	return 0;



}