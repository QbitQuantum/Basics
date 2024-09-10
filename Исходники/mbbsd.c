void u_exit(char *mode) {
    userec_t xuser;
    int diff = (time(0) - login_start_time) / 60;

    passwd_query(usernum, &xuser);
    
    auto_backup();
    
    setflags(PAGER_FLAG, currutmp->pager != 1);
    setflags(CLOAK_FLAG, currutmp->invisible);
    
    xuser.invisible = currutmp->invisible % 2;
    xuser.pager = currutmp->pager % 5;
    
    if(!(HAS_PERM(PERM_SYSOP) && HAS_PERM(PERM_DENYPOST)))
	do_aloha("<<下站通知>> -- 我走囉！");
    
    purge_utmp(currutmp);
    if((cuser.uflag != enter_uflag) || (currmode & MODE_DIRTY) || !diff) {
	xuser.uflag = cuser.uflag;
	xuser.numposts = cuser.numposts;
	if(!diff && cuser.numlogins)
	    xuser.numlogins = --cuser.numlogins; /* Leeym 上站停留時間限制式 */
	reload_money();
	passwd_update(usernum, &xuser);
    }
    log_usies(mode, NULL);
}