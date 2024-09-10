static int ext2_fill_super(struct super_block *sb, void *data, int silent)
{
	struct buffer_head * bh;
	struct ext2_sb_info * sbi;
	struct ext2_super_block * es;
	struct inode *root;
	unsigned long block;
	unsigned long sb_block = get_sb_block(&data);
	unsigned long logic_sb_block;
	unsigned long offset = 0;
	unsigned long def_mount_opts;
	int blocksize = BLOCK_SIZE;
	int db_count;
	int i, j;
	__le32 features;

	sbi = kmalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;
	sb->s_fs_info = sbi;
	memset(sbi, 0, sizeof(*sbi));

	/*
	 * See what the current blocksize for the device is, and
	 * use that as the blocksize.  Otherwise (or if the blocksize
	 * is smaller than the default) use the default.
	 * This is important for devices that have a hardware
	 * sectorsize that is larger than the default.
	 */
	blocksize = sb_min_blocksize(sb, BLOCK_SIZE);
	if (!blocksize) {
		printk ("EXT2-fs: unable to set blocksize\n");
		goto failed_sbi;
	}

	/*
	 * If the superblock doesn't start on a hardware sector boundary,
	 * calculate the offset.  
	 */
	if (blocksize != BLOCK_SIZE) {
		logic_sb_block = (sb_block*BLOCK_SIZE) / blocksize;
		offset = (sb_block*BLOCK_SIZE) % blocksize;
	} else {
		logic_sb_block = sb_block;
	}

	if (!(bh = sb_bread(sb, logic_sb_block))) {
		printk ("EXT2-fs: unable to read superblock\n");
		goto failed_sbi;
	}
	/*
	 * Note: s_es must be initialized as soon as possible because
	 *       some ext2 macro-instructions depend on its value
	 */
	es = (struct ext2_super_block *) (((char *)bh->b_data) + offset);
	sbi->s_es = es;
	sb->s_magic = le16_to_cpu(es->s_magic);

	if (sb->s_magic != EXT2_SUPER_MAGIC)
		goto cantfind_ext2;

	/* Set defaults before we parse the mount options */
	def_mount_opts = le32_to_cpu(es->s_default_mount_opts);
	if (def_mount_opts & EXT2_DEFM_DEBUG)
		set_opt(sbi->s_mount_opt, DEBUG);
	if (def_mount_opts & EXT2_DEFM_BSDGROUPS)
		set_opt(sbi->s_mount_opt, GRPID);
	if (def_mount_opts & EXT2_DEFM_UID16)
		set_opt(sbi->s_mount_opt, NO_UID32);
	if (def_mount_opts & EXT2_DEFM_XATTR_USER)
		set_opt(sbi->s_mount_opt, XATTR_USER);
	if (def_mount_opts & EXT2_DEFM_ACL)
		set_opt(sbi->s_mount_opt, POSIX_ACL);
	
	if (le16_to_cpu(sbi->s_es->s_errors) == EXT2_ERRORS_PANIC)
		set_opt(sbi->s_mount_opt, ERRORS_PANIC);
	else if (le16_to_cpu(sbi->s_es->s_errors) == EXT2_ERRORS_RO)
		set_opt(sbi->s_mount_opt, ERRORS_RO);

	sbi->s_resuid = le16_to_cpu(es->s_def_resuid);
	sbi->s_resgid = le16_to_cpu(es->s_def_resgid);
	
	if (!parse_options ((char *) data, sbi))
		goto failed_mount;

	sb->s_flags = (sb->s_flags & ~MS_POSIXACL) |
		((EXT2_SB(sb)->s_mount_opt & EXT2_MOUNT_POSIX_ACL) ?
		 MS_POSIXACL : 0);

	if (le32_to_cpu(es->s_rev_level) == EXT2_GOOD_OLD_REV &&
	    (EXT2_HAS_COMPAT_FEATURE(sb, ~0U) ||
	     EXT2_HAS_RO_COMPAT_FEATURE(sb, ~0U) ||
	     EXT2_HAS_INCOMPAT_FEATURE(sb, ~0U)))
		printk("EXT2-fs warning: feature flags set on rev 0 fs, "
		       "running e2fsck is recommended\n");
	/*
	 * Check feature flags regardless of the revision level, since we
	 * previously didn't change the revision level when setting the flags,
	 * so there is a chance incompat flags are set on a rev 0 filesystem.
	 */
	features = EXT2_HAS_INCOMPAT_FEATURE(sb, ~EXT2_FEATURE_INCOMPAT_SUPP);
	if (features) {
		printk("EXT2-fs: %s: couldn't mount because of "
		       "unsupported optional features (%x).\n",
		       sb->s_id, le32_to_cpu(features));
		goto failed_mount;
	}
	if (!(sb->s_flags & MS_RDONLY) &&
	    (features = EXT2_HAS_RO_COMPAT_FEATURE(sb, ~EXT2_FEATURE_RO_COMPAT_SUPP))){
		printk("EXT2-fs: %s: couldn't mount RDWR because of "
		       "unsupported optional features (%x).\n",
		       sb->s_id, le32_to_cpu(features));
		goto failed_mount;
	}

	blocksize = BLOCK_SIZE << le32_to_cpu(sbi->s_es->s_log_block_size);

	/* If the blocksize doesn't match, re-read the thing.. */
	if (sb->s_blocksize != blocksize) {
		brelse(bh);

		if (!sb_set_blocksize(sb, blocksize)) {
			printk(KERN_ERR "EXT2-fs: blocksize too small for device.\n");
			goto failed_sbi;
		}

		logic_sb_block = (sb_block*BLOCK_SIZE) / blocksize;
		offset = (sb_block*BLOCK_SIZE) % blocksize;
		bh = sb_bread(sb, logic_sb_block);
		if(!bh) {
			printk("EXT2-fs: Couldn't read superblock on "
			       "2nd try.\n");
			goto failed_sbi;
		}
		es = (struct ext2_super_block *) (((char *)bh->b_data) + offset);
		sbi->s_es = es;
		if (es->s_magic != cpu_to_le16(EXT2_SUPER_MAGIC)) {
			printk ("EXT2-fs: Magic mismatch, very weird !\n");
			goto failed_mount;
		}
	}

	sb->s_maxbytes = ext2_max_size(sb->s_blocksize_bits);

	if (le32_to_cpu(es->s_rev_level) == EXT2_GOOD_OLD_REV) {
		sbi->s_inode_size = EXT2_GOOD_OLD_INODE_SIZE;
		sbi->s_first_ino = EXT2_GOOD_OLD_FIRST_INO;
	} else {
		sbi->s_inode_size = le16_to_cpu(es->s_inode_size);
		sbi->s_first_ino = le32_to_cpu(es->s_first_ino);
		if ((sbi->s_inode_size < EXT2_GOOD_OLD_INODE_SIZE) ||
		    (sbi->s_inode_size & (sbi->s_inode_size - 1)) ||
		    (sbi->s_inode_size > blocksize)) {
			printk ("EXT2-fs: unsupported inode size: %d\n",
				sbi->s_inode_size);
			goto failed_mount;
		}
	}

	sbi->s_frag_size = EXT2_MIN_FRAG_SIZE <<
				   le32_to_cpu(es->s_log_frag_size);
	if (sbi->s_frag_size == 0)
		goto cantfind_ext2;
	sbi->s_frags_per_block = sb->s_blocksize / sbi->s_frag_size;

	sbi->s_blocks_per_group = le32_to_cpu(es->s_blocks_per_group);
	sbi->s_frags_per_group = le32_to_cpu(es->s_frags_per_group);
	sbi->s_inodes_per_group = le32_to_cpu(es->s_inodes_per_group);

	if (EXT2_INODE_SIZE(sb) == 0)
		goto cantfind_ext2;
	sbi->s_inodes_per_block = sb->s_blocksize / EXT2_INODE_SIZE(sb);
	if (sbi->s_inodes_per_block == 0)
		goto cantfind_ext2;
	sbi->s_itb_per_group = sbi->s_inodes_per_group /
					sbi->s_inodes_per_block;
	sbi->s_desc_per_block = sb->s_blocksize /
					sizeof (struct ext2_group_desc);
	sbi->s_sbh = bh;
	sbi->s_mount_state = le16_to_cpu(es->s_state);
	sbi->s_addr_per_block_bits =
		log2 (EXT2_ADDR_PER_BLOCK(sb));
	sbi->s_desc_per_block_bits =
		log2 (EXT2_DESC_PER_BLOCK(sb));

	if (sb->s_magic != EXT2_SUPER_MAGIC)
		goto cantfind_ext2;

	if (sb->s_blocksize != bh->b_size) {
		if (!silent)
			printk ("VFS: Unsupported blocksize on dev "
				"%s.\n", sb->s_id);
		goto failed_mount;
	}

	if (sb->s_blocksize != sbi->s_frag_size) {
		printk ("EXT2-fs: fragsize %lu != blocksize %lu (not supported yet)\n",
			sbi->s_frag_size, sb->s_blocksize);
		goto failed_mount;
	}

	if (sbi->s_blocks_per_group > sb->s_blocksize * 8) {
		printk ("EXT2-fs: #blocks per group too big: %lu\n",
			sbi->s_blocks_per_group);
		goto failed_mount;
	}
	if (sbi->s_frags_per_group > sb->s_blocksize * 8) {
		printk ("EXT2-fs: #fragments per group too big: %lu\n",
			sbi->s_frags_per_group);
		goto failed_mount;
	}
	if (sbi->s_inodes_per_group > sb->s_blocksize * 8) {
		printk ("EXT2-fs: #inodes per group too big: %lu\n",
			sbi->s_inodes_per_group);
		goto failed_mount;
	}

	if (EXT2_BLOCKS_PER_GROUP(sb) == 0)
		goto cantfind_ext2;
	sbi->s_groups_count = (le32_to_cpu(es->s_blocks_count) -
				        le32_to_cpu(es->s_first_data_block) +
				       EXT2_BLOCKS_PER_GROUP(sb) - 1) /
				       EXT2_BLOCKS_PER_GROUP(sb);
	db_count = (sbi->s_groups_count + EXT2_DESC_PER_BLOCK(sb) - 1) /
		   EXT2_DESC_PER_BLOCK(sb);
	sbi->s_group_desc = kmalloc (db_count * sizeof (struct buffer_head *), GFP_KERNEL);
	if (sbi->s_group_desc == NULL) {
		printk ("EXT2-fs: not enough memory\n");
		goto failed_mount;
	}
	percpu_counter_init(&sbi->s_freeblocks_counter);
	percpu_counter_init(&sbi->s_freeinodes_counter);
	percpu_counter_init(&sbi->s_dirs_counter);
	bgl_lock_init(&sbi->s_blockgroup_lock);
	sbi->s_debts = kmalloc(sbi->s_groups_count * sizeof(*sbi->s_debts),
			       GFP_KERNEL);
	if (!sbi->s_debts) {
		printk ("EXT2-fs: not enough memory\n");
		goto failed_mount_group_desc;
	}
	memset(sbi->s_debts, 0, sbi->s_groups_count * sizeof(*sbi->s_debts));
	for (i = 0; i < db_count; i++) {
		block = descriptor_loc(sb, logic_sb_block, i);
		sbi->s_group_desc[i] = sb_bread(sb, block);
		if (!sbi->s_group_desc[i]) {
			for (j = 0; j < i; j++)
				brelse (sbi->s_group_desc[j]);
			printk ("EXT2-fs: unable to read group descriptors\n");
			goto failed_mount_group_desc;
		}
	}
	if (!ext2_check_descriptors (sb)) {
		printk ("EXT2-fs: group descriptors corrupted!\n");
		db_count = i;
		goto failed_mount2;
	}
	sbi->s_gdb_count = db_count;
	get_random_bytes(&sbi->s_next_generation, sizeof(u32));
	spin_lock_init(&sbi->s_next_gen_lock);
	/*
	 * set up enough so that it can read an inode
	 */
	sb->s_op = &ext2_sops;
	sb->s_export_op = &ext2_export_ops;
	sb->s_xattr = ext2_xattr_handlers;
	root = iget(sb, EXT2_ROOT_INO);
	sb->s_root = d_alloc_root(root);
	if (!sb->s_root) {
		iput(root);
		printk(KERN_ERR "EXT2-fs: get root inode failed\n");
		goto failed_mount2;
	}
	if (!S_ISDIR(root->i_mode) || !root->i_blocks || !root->i_size) {
		dput(sb->s_root);
		sb->s_root = NULL;
		printk(KERN_ERR "EXT2-fs: corrupt root inode, run e2fsck\n");
		goto failed_mount2;
	}
	if (EXT2_HAS_COMPAT_FEATURE(sb, EXT3_FEATURE_COMPAT_HAS_JOURNAL))
		ext2_warning(sb, __FUNCTION__,
			"mounting ext3 filesystem as ext2\n");
	ext2_setup_super (sb, es, sb->s_flags & MS_RDONLY);
	percpu_counter_mod(&sbi->s_freeblocks_counter,
				ext2_count_free_blocks(sb));
	percpu_counter_mod(&sbi->s_freeinodes_counter,
				ext2_count_free_inodes(sb));
	percpu_counter_mod(&sbi->s_dirs_counter,
				ext2_count_dirs(sb));
	return 0;

cantfind_ext2:
	if (!silent)
		printk("VFS: Can't find an ext2 filesystem on dev %s.\n",
		       sb->s_id);
	goto failed_mount;

failed_mount2:
	for (i = 0; i < db_count; i++)
		brelse(sbi->s_group_desc[i]);
failed_mount_group_desc:
	kfree(sbi->s_group_desc);
	kfree(sbi->s_debts);
failed_mount:
	brelse(bh);
failed_sbi:
	sb->s_fs_info = NULL;
	kfree(sbi);
	return -EINVAL;
}