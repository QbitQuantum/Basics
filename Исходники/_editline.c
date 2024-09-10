/* ARGSUSED */
static void
onintr(int sig)
{
    longjmp(jbuf, 1);
}