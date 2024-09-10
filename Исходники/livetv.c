/*
 * cmyth_livetv_chain_seek(cmyth_recorder_t file, long long offset, int whence)
 * 
 * Scope: PUBLIC
 *
 * Description
 *
 * Seek to a new position in the file based on the value of whence:
 *	SEEK_SET
 *		The offset is set to offset bytes.
 *	SEEK_CUR
 *		The offset is set to the current position plus offset bytes.
 *	SEEK_END
 *		The offset is set to the size of the file minus offset bytes.
 *
 * Return Value:
 *
 * Sucess: 0
 *
 * Failure: an int containing -errno
 */
static long long
cmyth_livetv_chain_seek(cmyth_recorder_t rec, long long offset, int whence)
{
	long long ret;
	cmyth_file_t fp;
	int cur, ct;

	if (rec == NULL)
		return -EINVAL;

	ct  = rec->rec_livetv_chain->chain_ct;

	if (whence == SEEK_END) {

		offset -= rec->rec_livetv_file->file_req;
		for (cur = rec->rec_livetv_chain->chain_current; cur < ct; cur++) {
			offset += rec->rec_livetv_chain->chain_files[cur]->file_length;
		}

		cur = rec->rec_livetv_chain->chain_current;
		fp  = rec->rec_livetv_chain->chain_files[cur];
		whence = SEEK_CUR;
	}

	if (whence == SEEK_SET) {

		for (cur = 0; cur < ct; cur++) {
    			fp = rec->rec_livetv_chain->chain_files[cur];
			if (offset < (long long)fp->file_length)
				break;
			offset -= fp->file_length;
		}
	}

	if (whence == SEEK_CUR) {

	if (offset == 0) {
		cur     = rec->rec_livetv_chain->chain_current;
		offset += rec->rec_livetv_chain->chain_files[cur]->file_req;
		for (; cur > 0; cur--) {
			offset += rec->rec_livetv_chain->chain_files[cur-1]->file_length;
		}
		return offset;
	}
  else
  {
    cur = rec->rec_livetv_chain->chain_current;
		fp  = rec->rec_livetv_chain->chain_files[cur];
  }

	offset += fp->file_req;

	while (offset > (long long)fp->file_length) {
		cur++;
		offset -= fp->file_length;
		if(cur == ct)
			return -1;
		fp = rec->rec_livetv_chain->chain_files[cur];
	}

	while (offset < 0) {
		cur--;
		if(cur < 0)
			return -1;
		fp = rec->rec_livetv_chain->chain_files[cur];
		offset += fp->file_length;
	}

	offset -= fp->file_req;
  }

	pthread_mutex_lock(&mutex);

	ret = cmyth_file_seek_unlocked(fp, offset, whence);

	PRINTF("** SSDEBUG: new pos %lld after seek command\n", ret);

	cur -= rec->rec_livetv_chain->chain_current;
	if (ret >= 0 && cur) {
		cmyth_livetv_chain_switch(rec, cur);
	}

	pthread_mutex_unlock(&mutex);

	return ret;
}