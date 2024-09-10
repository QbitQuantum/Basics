static void handleCloseRequest(char *msgBuf)
{
    char user[USERNAME_LEN];
    char *ptr = msgBuf;
    pid_t pid;

    /* get ssh pid */
    getPid(&ptr, &pid);
    /* get pam username */
    getString(&ptr, user, sizeof(user));

    mdbg(PSPAM_LOG_DEBUG, "%s: got pam close of user: '******' pid: %i\n", __func__,
	 user, pid);
    rmSession(user, pid);
}