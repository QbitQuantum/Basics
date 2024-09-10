int
cifs_get_inode_info_unix(struct inode **pinode,
			 const unsigned char *search_path,
			 struct super_block *sb,int xid)
{
	int rc = 0;
	FILE_UNIX_BASIC_INFO findData;
	struct cifsTconInfo *pTcon;
	struct inode *inode;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	char *tmp_path;

	pTcon = cifs_sb->tcon;
	cFYI(1, (" Getting info on %s ", search_path));
	/* we could have done a find first instead but this returns more info */
	rc = CIFSSMBUnixQPathInfo(xid, pTcon, search_path, &findData,
				  cifs_sb->local_nls);
	/* dump_mem("\nUnixQPathInfo return data", &findData, sizeof(findData)); */
	if (rc) {
		if (rc == -EREMOTE) {
			tmp_path =
			    kmalloc(strnlen
				    (pTcon->treeName,
				     MAX_TREE_SIZE + 1) +
				    strnlen(search_path, MAX_PATHCONF) + 1,
				    GFP_KERNEL);
			if (tmp_path == NULL) {
				return -ENOMEM;
			}
        /* have to skip first of the double backslash of UNC name */
			strncpy(tmp_path, pTcon->treeName, MAX_TREE_SIZE);	
			strncat(tmp_path, search_path, MAX_PATHCONF);
			rc = connect_to_dfs_path(xid, pTcon->ses,
						 /* treename + */ tmp_path,
						 cifs_sb->local_nls);
			kfree(tmp_path);

			/* BB fix up inode etc. */
		} else if (rc) {
			return rc;
		}

	} else {
		struct cifsInodeInfo *cifsInfo;

		/* get new inode */
		if (*pinode == NULL) {
			*pinode = new_inode(sb);
			if(*pinode == NULL) 
				return -ENOMEM;
			insert_inode_hash(*pinode);
		}
			
		inode = *pinode;
		cifsInfo = CIFS_I(inode);

		cFYI(1, (" Old time %ld ", cifsInfo->time));
		cifsInfo->time = jiffies;
		cFYI(1, (" New time %ld ", cifsInfo->time));
		atomic_set(&cifsInfo->inUse,1);	/* ok to set on every refresh of inode */

		inode->i_atime =
		    cifs_NTtimeToUnix(le64_to_cpu(findData.LastAccessTime));
		inode->i_mtime =
		    cifs_NTtimeToUnix(le64_to_cpu
				(findData.LastModificationTime));
		inode->i_ctime =
		    cifs_NTtimeToUnix(le64_to_cpu(findData.LastStatusChange));
		inode->i_mode = le64_to_cpu(findData.Permissions);
		findData.Type = le32_to_cpu(findData.Type);
		if (findData.Type == UNIX_FILE) {
			inode->i_mode |= S_IFREG;
		} else if (findData.Type == UNIX_SYMLINK) {
			inode->i_mode |= S_IFLNK;
		} else if (findData.Type == UNIX_DIR) {
			inode->i_mode |= S_IFDIR;
		} else if (findData.Type == UNIX_CHARDEV) {
			inode->i_mode |= S_IFCHR;
			inode->i_rdev = MKDEV(le64_to_cpu(findData.DevMajor),
				le64_to_cpu(findData.DevMinor) & MINORMASK);
		} else if (findData.Type == UNIX_BLOCKDEV) {
			inode->i_mode |= S_IFBLK;
			inode->i_rdev = MKDEV(le64_to_cpu(findData.DevMajor),
				le64_to_cpu(findData.DevMinor) & MINORMASK);
		} else if (findData.Type == UNIX_FIFO) {
			inode->i_mode |= S_IFIFO;
		} else if (findData.Type == UNIX_SOCKET) {
			inode->i_mode |= S_IFSOCK;
		}
		inode->i_uid = le64_to_cpu(findData.Uid);
		inode->i_gid = le64_to_cpu(findData.Gid);
		inode->i_nlink = le64_to_cpu(findData.Nlinks);
		findData.NumOfBytes = le64_to_cpu(findData.NumOfBytes);
		findData.EndOfFile = le64_to_cpu(findData.EndOfFile);

		if(is_size_safe_to_change(cifsInfo)) {
		/* can not safely change the file size here if the 
		   client is writing to it due to potential races */

			i_size_write(inode,findData.EndOfFile);
/* blksize needs to be multiple of two. So safer to default to blksize
	and blkbits set in superblock so 2**blkbits and blksize will match */
/*		inode->i_blksize =
		    (pTcon->ses->server->maxBuf - MAX_CIFS_HDR_SIZE) & 0xFFFFFE00;*/

		/* This seems incredibly stupid but it turns out that
		i_blocks is not related to (i_size / i_blksize), instead a
		size of 512 is required to be used for calculating num blocks */
		 

/*		inode->i_blocks = 
	                (inode->i_blksize - 1 + findData.NumOfBytes) >> inode->i_blkbits;*/

		/* 512 bytes (2**9) is the fake blocksize that must be used */
		/* for this calculation */
			inode->i_blocks = (512 - 1 + findData.NumOfBytes) >> 9;
		}

		if (findData.NumOfBytes < findData.EndOfFile)
			cFYI(1, ("Server inconsistency Error: it says allocation size less than end of file "));
		cFYI(1,
		     ("Size %ld and blocks %ld ",
		      (unsigned long) inode->i_size, inode->i_blocks));
		if (S_ISREG(inode->i_mode)) {
			cFYI(1, (" File inode "));
			inode->i_op = &cifs_file_inode_ops;
			inode->i_fop = &cifs_file_ops;
			inode->i_data.a_ops = &cifs_addr_ops;
		} else if (S_ISDIR(inode->i_mode)) {
			cFYI(1, (" Directory inode"));
			inode->i_op = &cifs_dir_inode_ops;
			inode->i_fop = &cifs_dir_ops;
		} else if (S_ISLNK(inode->i_mode)) {
			cFYI(1, (" Symbolic Link inode "));
			inode->i_op = &cifs_symlink_inode_ops;
/* tmp_inode->i_fop = *//* do not need to set to anything */
		} else {
			cFYI(1, (" Init special inode "));
			init_special_inode(inode, inode->i_mode,
					   inode->i_rdev);
		}
	}
	return rc;
}