static void
GetFileInfo(FD_t fd, int *size, char **ctime, char **mtime, char **atime)
{
#ifdef AFS_NT40_ENV
    BY_HANDLE_FILE_INFORMATION fi;
    if (!GetFileInformationByHandle(fd, &fi)) {
	printf("GetFileInformationByHandle failed, exiting\n");
	exit(1);
    }
    *size = (int)fi.nFileSizeLow;
    *ctime = "N/A";
    *mtime = NT_date(&fi.ftLastWriteTime);
    *atime = NT_date(&fi.ftLastAccessTime);
#else
    struct afs_stat status;
    if (afs_fstat(fd, &status) == -1) {
	printf("fstat failed %d\n", errno);
	exit(1);
    }
    *size = (int)status.st_size;
    *ctime = date(status.st_ctime);
    *mtime = date(status.st_mtime);
    *atime = date(status.st_atime);
#endif
}