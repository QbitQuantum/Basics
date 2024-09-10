static int retrieve_backup(userec_t *user)
{
    int     uid;
    char    src[PATHLEN], dst[PATHLEN];
    char    ans;

    if ((uid = searchuser(user->userid, user->userid))) {
	userec_t orig;
	passwd_sync_query(uid, &orig);
	strlcpy(user->passwd, orig.passwd, sizeof(orig.passwd));
	setumoney(uid, user->money);
	passwd_sync_update(uid, user);
	return 0;
    }

    ans = vans("目前的 PASSWD 檔沒有此 ID，新增嗎？[y/N]");

    if (ans != 'y') {
	vmsg("目前的 PASSWDS 檔沒有此 ID，請先新增此帳號");
	return -1;
    }

    if (setupnewuser((const userec_t *)user) >= 0) {
	sethomepath(dst, user->userid);
	if (!dashd(dst)) {
	    snprintf(src, sizeof(src), "tmp/%s", user->userid);
	    if (!dashd(src) || !Rename(src, dst))
		mkuserdir(user->userid);
	}
	return 0;
    }
    return -1;
}