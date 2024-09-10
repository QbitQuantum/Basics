void ListSysEnhanced(FILE *fpout,
                     const T_hklCond *cnd, const int *SysEnhanced, int cndn)
{
  int   i,j,n,m;
  char  hkl[3]="hkl";
  int   x[3];
  int   S[3][3];
  char  buf[128];


  Fprintf(fpout, "Systematically enhanced reflections\n");

  for(m=0;m<cndn;m++,cnd++) {
    if(SysEnhanced[m]==0) continue;
    (void) memcpy(S,cnd->Mx,sizeof(S));
    (void) memcpy(x,cnd->Gl,sizeof(x));

    buf[0] = 0;
    for(j=0; j<3; j++){
      for(n=i=0; i<3; i++) if((n=S[i][j]) != 0) break;
      if(i==3)
        Sprintf(&buf[strlen(buf)],"0");
      else {
        if (n==1) Sprintf(&buf[strlen(buf)],"%1c",hkl[i]);
        else if (n==-1) Sprintf(&buf[strlen(buf)],"-%1c",hkl[i]);
        else Sprintf(&buf[strlen(buf)],"%d%1c",n,hkl[i]);
      }
    }

    Sprintf(&buf[strlen(buf)],": e=%d",SysEnhanced[m]);

    Fprintf(fpout, "  %s\n", buf);
  }

  putc('\n', fpout);
}