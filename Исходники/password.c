void add_session_user(const char *user)
{
	fstring suser;
	struct passwd *passwd;

	if (!(passwd = Get_Pwnam(user)))
		return;

	fstrcpy(suser,passwd->pw_name);

	if(!*suser)
		return;

	if( session_userlist && in_list(suser,session_userlist,False) )
		return;

	if( !session_userlist || (strlen(suser) + strlen(session_userlist) + 2 >= len_session_userlist) ) {
		char *newlist;

		if (len_session_userlist > 128 * PSTRING_LEN) {
			DEBUG(3,("add_session_user: session userlist already too large.\n"));
			return;
		}
		newlist = Realloc( session_userlist, len_session_userlist + PSTRING_LEN );
		if( newlist == NULL ) {
			DEBUG(1,("Unable to resize session_userlist\n"));
			return;
		}
		if (!session_userlist) {
			*newlist = '\0';
		}
		session_userlist = newlist;
		len_session_userlist += PSTRING_LEN;
	}

	safe_strcat(session_userlist," ",len_session_userlist-1);
	safe_strcat(session_userlist,suser,len_session_userlist-1);
}