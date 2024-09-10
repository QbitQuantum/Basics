/*
 *  Synopsis:
 *	Handle reply from client after client took blob.
 */
static int
sha_fs_take_reply(struct request *r, char *reply)
{
	struct sha_fs_request *sp = (struct sha_fs_request *)r->open_data;

	/*
	 *  If client replies 'ok', then delete the blob.
	 *  Eventually need to lock the file.
	 */
	if (*reply == 'o') {
		int exists = 1;
		char *slash;

		if (_unlink(r, sp->blob_path, &exists))
			_panic(r, "_unlink() failed");
		if (!exists)
			_warn2(r, "expected blob file does not exist",
							sp->blob_path);
		/*
		 *  Request trimming the empty directories.
		 */
		if ((slash = rindex(sp->blob_path, '/'))) {
			*slash = 0;
			arbor_trim(sp->blob_path);
			*slash = '/';
		}
		else
			_panic2(r, "slash missing from blob path",
							sp->blob_path);
	}
	return 0;
}