void MPIOpenFile(FILE **fileptr, char *name, char *namestr, char *mode,
    char *prog, char *name2)
  {
    char buffer[BSZ];
    char namewnode[BSZ];
    int i;
    char *j;
    int IAM;
    MPI_Comm_rank(MPI_COMM_WORLD, &IAM);
    sprintf(namewnode,"%s.%d",name,IAM);
    sprintf(name2,"%s.%d",name,IAM);
    openfile(fileptr,namewnode,namestr,mode,prog,name2);
  }