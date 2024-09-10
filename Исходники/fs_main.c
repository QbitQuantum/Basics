void ide_fs_unmount(UINT32 param)
{
	int i;
	char mount_name[16];	
	int result;
	struct statvfs sfs;
	int fd;
	
	char dirbuf[sizeof(struct dirent) + 32];	
	struct dirent *dire = (struct dirent *)dirbuf;

	unlink_device("/c", MNT_TYPE_IDE);
	unlink_device("/r", MNT_TYPE_IDE);

	fd = fs_opendir("/mnt");

	while (fs_readdir(fd, dire) > 0)
	{
		fs_get_mount_name(MNT_TYPE_IDE, 0, 0, mount_name);
		if(!MEMCMP(&dire->d_name, &mount_name[5], 3))
		{
			STRCPY(mount_name, "/mnt/");
			strcat(mount_name, dire->d_name);

			FS_PRINTF("unmount: %s ...\n", mount_name);
			result = fs_statvfs(mount_name, &sfs);
			if (result < 0)
			{
				FS_PRINTF("%s is not mounted! err = %d\n", mount_name, result);
				FS_NOTICE_MESSAGE(MP_FS_UNMOUNT, MNT_MSG_PARAM(UNMNT_FAILED, MNT_TYPE_IDE, 0));
//				IDE_MESSAGE(MP_FS_UNMOUNT, UNMNT_FAILED);	
				continue;
			}

			result = fs_unmount(mount_name, 1);
			if (result < 0)
			{
				FS_PRINTF("%s unmounted failed! err = %d\n", mount_name, result);
				FS_NOTICE_MESSAGE(MP_FS_UNMOUNT, MNT_MSG_PARAM(UNMNT_FAILED, MNT_TYPE_IDE, 0));
//				IDE_MESSAGE(MP_FS_UNMOUNT, UNMNT_FAILED);
			}
			else
			{
				FS_PRINTF("%s unmounted successed!\n", mount_name);
			}

	        result = fs_rmdir(mount_name);
			if (result < 0)
			{
	            FS_PRINTF("remove dir %s failed! err = %d\n", mount_name, result);
			}
		}	
	}	

	fs_closedir(fd);
    ide_hdd_cleanup(0);
	FS_NOTICE_MESSAGE(MP_FS_UNMOUNT, MNT_MSG_PARAM(UNMNT_UNMOUNT_OK, MNT_TYPE_IDE, 0));
//	IDE_MESSAGE(MP_FS_UNMOUNT, UNMNT_UNMOUNT_OK);
}