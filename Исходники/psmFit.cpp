//
// gateway driver to call the distance transform code from matlab
//
// This is the matlab entry point
void 
mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  int i, j, k, c, nrow, ncol, maxdim, nmpt;
  int mxfn, myfn, mrfn, mvxfn, mvyfn, mpfn, mchfn;
  int root, curt, ch, prnt, dtarrbase, dtarrlim;
  int ldim[3], *v, *mp, *mnch, *mdone, *mndesc, *dtarrhist;
  int *loc, *loc2, *lscratch, **locarr, **locarr2;
  char *pbimgc;
  double x_multiply, y_multiply, yx_ratio, maxd, *z;
  double *cost, *out, *scratch, *scratch2, *scl;
  double *mx, *my, *mr, *mvx, *mvy, *pbimg, *dt1, *tranarr;
  double **mch, **locp, **dtarr, **dtarrp;
  mxArray *cell, *field;

  // check for proper number and size of arguments
  errCheck(nrhs >= 2,"Arguments:  model, bimg, [maxd]");
  errCheck(nrhs <= 3,"Arguments:  model, bimg, [maxd]");
  errCheck(nlhs <= 3,"Outputs:  dt, [loc], [scale]");
  errCheck(mxIsStruct(prhs[0]),"model must be struct.");
  mxfn = mxGetFieldNumber(prhs[0],"x");
  errCheck(mxfn>=0,"Model must have field named x.");
  myfn = mxGetFieldNumber(prhs[0],"y");
  errCheck(myfn>=0,"Model must have field named y.");
  mrfn = mxGetFieldNumber(prhs[0],"r");
  errCheck(mrfn>=0,"Model must have field named r.");
  mvxfn = mxGetFieldNumber(prhs[0],"vx");
  errCheck(mvxfn>=0,"Model must have field named vx.");
  mvyfn = mxGetFieldNumber(prhs[0],"vy");
  errCheck(mvyfn>=0,"Model must have field named vy.");
  mpfn = mxGetFieldNumber(prhs[0],"parent");
  errCheck(mpfn>=0,"Model must have field named parent.");
  mchfn = mxGetFieldNumber(prhs[0],"children");
  errCheck(mchfn>=0,"Model must have field named children.");
  errCheck(mxIsDouble(prhs[1])||mxIsLogical(prhs[1])||mxIsUint8(prhs[1]),
           "Second argument must be binary image type.");
  errCheck(mxGetNumberOfDimensions(prhs[1])==2,
           "Second argument must be binary image type.");
  if (nrhs>2) {
    errCheck(mxIsDouble(prhs[2])&&!mxIsComplex(prhs[2]),
             "maxd must be real double.");
    errCheck(mxGetNumberOfElements(prhs[2])==1,
             "maxd must be scalar.");
    maxd = *mxGetPr(prhs[2]);
  } else {
    maxd = LARGE;
  }
  nmpt = (int)mxGetNumberOfElements(prhs[0]);
  nrow = (int)mxGetM(prhs[1]);
  ncol = (int)mxGetN(prhs[1]);

  // transcribe model variables
  root = -1;
  mx = (double*)mxMalloc(nmpt*sizeof(double));
  my = (double*)mxMalloc(nmpt*sizeof(double));
  mr = (double*)mxMalloc(nmpt*sizeof(double));
  mvx = (double*)mxMalloc(nmpt*sizeof(double));
  mvy = (double*)mxMalloc(nmpt*sizeof(double));
  mp = (int*)mxMalloc(nmpt*sizeof(int));
  mch = (double**)mxMalloc(nmpt*sizeof(double*));
  mnch = (int*)mxMalloc(nmpt*sizeof(int));
  for (int i = 0; i < nmpt; i++) {
    mx[i] = *mxGetPr(mxGetFieldByNumber(prhs[0],i,mxfn));
    errCheck(ABS(ROUND(mx[i])) < ncol,"Model displacement larger than image.");
    my[i] = *mxGetPr(mxGetFieldByNumber(prhs[0],i,myfn));
    errCheck(ABS(ROUND(my[i])) < nrow,"Model displacement larger than image.");
    mr[i] = *mxGetPr(mxGetFieldByNumber(prhs[0],i,mrfn));
    mvx[i] = *mxGetPr(mxGetFieldByNumber(prhs[0],i,mvxfn));
    mvy[i] = *mxGetPr(mxGetFieldByNumber(prhs[0],i,mvyfn));
    mp[i] = (int)(*mxGetPr(mxGetFieldByNumber(prhs[0],i,mpfn)));
    field = mxGetFieldByNumber(prhs[0],i,mchfn);
    mch[i] = mxGetPr(field);
    mnch[i] = (int)(mxGetNumberOfElements(field));
    if (mp[i]==0) {
      errCheck(root<0,"Model must have a single root.");
      root = i;
    }
  }
  errCheck(root>=0,"Model must have a root.");

  // allocate output space
  plhs[0] = mxCreateDoubleMatrix(nrow, ncol, mxREAL);
  out = mxGetPr(plhs[0]);
  if (nlhs>=2) {
    locp = (double**)mxMalloc(nrow*ncol*sizeof(double*));
    plhs[1] = mxCreateCellMatrix(nrow,ncol);
    for (i = 0; i < nrow*ncol; i++) {
      cell = mxCreateDoubleMatrix(2,nmpt,mxREAL);
      mxSetCell(plhs[1],i,cell);
      locp[i] = mxGetPr(cell);
    }
    loc = (int*)mxMalloc(2*nrow*ncol*sizeof(int));
    loc2 = loc+nrow*ncol;
    if (nlhs>=3) {
      plhs[2] = mxCreateDoubleMatrix(nrow,ncol,mxREAL);
      scl = mxGetPr(plhs[2]);
    }
  } else {
    loc = 0;
    loc2 = 0;
    locp = 0;
  }

  // transcribe image
  pbimg = mxGetPr(prhs[1]);
  pbimgc = (char*)pbimg;
  dt1 = out;  // this is where the answer will end up, eventually
  if (mxIsDouble(prhs[1])) {
    for (int i = 0; i <nrow*ncol; i++) {
      if (pbimg[i]) {
        dt1[i] = 0;
      } else {
        dt1[i] = maxd;
      }
    }
  } else {
    for (int i = 0; i <nrow*ncol; i++) {
      if (pbimgc[i]) {
        dt1[i] = 0;
      } else {
        dt1[i] = maxd;
      }
    }
  }

  // allocate scratch space for distance transform
  maxdim = MAX(nrow,ncol);
  scratch = (double*)mxMalloc(maxdim*sizeof(double));
  scratch2 = (double*)mxMalloc(nrow*ncol*sizeof(double));
  if (loc) {
    lscratch = (int*)mxMalloc(nrow*ncol*sizeof(int));
  } else {
    lscratch = 0;
  }
  v = (int*)mxMalloc(maxdim*sizeof(int));
  z = (double*)mxMalloc((maxdim+1)*sizeof(double));

  // allocate other variables
  mdone = (int*)mxMalloc(nmpt*sizeof(int));
  mndesc = (int*)mxMalloc(nmpt*sizeof(int));
  tranarr = (double*)mxMalloc(nrow*ncol*sizeof(double));  // stores translation
  dtarr = (double**)mxMalloc(nmpt*sizeof(double*));  // stores intermediate dt
  dtarrp = (double**)mxMalloc(nmpt*sizeof(double*));  // pointer to storage
  dtarrhist = (int*)mxMalloc(nmpt*sizeof(int));  // stores historical size
  locarr = (int**)mxMalloc(2*nmpt*sizeof(int*));  // stores intermediate loc
  locarr2 = locarr+nmpt;
  for (i = 0; i < nmpt; i++) {
    mdone[i] = 0;
    mndesc[i] = 1;
    dtarrp[i] = 0;
  }
  if (loc) {
    for (i = 0; i < nmpt; i++) {
      locarr[i] = (int*)mxMalloc(2*nrow*ncol*sizeof(int));
      locarr2[i] = locarr[i]+nrow*ncol;
    }
  } else {
    for (i = 0; i < nmpt; i++) {
      locarr[i] = 0;
      locarr2[i] = 0;
    }
  }

  // compute distance transform on input image
  gdt2d(dt1,dt1,0,v,z,nrow,ncol,1,1,scratch,scratch2,lscratch);

  // run computation
  curt = root;
  dtarrlim = 0;
  dtarrbase = 0;
  dtarrp[root] = dt1;
  k = 0;
  while (curt != -1) {

    // set base point
    if (mdone[curt]==0) {
      dtarrhist[curt] = dtarrbase;
    }

    // figure out if we need to descend to children
    if (mdone[curt]<mnch[curt]) {
      // figure out current child
      ch = (int)(mch[curt][mdone[curt]])-1;  // Matlab indices start from 1
     
      // we haven't yet computed the current child; set up to do that now
      ch = (int)(mch[curt][mdone[curt]])-1;  // Matlab indices start from 1
      
      // allocate new dt storage space if necessary
      if (dtarrlim==dtarrbase) {
        dtarr[dtarrlim] = (double*)mxMalloc(nrow*ncol*sizeof(double));
        dtarrlim++;
      }
      
      // copy dt1
      for (i = 0; i < nrow*ncol; i++) {
        dtarr[dtarrbase][i] = dt1[i];
      }
           
      // set up storage for this child
      dtarrp[ch] = dtarr[dtarrbase];
      dtarrbase++;
      
      // move on, but when we return, remember that this child is done
      mdone[curt]++;
      curt = ch;
    } else {
      // all children complete; assemble result
      for (c = 0; c < mnch[curt]; c++) {
        ch = (int)(mch[curt][c])-1;  // Matlab indices start from 1
        errCheck(dtarrp[ch]!=0,"Null pointer");
        mxAssert((ch>=0)&&(ch<nmpt),"Out of bounds");
        tranDT(dtarrp[ch],tranarr,nrow,ncol,mx[ch],my[ch],maxd*mndesc[ch]);
        gdt2d(tranarr,dtarrp[ch],locarr[ch],v,z,nrow,ncol,mvx[ch],mvy[ch],
               scratch,scratch2,lscratch);
        for (i = 0; i < nrow*ncol; i++) {
          dtarrp[curt][i] += dtarrp[ch][i];
        }
      }

      // now go back up to the parent
      if (mp[curt]>0) {
        mxAssert((curt>=0)&&(curt<nmpt),"Out of bounds");
        mxAssert((mp[curt]-1>=0)&&(mp[curt]-1<nmpt),"Out of bounds");
        mndesc[mp[curt]-1] += mndesc[curt];
      }
      dtarrbase = dtarrhist[curt];
      curt = mp[curt]-1;  // Matlab indices start from 1
    }
  }

  // do final translation and distance transform
  tranDT(dt1,tranarr,nrow,ncol,mx[root],my[root],maxd*nmpt);
  gdt2d(tranarr,dt1,locarr[root],v,z,nrow,ncol,mvx[root],mvy[root],
         scratch,scratch2,lscratch);

  // assemble loc information if required
  prnt = -1;
  if (loc) {
    for (i = 0; i < nmpt; i++) {
      mdone[i] = 0;
    }
    curt = root;

    while (curt != -1) {
      // first time through:
      if (mdone[curt] == 0) {
        int y = ROUND(my[curt]);
        int x = ROUND(mx[curt]);
        // copy results for this node
        for (i = 0; i < nrow; i++) {
          for (j = 0; j < ncol; j++) {
            if (prnt == -1) {
              locp[i+j*nrow][2*curt] = BOUND(j+x,0,ncol-1);
              locp[i+j*nrow][2*curt+1] = BOUND(i+y,0,nrow-1);
            } else {
              int jj = (int)BOUND(locp[i+j*nrow][2*prnt],0,ncol-1);
              int ii = (int)BOUND(locp[i+j*nrow][2*prnt+1],0,nrow-1);
              locp[i+j*nrow][2*curt] = locarr[curt][ii+nrow*jj]+x;
              locp[i+j*nrow][2*curt+1] = locarr2[curt][ii+nrow*jj]+y;
            }
          }
        }
      }

      // descend to children if any left
      if (mdone[curt]<mnch[curt]) {
        // descend to child
        prnt = curt;
        ch = (int)(mch[curt][mdone[curt]])-1;  // Matlab indices start from 1
        mdone[curt]++;
        curt = ch;
      } else {
        // come back up
        curt = prnt;  // Matlab indices start from 1
        prnt = mp[curt]-1;
      }
    }

    // add +1 to all indices for Matlab
    for (i = 0; i < nrow*ncol; i++) {
      for (j = 0; j < 2*nmpt; j++) {
        locp[i][j]++;
      }
    }
  }

  // compute scale if needed
  if (nlhs>=3) {
    for (i = 0; i < nrow*ncol; i++) {
      double tmp = 0;
      
      for (j = 0; j < nmpt; j++) {
        if (mp[j]>0) {
          tmp += sqrt(SQR(locp[i][2*j]-locp[i][2*mp[j]-2])+
                      SQR(locp[i][2*j+1]-locp[i][2*mp[j]-1]));
        }
      }
      scl[i] = tmp;
    }
  }

  // free stuff
  for (i = 0; i < dtarrlim; i++) {
    mxFree(dtarr[i]);
  }
  if (loc) {
    for (i = 0; i < nmpt; i++) {
      mxFree(locarr[i]);
    }
  }
  mxFree(locarr);
  mxFree(dtarrhist);
  mxFree(dtarrp);
  mxFree(dtarr);
  mxFree(mndesc);
  mxFree(mdone);
  mxFree(z);
  mxFree(v);
  if (locp) {
    mxFree(lscratch);
  }
  mxFree(scratch2);
  mxFree(scratch);
  if (nlhs==2) {
    mxFree(loc);
    mxFree(locp);
  }
  mxFree(mnch);
  mxFree(mch);
  mxFree(mp);
  mxFree(mvy);
  mxFree(mvx);
  mxFree(mr);
  mxFree(my);
  mxFree(mx);
}