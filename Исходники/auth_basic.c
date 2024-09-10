static void
authenticateBasicDecodeAuth(auth_user_request_t * auth_user_request, const char *proxy_auth)
{
    char *sent_auth;
    char *cleartext;
    basic_data *basic_auth, local_basic;
    auth_user_t *auth_user;
    dlink_node *node;

    /* decode the username */
    /* trim BASIC from string */
    while (xisgraph(*proxy_auth))
	proxy_auth++;

    local_basic.passwd = NULL;

    /* Trim leading whitespace before decoding */
    while (xisspace(*proxy_auth))
	proxy_auth++;
    /* username and password */
    sent_auth = xstrdup(proxy_auth);
    /* Trim trailing \n before decoding */
    strtok(sent_auth, "\n");
    cleartext = uudecode(sent_auth);
    xfree(sent_auth);
    /*
     * Don't allow NL or CR in the credentials.
     * Oezguer Kesim <*****@*****.**>
     */
    debug(29, 9) ("authenticateBasicDecodeAuth: cleartext = '%s'\n", cleartext);
    if (strcspn(cleartext, "\r\n") != strlen(cleartext)) {
	debug(29, 1) ("authenticateBasicDecodeAuth: bad characters in authorization header '%s'\n",
	    proxy_auth);
	xfree(cleartext);
	return;
    }
    local_basic.username = cleartext;
    if ((cleartext = strchr(local_basic.username, ':')) != NULL)
	*(cleartext)++ = '\0';
    local_basic.passwd = cleartext;
    if (cleartext == NULL) {
	debug(29, 4) ("authenticateBasicDecodeAuth: no password in proxy authorization header '%s'\n",
	    proxy_auth);
	local_basic.passwd = NULL;
	auth_user_request->message = xstrdup("no password was present in the HTTP [proxy-]authorization header. This is most likely a browser bug");
    } else if (*cleartext == '\0' && !basicConfig->blankpassword) {
	debug(29, 4) ("authenticateBasicDecodeAuth: Disallowing empty password,"
	    "user is '%s'\n", local_basic.username);
	local_basic.passwd = NULL;
	auth_user_request->message = xstrdup("Request denied because you provided an empty password. Users MUST have a password.");
    }
    /* special case: we have to free the strings for user and password
     * if we are not returning a filled out structure 
     */
    if (local_basic.passwd == NULL) {
	if (local_basic.username) {
	    /* log the username */
	    debug(29, 9) ("authBasicDecodeAuth: Creating new user for logging '%s'\n", local_basic.username);
	    /* new auth_user */
	    auth_user = authenticateAuthUserNew("basic");
	    /* new scheme data */
	    basic_auth = authBasicDataNew();
	    /* save the credentials */
	    basic_auth->username = local_basic.username;
	    /* link the scheme data in */
	    auth_user->scheme_data = basic_auth;
	    /* set the auth_user type */
	    auth_user->auth_type = AUTH_BROKEN;
	    /* link the request to the user */
	    auth_user_request->auth_user = auth_user;
	    /* lock for the auth_user_request link */
	    authenticateAuthUserLock(auth_user);
	    node = dlinkNodeNew();
	    dlinkAdd(auth_user_request, node, &auth_user->requests);
	}
	return;
    } else {
	local_basic.passwd = xstrndup(cleartext, USER_IDENT_SZ);
    }

    if (!basicConfig->casesensitive)
	Tolower(local_basic.username);
    /* now lookup and see if we have a matching auth_user structure in memory. */

    if ((auth_user = authBasicAuthUserFindUsername(local_basic.username)) == NULL) {
	/* the user doesn't exist in the username cache yet */
	debug(29, 9) ("authBasicDecodeAuth: Creating new user '%s'\n", local_basic.username);
	/* new auth_user */
	auth_user = authenticateAuthUserNew("basic");
	/* new scheme data */
	basic_auth = authBasicDataNew();
	/* save the credentials */
	basic_auth->username = local_basic.username;
	basic_auth->passwd = local_basic.passwd;
	/* link the scheme data in */
	auth_user->scheme_data = basic_auth;
	/* set the auth_user type */
	auth_user->auth_type = AUTH_BASIC;
	/* current time for timeouts */
	auth_user->expiretime = current_time.tv_sec;

	/* this auth_user struct is the 'lucky one' to get added to the username cache */
	/* the requests after this link to the auth_user */
	/* store user in hash */
	authenticateUserNameCacheAdd(auth_user);
    } else {
	debug(29, 9) ("authBasicDecodeAuth: Found user '%s' in the user cache as '%p'\n", local_basic.username, auth_user);
	xfree(local_basic.username);
	basic_auth = auth_user->scheme_data;
	if (strcmp(local_basic.passwd, basic_auth->passwd)) {
	    debug(29, 4) ("authBasicDecodeAuth: new password found. Updating in user master record and resetting auth state to unchecked\n");
	    basic_auth->flags.credentials_ok = 0;
	    xfree(basic_auth->passwd);
	    basic_auth->passwd = local_basic.passwd;
	} else
	    xfree(local_basic.passwd);
	if (basic_auth->flags.credentials_ok == 3) {
	    debug(29, 4) ("authBasicDecodeAuth: last attempt to authenticate this user failed, resetting auth state to unchecked\n");
	    basic_auth->flags.credentials_ok = 0;
	}
    }
    /* link the request to the user */
    auth_user_request->auth_user = auth_user;
    /* lock for the auth_user_request link */
    authenticateAuthUserLock(auth_user);
    node = dlinkNodeNew();
    dlinkAdd(auth_user_request, node, &auth_user->requests);
    return;
}