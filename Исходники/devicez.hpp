/* replacement of Unix rint() for Windows */
static int rint (double x)
{
char *buf;
int i,dec,sig;

buf = _fcvt(x, 0, &dec, &sig);
i = atoi(buf);
if(sig == 1) {
i = i * -1;
}
return(i);
}