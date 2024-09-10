void ns_setpassword(User * u, NickCore * nc)
{
    int len = 0;
    char password[PASSCODELEN];

    if (nc->pass)
        free(nc->pass);

    nc->pass = smalloc(PASSMAX);

    /* we'll generate the password just like we
     * did for the passcode */
    generatePassCode(password);

    len = strlen(password);

#ifdef USE_ENCRYPTION
    if (encrypt(password, len, nc->pass, PASSMAX) < 0) {
        alog("%s: Failed to encrypt password for %s (set)", MYNAME,
             nc->display);
        notice_lang(s_NickServ, u, NICK_SET_PASSWORD_FAILED);
        return;
    }

    nc->flags |= NI_ENCRYPTEDPW;
#else
    strncpy(nc->pass, password, PASSMAX);
#endif

    if (do_sendpassword(u, nc, password) != 0)
    {
        alog(LOG_COULDNT_SENDMAIL, MYNAME, nc->display);
	return;
    }

    notice(s_NickServ, u->nick, "Your password has been changed successfully.  Your new password has been e-mailed to you.");

    alog("%s: Password reset for %s (e-mail: %s) by %s!%s@%s.", MYNAME,
         nc->display, nc->email, u->nick, u->username, u->host);

    return;
}