/* drops privileges */
int drop_privileges(char *user, char *group){
	uid_t uid=-1;
	gid_t gid=-1;
	struct group *grp;
	struct passwd *pw;

	/* set effective group ID */
	if(group!=NULL){
		
		/* see if this is a group name */
		if(strspn(group,"0123456789")<strlen(group)){
			grp=(struct group *)getgrnam(group);
			if(grp!=NULL)
				gid=(gid_t)(grp->gr_gid);
			else
				syslog(LOG_ERR,"Warning: Could not get group entry for '%s'",group);
			endgrent();
		        }

		/* else we were passed the GID */
		else
			gid=(gid_t)atoi(group);

		/* set effective group ID if other than current EGID */
		if(gid!=getegid()){

			if(setgid(gid)==-1)
				syslog(LOG_ERR,"Warning: Could not set effective GID=%d",(int)gid);
		        }
	        }


	/* set effective user ID */
	if(user!=NULL){
		
		/* see if this is a user name */
		if(strspn(user,"0123456789")<strlen(user)){
			pw=(struct passwd *)getpwnam(user);
			if(pw!=NULL)
				uid=(uid_t)(pw->pw_uid);
			else
				syslog(LOG_ERR,"Warning: Could not get passwd entry for '%s'",user);
			endpwent();
		        }

		/* else we were passed the UID */
		else
			uid=(uid_t)atoi(user);
			
		/* set effective user ID if other than current EUID */
		if(uid!=geteuid()){

#ifdef HAVE_INITGROUPS
			/* initialize supplementary groups */
			if(initgroups(user,gid)==-1){
				if(errno==EPERM)
					syslog(LOG_ERR,"Warning: Unable to change supplementary groups using initgroups()");
				else{
					syslog(LOG_ERR,"Warning: Possibly root user failed dropping privileges with initgroups()");
					return ERROR;
			                }
	                        }
#endif

			if(setuid(uid)==-1)
				syslog(LOG_ERR,"Warning: Could not set effective UID=%d",(int)uid);
		        }
	        }

	return OK;
        }