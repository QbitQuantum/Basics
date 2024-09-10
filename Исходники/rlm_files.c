/*
 *	(Re-)read the "users" file into memory.
 */
static int mod_instantiate(UNUSED CONF_SECTION *conf, void *instance)
{
	rlm_files_t *inst = instance;

#undef READFILE
#define READFILE(_x, _y) do { if (getusersfile(inst, inst->_x, &inst->_y, inst->compat_mode) != 0) { ERROR("Failed reading %s", inst->_x); mod_detach(inst);return -1;} } while (0)

	READFILE(filename, common);
	READFILE(usersfile, users);
	READFILE(acctusersfile, acctusers);

#ifdef WITH_PROXY
	READFILE(preproxy_usersfile, preproxy_users);
	READFILE(postproxy_usersfile, postproxy_users);
#endif

	READFILE(auth_usersfile, auth_users);
	READFILE(postauth_usersfile, postauth_users);

	return 0;
}