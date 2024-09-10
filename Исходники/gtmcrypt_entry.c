uint4 gtmcrypt_entry()
{
	void_ptr_t		handle, fptr;
	char_ptr_t		err_str, env_ptr, libname_ptr, libpath_ptr;
	char			*gtmcryptlib_fname[] = {
					GTMCRYPT_INIT_FNAME,
					GTMCRYPT_CLOSE_FNAME,
					GTMCRYPT_HASH_GEN_FNAME,
					GTMCRYPT_ENCRYPT_FNAME,
					GTMCRYPT_DECRYPT_FNAME,
					GTMCRYPT_GETKEY_BY_NAME,
					GTMCRYPT_GETKEY_BY_HASH,
					GTMCRYPT_STRERROR
				};
	void			**gtmcryptlib_fptr[] = {
					(void **)&gtmcrypt_init_fnptr,
					(void **)&gtmcrypt_close_fnptr,
					(void **)&gtmcrypt_hash_gen_fnptr,
					(void **)&gtmcrypt_encrypt_fnptr,
					(void **)&gtmcrypt_decrypt_fnptr,
					(void **)&gtmcrypt_getkey_by_name_fnptr,
					(void **)&gtmcrypt_getkey_by_hash_fnptr,
					(void **)&gtmcrypt_strerror_fnptr
				};
	int			findx, num_dlsyms, plugin_dir_len, save_errno;
	char			libpath[GTM_PATH_MAX], buf[MAX_GTMCRYPT_PLUGIN_STR_LEN], plugin_dir_path[GTM_PATH_MAX];
	char			resolved_libpath[GTM_PATH_MAX], resolved_gtmdist[GTM_PATH_MAX];
	mstr			trans, env_var = {0, SIZEOF(GTM_CRYPT_PLUGIN) - 1, GTM_CRYPT_PLUGIN};

	if (NULL == (env_ptr = getenv(GTM_DIST)))
		rts_error(VARLSTCNT(1) ERR_GTMDISTUNDEF);
	if (NULL == realpath(env_ptr, &resolved_gtmdist[0]))
	{
		save_errno = errno;
		SNPRINTF(dl_err, MAX_ERRSTR_LEN, "Failed to find symbolic link for %s. %s", env_ptr, STRERROR(save_errno));
		return ERR_CRYPTDLNOOPEN;
	}
	SNPRINTF(plugin_dir_path, GTM_PATH_MAX, "%s/%s", resolved_gtmdist, PLUGIN_DIR_NAME);
	plugin_dir_len = STRLEN(plugin_dir_path);
	if ((SS_NORMAL != TRANS_LOG_NAME(&env_var, &trans, buf, SIZEOF(buf), do_sendmsg_on_log2long)) || (0 >= trans.len))
	{	/* Either $gtm_crypt_plugin is not defined in the environment variable OR it is set to null-string. Fall-back to
		 * using libgtmcrypt.so
		 */
		libname_ptr = GTMCRYPT_LIBNAME;
	} else
		libname_ptr = &buf[0];		/* value of $gtm_crypt_plugin */
	SNPRINTF(libpath, GTM_PATH_MAX, "%s/%s", plugin_dir_path, libname_ptr);
	if (NULL == realpath(&libpath[0], &resolved_libpath[0]))
	{
		save_errno = errno;
		SNPRINTF(dl_err, MAX_ERRSTR_LEN, "Failed to find symbolic link for %s. %s", libpath, STRERROR(save_errno));
		return ERR_CRYPTDLNOOPEN;
	}
	/* Symbolic link found. dlopen resolved_libpath */
	if (0 != memcmp(&resolved_libpath[0], plugin_dir_path, plugin_dir_len))
	{	/* resolved_path doesn't contain $gtm_dist/plugin as the prefix */
		SNPRINTF(dl_err, MAX_ERRSTR_LEN, "Symbolic link for %s must be relative to %s", libpath, plugin_dir_path);
		return ERR_CRYPTDLNOOPEN;
	}
	handle = dlopen(&resolved_libpath[0], GTMCRYPT_LIBFLAGS);
	if (NULL == handle)
	{
		COPY_DLLERR_MSG(err_str, dl_err);
		return ERR_CRYPTDLNOOPEN;
	}
	num_dlsyms = ARRAYSIZE(gtmcryptlib_fptr); /* number of functions to be dlsym'ed */
	for(findx = 0; findx < num_dlsyms; ++findx)
	{
		fptr = (void *)dlsym(handle, gtmcryptlib_fname[findx]);
		if (NULL == fptr)
		{
			COPY_DLLERR_MSG(err_str, dl_err);
			return ERR_CRYPTDLNOOPEN;
		}
		*gtmcryptlib_fptr[findx] = fptr;
	}
	return 0;
}