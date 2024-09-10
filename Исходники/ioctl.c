static int setflags(struct inode *inode, int flags)
{
	int oldflags, err, release;
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	struct ubifs_budget_req req = { .dirtied_ino = 1,
					.dirtied_ino_d = ui->data_len };

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	/*
	 * The IMMUTABLE and APPEND_ONLY flags can only be changed by
	 * the relevant capability.
	 */
	mutex_lock(&ui->ui_mutex);
	oldflags = ubifs2ioctl(ui->flags);
	if ((flags ^ oldflags) & (FS_APPEND_FL | FS_IMMUTABLE_FL)) {
		if (!capable(CAP_LINUX_IMMUTABLE)) {
			err = -EPERM;
			goto out_unlock;
		}
	}

	ui->flags = ioctl2ubifs(flags);
	ubifs_set_inode_flags(inode);
	inode->i_ctime = ubifs_current_time(inode);
	release = ui->dirty;
	mark_inode_dirty_sync(inode);
	mutex_unlock(&ui->ui_mutex);

	if (release)
		ubifs_release_budget(c, &req);
	if (IS_SYNC(inode))
		err = write_inode_now(inode, 1);
	return err;

out_unlock:
	ubifs_err("can't modify inode %lu attributes", inode->i_ino);
	mutex_unlock(&ui->ui_mutex);
	ubifs_release_budget(c, &req);
	return err;
}

long ubifs_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int flags, err;
	struct inode *inode = file->f_path.dentry->d_inode;

	switch (cmd) {
	case FS_IOC_GETFLAGS:
		flags = ubifs2ioctl(ubifs_inode(inode)->flags);

		dbg_gen("get flags: %#x, i_flags %#x", flags, inode->i_flags);
		return put_user(flags, (int __user *) arg);

	case FS_IOC_SETFLAGS: {
		if (IS_RDONLY(inode))
			return -EROFS;

		if (!inode_owner_or_capable(inode))
			return -EACCES;

		if (get_user(flags, (int __user *) arg))
			return -EFAULT;

		if (!S_ISDIR(inode->i_mode))
			flags &= ~FS_DIRSYNC_FL;

		/*
		 * Make sure the file-system is read-write and make sure it
		 * will not become read-only while we are changing the flags.
		 */
		err = mnt_want_write(file->f_path.mnt);
		if (err)
			return err;
		dbg_gen("set flags: %#x, i_flags %#x", flags, inode->i_flags);
		err = setflags(inode, flags);
		mnt_drop_write(file->f_path.mnt);
		return err;
	}

	default:
		return -ENOTTY;
	}
}