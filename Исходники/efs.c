/**
 * This function will set a hook function, which will be invoked when a memory 
 * block is allocated from heap memory.
 * 
 * @param hook the hook function
 */
int efs_rename(struct dfs_filesystem* fs, const char* oldpath, const char* newpath)
{
	FileRecord old_entry, new_entry;
	FileLocation old_loc, new_loc;
	efsl_fs* efsfs;
	eint8 fatfilename[11];
	
	efsfs = (efsl_fs*) fs->data ;
	RT_ASSERT(efsfs != RT_NULL);

	dir_getFatFileName((eint8 *)newpath, &fatfilename[0]);	
	
	/* parameters check */
	if (strlen(oldpath) > DFS_PATH_MAX || 
		strlen(newpath) > DFS_PATH_MAX ||
		/* old path is a directory that contains newpath */
		strncmp(oldpath, newpath, strlen(newpath)) == 0) 
		{
			dfs_log(DFS_DEBUG_ERROR, ("old path is a directory that contains newpath"));					
			return -DFS_STATUS_EINVAL;
		}	

	/* if can't find old direntry */
	if(fs_findFile(&efsfs->filesystem, (eint8 *)oldpath, &old_loc, 0) == 0)
	{
		dfs_log(DFS_DEBUG_ERROR, ("can't find old direntry"));		
		return -DFS_STATUS_ENOENT;
	}
	dir_getFileStructure(&efsfs->filesystem, &old_entry, &old_loc);

	/* if the new direntry exist */
	if(fs_findFile(&efsfs->filesystem, (eint8 *)newpath, &new_loc, 0) > 0)
	{
		dfs_log(DFS_DEBUG_ERROR, ("new direntry existed"));
		return -DFS_STATUS_ENOENT;
	}
	if(fs_findFreeFile(&efsfs->filesystem, (eint8 *)newpath, &new_loc, 0))
	{
		memCpy(&old_entry, &new_entry, sizeof(FileRecord));	
		memCpy(fatfilename, new_entry.FileName, 11);
		dir_createDirectoryEntry(&efsfs->filesystem, &new_entry, &new_loc);
	}

	/* delete the old direntry */
	old_entry.FileName[0] = 0xe5;
	dir_updateDirectoryEntry(&efsfs->filesystem, &old_entry, &old_loc);	

	return 0;
}