MFModifiedPolytope MFReadPolytopeFromPlotfile(FILE *fid, int k, int dimV, MFErrorHandler e)
 {
  static char RoutineName[]={"MFReadPolytopeFromPlotfile"};
  MFModifiedPolytope P;
  int mV,iV,iV0;
  double *v;
  int *vt;
  int mE,iE;
  int *ev;
  int *et;
  int mF,iF;
  int *nfv;
  int **fv;
  int *ft;
  int i,j,l,n;
  int ipoly,nv,ne,nf;
  int verbose=0;
  int iv,ie,iE0,je,np,v0,v1;
  int trip;
  int sing,bnd;
  char c;
  double R;

  if(verbose){printf("     Read Polytope\n");fflush(stdout);}
  P=(MFModifiedPolytope)malloc(sizeof(struct MFModifiedPolytopeSt));
  P->k=k;
  P->dimV=dimV;

  fscanf(fid,"Polyhedron %d, ",&ipoly);
  if(verbose){printf("          Polytope %d\n",ipoly);fflush(stdout);}
  c=fgetc(fid);
  ungetc(c,fid);
  if(c=='R')
   {
    fscanf(fid,"R=%lf, %d vertices, %d edges, %d faces,  boundary %d, singular %d\n",&R,&nv,&ne,&nf,&bnd,&sing);
   }else{
    fscanf(fid,"%d vertices, %d edges, %d faces,  boundary %d, singular %d\n",&nv,&ne,&nf,&bnd,&sing);
    R=0;
   }
  fscanf(fid,"  %d vertices, %d edges, %d faces,  boundary %d, singular %d\n",nv,ne,nf,bnd,sing);

  P->n=nv;
  P->m=nv;
  P->v=(double*)malloc(P->n*dimV*sizeof(double));
  P->nIndices=(int*)malloc(P->n*sizeof(int));
  P->mIndices=(int*)malloc(P->n*sizeof(int));
  P->indices=(int**)malloc(P->n*sizeof(int*));
  P->mark=(int*)malloc(P->n*sizeof(int));
  for(i=0;i<P->n;i++)
   {
    P->nIndices[i]=0;
    P->mIndices[i]=0;
    P->indices[i]=(int*)NULL;
    P->mark[i]=0;
   }

  if(verbose){printf("Polyhedron %d, %d vertices, %d edges, %d faces\n",ipoly,nv,ne,nf);fflush(stdout);}

  for(iv=0;iv<nv;iv++)
   {
    fscanf(fid,"Vertex %d (%lf",&iV,&(P->v[0+P->dimV*iv]));
    if(verbose){printf("Vertex %d (%lf",iV,(P->v[0+P->dimV*iv]));fflush(stdout);}
    for(i=1;i<dimV;i++){fscanf(fid,",%lf",&(P->v[i+P->dimV*iv]));if(verbose){printf(",%lf",(P->v[i+P->dimV*iv]));fflush(stdout);}}
    fscanf(fid,"), %d ",&(P->nIndices[iv]));
    if(verbose){printf("), %d ",(P->nIndices[iv]));fflush(stdout);}
    P->mIndices[iv]=P->nIndices[iv];
    if(P->nIndices[iv]!=0)
     {
      P->indices[iv]=(int*)malloc((P->nIndices[i])*sizeof(int));

      fscanf(fid,"[%d",&(P->indices[iv][0]));
      if(verbose){printf(    "[%d", (P->indices[iv][0]));fflush(stdout);}

      for(i=1;i<P->nIndices[iv];i++)
       {
        fscanf(fid,",%d",&(P->indices[iv][i]));
        if(verbose){printf(    ",%d", (P->indices[iv][i]));fflush(stdout);}
       }

      fscanf(fid,"]\n");
      if(verbose){printf(    "]\n");fflush(stdout);}
     }else{
      fscanf(fid," [ ]\n");
      if(verbose){printf(    "\n");fflush(stdout);}
     }

    if(verbose)
     {
      printf("  Vertex %d (%lf",iv,P->v[0+P->dimV*iV]);
      for(i=1;i<P->dimV;i++)printf(",%lf",P->v[i+P->dimV*iV]);
      printf(")\n");fflush(stdout);
     }
   }


  for(ie=0;ie<ne;ie++)
   {
    if(k>1)
     {
      fscanf(fid,"Edge %d (%d,%d), %*d [%*[ 0-9+-.,]]\n",&iE,&v0,&v1);
      if(verbose){printf(    "Edge %d (%d,%d)\n",iE,v0,v1);fflush(stdout);}
     }else if(k==1)
     {
      fscanf(fid,"Edge %d (%d,%d), %*d []\n",&iE,&v0,&v1);
      if(verbose){printf(    "Edge %d (%d,%d)\n",iE,v0,v1);fflush(stdout);}
     }else{
      fscanf(fid,"Edge %d (%d,%d), %*d [%*[ 0-9+-.,]]\n",&iE,&v0,&v1);
      if(verbose){printf(    "Edge %d (%d,%d)\n",iE,v0,v1);fflush(stdout);}
     }
    if(verbose){printf("  Edge %d (%d,%d)\n",ie,v0,v1);fflush(stdout);}
   }

  P->nFaces=nf;
  P->mFaces=nf;
  P->face  =(int*)malloc(P->mFaces*sizeof(int));
  P->nFaceV=(int*)malloc(P->mFaces*sizeof(int));
  P->faceN =(MFNVector*)malloc(P->mFaces*sizeof(MFNVector));
  P->faceO =(double*)malloc(P->mFaces*sizeof(double));

  for(i=0;i<nf;i++)
   {
    fscanf(fid,"Face %d neighbor %*d\n",&(P->face[i]));
    if(verbose){printf(    "Face %d neighbor\n",(P->face[i]));fflush(stdout);}
    P->nFaceV[i]=0;
    P->faceN [i]=(MFNVector)NULL;
    P->faceO [i]=0.;
   }
  if(verbose){printf("done\n");fflush(stdout);}

  return P;
 }