shell(void)
{
        char *shell;            /* Name of system command processor */


        /*  get name of system shell  */
        if ((shell = getenv("COMSPEC")) == NULL) {
                return(FALSE);          /*  No shell located  */
        }

        return (_spawnlp(_P_WAIT, shell, shell, NULL));
}