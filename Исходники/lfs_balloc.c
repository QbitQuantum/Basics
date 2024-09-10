/* VOP_BWRITE ULFS_NIADDR+2 times */
int
lfs_balloc(struct vnode *vp, off_t startoffset, int iosize, kauth_cred_t cred,
    int flags, struct buf **bpp)
{
	int offset;
	daddr_t daddr, idaddr;
	struct buf *ibp, *bp;
	struct inode *ip;
	struct lfs *fs;
	struct indir indirs[ULFS_NIADDR+2], *idp;
	daddr_t	lbn, lastblock;
	int bcount;
	int error, frags, i, nsize, osize, num;

	ip = VTOI(vp);
	fs = ip->i_lfs;
	offset = lfs_blkoff(fs, startoffset);
	KASSERT(iosize <= lfs_sb_getbsize(fs));
	lbn = lfs_lblkno(fs, startoffset);
	/* (void)lfs_check(vp, lbn, 0); */

	ASSERT_MAYBE_SEGLOCK(fs);

	/*
	 * Three cases: it's a block beyond the end of file, it's a block in
	 * the file that may or may not have been assigned a disk address or
	 * we're writing an entire block.
	 *
	 * Note, if the daddr is UNWRITTEN, the block already exists in
	 * the cache (it was read or written earlier).	If so, make sure
	 * we don't count it as a new block or zero out its contents. If
	 * it did not, make sure we allocate any necessary indirect
	 * blocks.
	 *
	 * If we are writing a block beyond the end of the file, we need to
	 * check if the old last block was a fragment.	If it was, we need
	 * to rewrite it.
	 */

	if (bpp)
		*bpp = NULL;

	/* Check for block beyond end of file and fragment extension needed. */
	lastblock = lfs_lblkno(fs, ip->i_size);
	if (lastblock < ULFS_NDADDR && lastblock < lbn) {
		osize = lfs_blksize(fs, ip, lastblock);
		if (osize < lfs_sb_getbsize(fs) && osize > 0) {
			if ((error = lfs_fragextend(vp, osize, lfs_sb_getbsize(fs),
						    lastblock,
						    (bpp ? &bp : NULL), cred)))
				return (error);
			ip->i_size = (lastblock + 1) * lfs_sb_getbsize(fs);
			lfs_dino_setsize(fs, ip->i_din, ip->i_size);
			uvm_vnp_setsize(vp, ip->i_size);
			ip->i_flag |= IN_CHANGE | IN_UPDATE;
			if (bpp)
				(void) VOP_BWRITE(bp->b_vp, bp);
		}
	}

	/*
	 * If the block we are writing is a direct block, it's the last
	 * block in the file, and offset + iosize is less than a full
	 * block, we can write one or more fragments.  There are two cases:
	 * the block is brand new and we should allocate it the correct
	 * size or it already exists and contains some fragments and
	 * may need to extend it.
	 */
	if (lbn < ULFS_NDADDR && lfs_lblkno(fs, ip->i_size) <= lbn) {
		osize = lfs_blksize(fs, ip, lbn);
		nsize = lfs_fragroundup(fs, offset + iosize);
		if (lfs_lblktosize(fs, lbn) >= ip->i_size) {
			/* Brand new block or fragment */
			frags = lfs_numfrags(fs, nsize);
			if (!ISSPACE(fs, frags, cred))
				return ENOSPC;
			if (bpp) {
				*bpp = bp = getblk(vp, lbn, nsize, 0, 0);
				bp->b_blkno = UNWRITTEN;
				if (flags & B_CLRBUF)
					clrbuf(bp);
			}
			ip->i_lfs_effnblks += frags;
			mutex_enter(&lfs_lock);
			lfs_sb_subbfree(fs, frags);
			mutex_exit(&lfs_lock);
			lfs_dino_setdb(fs, ip->i_din, lbn, UNWRITTEN);
		} else {
			if (nsize <= osize) {
				/* No need to extend */
				if (bpp && (error = bread(vp, lbn, osize,
				    0, &bp)))
					return error;
			} else {
				/* Extend existing block */
				if ((error =
				     lfs_fragextend(vp, osize, nsize, lbn,
						    (bpp ? &bp : NULL), cred)))
					return error;
			}
			if (bpp)
				*bpp = bp;
		}
		return 0;
	}

	error = ulfs_bmaparray(vp, lbn, &daddr, &indirs[0], &num, NULL, NULL);
	if (error)
		return (error);

	KASSERT(daddr <= LFS_MAX_DADDR(fs));

	/*
	 * Do byte accounting all at once, so we can gracefully fail *before*
	 * we start assigning blocks.
	 */
	frags = fs->um_seqinc;
	bcount = 0;
	if (daddr == UNASSIGNED) {
		bcount = frags;
	}
	for (i = 1; i < num; ++i) {
		if (!indirs[i].in_exists) {
			bcount += frags;
		}
	}
	if (ISSPACE(fs, bcount, cred)) {
		mutex_enter(&lfs_lock);
		lfs_sb_subbfree(fs, bcount);
		mutex_exit(&lfs_lock);
		ip->i_lfs_effnblks += bcount;
	} else {
		return ENOSPC;
	}

	if (daddr == UNASSIGNED) {
		if (num > 0 && lfs_dino_getib(fs, ip->i_din, indirs[0].in_off) == 0) {
			lfs_dino_setib(fs, ip->i_din, indirs[0].in_off, UNWRITTEN);
		}

		/*
		 * Create new indirect blocks if necessary
		 */
		if (num > 1) {
			idaddr = lfs_dino_getib(fs, ip->i_din, indirs[0].in_off);
			for (i = 1; i < num; ++i) {
				ibp = getblk(vp, indirs[i].in_lbn,
				    lfs_sb_getbsize(fs), 0,0);
				if (!indirs[i].in_exists) {
					clrbuf(ibp);
					ibp->b_blkno = UNWRITTEN;
				} else if (!(ibp->b_oflags & (BO_DELWRI | BO_DONE))) {
					ibp->b_blkno = LFS_FSBTODB(fs, idaddr);
					ibp->b_flags |= B_READ;
					VOP_STRATEGY(vp, ibp);
					biowait(ibp);
				}
				/*
				 * This block exists, but the next one may not.
				 * If that is the case mark it UNWRITTEN to keep
				 * the accounting straight.
				 */
				/* XXX ondisk32 */
				if (((int32_t *)ibp->b_data)[indirs[i].in_off] == 0)
					((int32_t *)ibp->b_data)[indirs[i].in_off] =
						UNWRITTEN;
				/* XXX ondisk32 */
				idaddr = ((int32_t *)ibp->b_data)[indirs[i].in_off];
#ifdef DEBUG
				if (vp == fs->lfs_ivnode) {
					LFS_ENTER_LOG("balloc", __FILE__,
						__LINE__, indirs[i].in_lbn,
						ibp->b_flags, curproc->p_pid);
				}
#endif
				if ((error = VOP_BWRITE(ibp->b_vp, ibp)))
					return error;
			}
		}
	}


	/*
	 * Get the existing block from the cache, if requested.
	 */
	if (bpp)
		*bpp = bp = getblk(vp, lbn, lfs_blksize(fs, ip, lbn), 0, 0);

	/*
	 * Do accounting on blocks that represent pages.
	 */
	if (!bpp)
		lfs_register_block(vp, lbn);

	/*
	 * The block we are writing may be a brand new block
	 * in which case we need to do accounting.
	 *
	 * We can tell a truly new block because ulfs_bmaparray will say
	 * it is UNASSIGNED.  Once we allocate it we will assign it the
	 * disk address UNWRITTEN.
	 */
	if (daddr == UNASSIGNED) {
		if (bpp) {
			if (flags & B_CLRBUF)
				clrbuf(bp);

			/* Note the new address */
			bp->b_blkno = UNWRITTEN;
		}

		switch (num) {
		    case 0:
			lfs_dino_setdb(fs, ip->i_din, lbn, UNWRITTEN);
			break;
		    case 1:
			lfs_dino_setib(fs, ip->i_din, indirs[0].in_off, UNWRITTEN);
			break;
		    default:
			idp = &indirs[num - 1];
			if (bread(vp, idp->in_lbn, lfs_sb_getbsize(fs),
				  B_MODIFY, &ibp))
				panic("lfs_balloc: bread bno %lld",
				    (long long)idp->in_lbn);
			/* XXX ondisk32 */
			((int32_t *)ibp->b_data)[idp->in_off] = UNWRITTEN;
#ifdef DEBUG
			if (vp == fs->lfs_ivnode) {
				LFS_ENTER_LOG("balloc", __FILE__,
					__LINE__, idp->in_lbn,
					ibp->b_flags, curproc->p_pid);
			}
#endif
			VOP_BWRITE(ibp->b_vp, ibp);
		}
	} else if (bpp && !(bp->b_oflags & (BO_DONE|BO_DELWRI))) {
		/*
		 * Not a brand new block, also not in the cache;
		 * read it in from disk.
		 */
		if (iosize == lfs_sb_getbsize(fs))
			/* Optimization: I/O is unnecessary. */
			bp->b_blkno = daddr;
		else {
			/*
			 * We need to read the block to preserve the
			 * existing bytes.
			 */
			bp->b_blkno = daddr;
			bp->b_flags |= B_READ;
			VOP_STRATEGY(vp, bp);
			return (biowait(bp));
		}
	}

	return (0);
}