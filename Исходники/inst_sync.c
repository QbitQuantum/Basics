static int
in_sync_sys(char *pathname, uint_t flags)
{
	struct vnode *vp;
	int error;

	/* For debugging/testing */
	if (inst_sync_disable)
		return (0);

	/*
	 * We must have sufficient privilege to do this, since we lock critical
	 * data structures whilst we're doing it ..
	 */
	if ((error = secpolicy_sys_devices(CRED())) != 0)
		return (set_errno(error));

	if (flags != INST_SYNC_ALWAYS && flags != INST_SYNC_IF_REQUIRED)
		return (set_errno(EINVAL));

	/*
	 * Only one process is allowed to get the state of the instance
	 * number assignments on the system at any given time.
	 */
	e_ddi_enter_instance();

	/*
	 * Recreate the instance file only if the device tree has changed
	 * or if the caller explicitly requests so.
	 */
	if (e_ddi_instance_is_clean() && flags != INST_SYNC_ALWAYS) {
		error = EALREADY;
		goto end;
	}

	/*
	 * Create an instance file for writing, giving it a mode that
	 * will only permit reading.  Note that we refuse to overwrite
	 * an existing file.
	 */
	if ((error = vn_open(pathname, UIO_USERSPACE,
	    FCREAT, 0444, &vp, CRCREAT, 0)) != 0) {
		if (error == EISDIR)
			error = EACCES;	/* SVID compliance? */
		goto end;
	}

	/*
	 * So far so good.  We're singly threaded, the vnode is beckoning
	 * so let's get on with it.  Any error, and we just give up and
	 * hand the first error we get back to userland.
	 */
	error = in_write_instance(vp);

	/*
	 * If there was any sort of error, we deliberately go and
	 * remove the file we just created so that any attempts to
	 * use it will quickly fail.
	 */
	if (error)
		(void) vn_remove(pathname, UIO_USERSPACE, RMFILE);
	else
		e_ddi_instance_set_clean();
end:
	e_ddi_exit_instance();
	return (error ? set_errno(error) : 0);
}