int main(){
  int i,j,k;
  float t;
  FILE *file1,*file2,*file3,*file4,*file5;
  FILE *file[15];
  file1=fopen("l5_ipx.dat","w");
  file3=fopen("l5in.dat","w");
  file4=fopen("l5out1.dat","w");
  file5=fopen("l5out2.dat","w");
  for(i=0;i<N*range;i++){
    K[i]=(1-al)*pow(-al,i);
    fprintf(file1,"%d %e\n",i,K[i]);}
  calcx(file3,fs,1);
  calcy(file4,file5);
  fcloseall();
  file2=fopen("l5_achx.dat","w");
  file[0]=fopen("l5_32i.dat","w");
  file[3]=fopen("l5_16i.dat","w");
  file[6]=fopen("l5_8i.dat","w");
  file[9]=fopen("l5_4i.dat","w");
  file[12]=fopen("l5_2i.dat","w");
  file[1]=fopen("l5_32o1.dat","w");
  file[4]=fopen("l5_16o1.dat","w");
  file[7]=fopen("l5_8o1.dat","w");
  file[10]=fopen("l5_4o1.dat","w");
  file[13]=fopen("l5_2o1.dat","w");
  file[2]=fopen("l5_32o2.dat","w");
  file[5]=fopen("l5_16o2.dat","w");
  file[8]=fopen("l5_8o2.dat","w");
  file[11]=fopen("l5_4o2.dat","w");
  file[14]=fopen("l5_2o2.dat","w");
  for(j=0;j<5;j++){
    H[j]=Hf(fa);
    fprintf(file2,"%e %e\n",fa,H[j]);
    calcx(file[j*3],fa,0);
    calcy(file[j*3+1],file[j*3+2]);
    fa*=2;}
  fcloseall();
  return(0);
}