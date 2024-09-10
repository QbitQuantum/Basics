void dump1byte_test(int fpp, float *fbuf, int size)
{
#define MAXBUF (NCROSS*ONEGATE)
  int i;
  struct {float fmax; char obuf[FFTLEN/NNODE]} outbuf[size/(FFTLEN/NNODE)];
  static char obuf[FFTLEN/NNODE];
  float fmax,ftmp;
  int k=0;

  while (size>FFTLEN/NNODE-2) {
    fmax=0;
    for (i=0;i<FFTLEN/NNODE;i++) fmax=MAX(fmax,fabs(fbuf[i]));
    outbuf[k].fmax=fmax;
    for (i=0;i<FFTLEN/NNODE;i++) {
      ftmp=sqrt(fabs(fbuf[i]/fmax));
      ftmp=(fbuf[i]>0)?ftmp:-ftmp;
      outbuf[k].obuf[i]=lroundf(127*ftmp);
    }
    k++;
    fbuf+=FFTLEN/NNODE;
    size-=FFTLEN/NNODE;
  }
  if (write(fpp,outbuf,sizeof(outbuf))!=sizeof(outbuf)) perror("dump1byte:write");
}