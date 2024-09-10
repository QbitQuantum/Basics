/*
 * Done staging file.  Compare accumulated checksum value on stage
 * against value generated during archive.  Upon successful completion
 * return a zero.  Otherwise, this function returns errno.
 */
int
ChecksumCompare(
	int fd,
	sam_id_t *id)
{
	struct sam_perm_inode pi;
	struct sam_ioctl_idstat idstat;
	int i;
	int retval;

	ASSERT(checksum != NULL);

	retval = 0;

	idstat.id = *id;
	idstat.size = sizeof (pi);
	idstat.dp.ptr = &pi;
	if (ioctl(fd, F_IDSTAT, &idstat) != 0) {
		retval = errno;
	}

	if (retval == 0 && checksum != NULL) {
		for (i = 0; i < 4; i++) {
			if (pi.csum.csum_val[i] != checksum->val.csum_val[i]) {
				retval = EDVVCMP;
				break;
			}
		}

		/* Checksum failed.  Try endian repair calculation. */
		if (retval == EDVVCMP && pi.di.cs_algo == CS_SIMPLE) {
			retval = 0;
			Trace(TR_MISC, "Trying alternate-endian checksum "
			    "inode: %d.%d", id->ino, id->gen);
			Trace(TR_FILES, "Checksum inode: %d.%d "
			    "length: %lld cookie: %lld",
			    id->ino, id->gen, (u_longlong_t)pi.di.rm.size,
			    checksum->seed);
			cs_repair((uchar_t *)&pi.csum.csum_val[0],
			    &checksum->seed);
			for (i = 0; i < 4; i++) {
				if (pi.csum.csum_val[i] !=
				    checksum->val.csum_val[i]) {
					retval = EDVVCMP;
					break;
				}
			}
		}

		if (retval == EDVVCMP) {
			SetErrno = 0;		/* set for trace */
			Trace(TR_ERR, "Checksum error inode: %d.%d",
			    id->ino, id->gen);
			Trace(TR_ERR, "Checksum value: %.8x %.8x %.8x %.8x",
			    pi.csum.csum_val[0], pi.csum.csum_val[1],
			    pi.csum.csum_val[2], pi.csum.csum_val[3]);
			Trace(TR_ERR, "Checksum calc: %.8x %.8x %.8x %.8x",
			    checksum->val.csum_val[0],
			    checksum->val.csum_val[1],
			    checksum->val.csum_val[2],
			    checksum->val.csum_val[3]);
		}
	}

	return (retval);
}