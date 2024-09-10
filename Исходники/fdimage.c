static void ctrlc(int sig)
{
    signal(sig, SIG_IGN);
    longjmp(jmpbuf, 1);
}