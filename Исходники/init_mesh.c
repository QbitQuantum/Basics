void init_mesh(MeshS *pM)
{
  int nblock,num_domains,nd,nl,level,maxlevel=0,nd_this_level;
  int nDim,nDim_test,dim;
  int *next_domainid;
  char block[80];
  int ncd,ir,irefine,l,m,n,roffset;
  int i,Nx[3],izones;
  div_t xdiv[3];  /* divisor with quot and rem members */
  Real root_xmin[3], root_xmax[3];  /* min/max of x in each dir on root grid */
  int Nproc_Comm_world=1,nproc=0,next_procID;
  SideS D1,D2;
  DomainS *pD, *pCD;
#ifdef MPI_PARALLEL
  int ierr,child_found,groupn,Nranks,Nranks0,max_rank,irank,*ranks;
  MPI_Group world_group;

/* Get total # of processes, in MPI_COMM_WORLD */
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &Nproc_Comm_world);
#endif

/* Start by initializing some quantaties in Mesh structure */

  pM->time = 0.0;
  pM->nstep = 0;
  pM->outfilename = par_gets("job","problem_id");

/*--- Step 1: Figure out how many levels and domains there are. --------------*/
/* read levels of each domain block in input file and calculate max level */

  num_domains = par_geti("job","num_domains");
#ifndef STATIC_MESH_REFINEMENT
  if (num_domains > 1) 
    ath_error("[init_mesh]: num_domains=%d; for num_domains > 1 configure with --enable-smr\n",num_domains);
#endif

  for (nblock=1; nblock<=num_domains; nblock++){
    sprintf(block,"domain%d",nblock);
    if (par_exist(block,"level") == 0)
      ath_error("[init_mesh]: level does not exist in block %s\n",block);
    level = par_geti(block,"level");
    maxlevel = MAX(maxlevel,level);
  }

/* set number of levels in Mesh, and allocate DomainsPerLevel array */

  pM->NLevels = maxlevel + 1;  /* level counting starts at 0 */

  pM->DomainsPerLevel = (int*)calloc_1d_array(pM->NLevels,sizeof(int));
  if (pM->DomainsPerLevel == NULL)
    ath_error("[init_mesh]: malloc returned a NULL pointer\n");

/* Now figure out how many domains there are at each level */

  for (nl=0; nl<=maxlevel; nl++){
    nd_this_level=0;
    for (nblock=1; nblock<=num_domains; nblock++){
      sprintf(block,"domain%d",nblock);
      if (par_geti(block,"level") == nl) nd_this_level++; 
    }

/* Error if there are any levels with no domains.  Else set DomainsPerLevel */

    if (nd_this_level == 0) {
      ath_error("[init_mesh]: Level %d has zero domains\n",nl);
    } else {
      pM->DomainsPerLevel[nl] = nd_this_level;
    }
  }

/*--- Step 2: Set up root level.  --------------------------------------------*/
/* Find the <domain> block in the input file corresponding to the root level,
 * and set root level properties in Mesh structure  */

  if (pM->DomainsPerLevel[0] != 1)
    ath_error("[init_mesh]: Level 0 has %d domains\n",pM->DomainsPerLevel[0]);

  for (nblock=1; nblock<=num_domains; nblock++){
    sprintf(block,"domain%d",nblock);
    level = par_geti(block,"level");
    if (level == 0){
      root_xmin[0] = par_getd(block,"x1min");
      root_xmax[0] = par_getd(block,"x1max");
      root_xmin[1] = par_getd(block,"x2min");
      root_xmax[1] = par_getd(block,"x2max");
      root_xmin[2] = par_getd(block,"x3min");
      root_xmax[2] = par_getd(block,"x3max");
      Nx[0] = par_geti(block,"Nx1");
      Nx[1] = par_geti(block,"Nx2");
      Nx[2] = par_geti(block,"Nx3");

/* number of dimensions of root level, to test against all other inputs */
      nDim=0;
      for (i=0; i<3; i++) if (Nx[i]>1) nDim++;
      if (nDim==0) ath_error("[init_mesh] None of Nx1,Nx2,Nx3 > 1\n");

/* some error tests of root grid */

      for (i=0; i<3; i++) {
        if (Nx[i] < 1) {
          ath_error("[init_mesh]: Nx%d in %s must be >= 1\n",(i+1),block);
        }
        if(root_xmax[i] < root_xmin[i]) {
          ath_error("[init_mesh]: x%dmax < x%dmin in %s\n",(i+1),block);
        }
      }
      if (nDim==1 && Nx[0]==1) {
        ath_error("[init_mesh]:1D requires Nx1>1: in %s Nx1=1,Nx2=%d,Nx3=%d\n",
        block,Nx[1],Nx[2]);
      }
      if (nDim==2 && Nx[2]>1) {ath_error(
        "[init_mesh]:2D requires Nx1,Nx2>1: in %s Nx1=%d,Nx2=%d,Nx3=%d\n",
        block,Nx[0],Nx[1],Nx[2]);
      }

/* Now that everything is OK, set root grid properties in Mesh structure  */

      for (i=0; i<3; i++) {
        pM->Nx[i] = Nx[i];
        pM->RootMinX[i] = root_xmin[i];
        pM->RootMaxX[i] = root_xmax[i];
        pM->dx[i] = (root_xmax[i] - root_xmin[i])/(Real)(Nx[i]);
      }

/* Set BC flags on root domain */

      pM->BCFlag_ix1 = par_geti_def(block,"bc_ix1",0);
      pM->BCFlag_ix2 = par_geti_def(block,"bc_ix2",0);
      pM->BCFlag_ix3 = par_geti_def(block,"bc_ix3",0);
      pM->BCFlag_ox1 = par_geti_def(block,"bc_ox1",0);
      pM->BCFlag_ox2 = par_geti_def(block,"bc_ox2",0);
      pM->BCFlag_ox3 = par_geti_def(block,"bc_ox3",0);
    }
  }

/*--- Step 3: Allocate and initialize domain array. --------------------------*/
/* Allocate memory and set pointers for Domain array in Mesh.  Since the
 * number of domains nd depends on the level nl, this is a strange array
 * because it is not [nl]x[nd].  Rather it is nl pointers to nd[nl] Domains.
 * Compare to the calloc_2d_array() function in ath_array.c
 */
      
  if((pM->Domain = (DomainS**)calloc((maxlevel+1),sizeof(DomainS*))) == NULL){
    ath_error("[init_mesh] failed to allocate memory for %d Domain pointers\n",
     (maxlevel+1));
  }

  if((pM->Domain[0]=(DomainS*)calloc(num_domains,sizeof(DomainS))) == NULL){
    ath_error("[init_mesh] failed to allocate memory for Domains\n");
  }

  for(nl=1; nl<=maxlevel; nl++)
    pM->Domain[nl] = (DomainS*)((unsigned char *)pM->Domain[nl-1] +
      pM->DomainsPerLevel[nl-1]*sizeof(DomainS));

/* Loop over every <domain> block in the input file, and initialize each Domain
 * in the mesh hierarchy (the Domain array), including the root level Domain  */

  next_domainid = (int*)calloc_1d_array(pM->NLevels,sizeof(int));
  for(nl=0; nl<=maxlevel; nl++) next_domainid[nl] = 0;

  for (nblock=1; nblock<=num_domains; nblock++){
    sprintf(block,"domain%d",nblock);

/* choose nd coordinate in Domain array for this <domain> block according
 * to the order it appears in input */

    nl = par_geti(block,"level");
    if (next_domainid[nl] > (pM->DomainsPerLevel[nl])-1)
      ath_error("[init_mesh]: Exceeded available domain ids on level %d\n",nl);
    nd = next_domainid[nl];
    next_domainid[nl]++;
    irefine = 1;
    for (ir=1;ir<=nl;ir++) irefine *= 2;   /* C pow fn only takes doubles !! */

/* Initialize level, number, input <domain> block number, and total number of
 * cells in this Domain */

    pM->Domain[nl][nd].Level = nl;
    pM->Domain[nl][nd].DomNumber = nd;
    pM->Domain[nl][nd].InputBlock = nblock;

    pM->Domain[nl][nd].Nx[0] = par_geti(block,"Nx1");
    pM->Domain[nl][nd].Nx[1] = par_geti(block,"Nx2");
    pM->Domain[nl][nd].Nx[2] = par_geti(block,"Nx3");

/* error tests: dimensions of domain */

    nDim_test=0;
    for (i=0; i<3; i++) if (pM->Domain[nl][nd].Nx[i]>1) nDim_test++;
    if (nDim_test != nDim) {
      ath_error("[init_mesh]: in %s grid is %dD, but in root level it is %dD\n",
      block,nDim_test,nDim);
    }
    for (i=0; i<3; i++) {
      if (pM->Domain[nl][nd].Nx[i] < 1) {
        ath_error("[init_mesh]: %s/Nx%d = %d must be >= 1\n",
          block,(i+1),pM->Domain[nl][nd].Nx[i]);
      }
    }
    if (nDim==1 && pM->Domain[nl][nd].Nx[0]==1) {ath_error(
      "[init_mesh]: 1D requires Nx1>1 but in %s Nx1=1,Nx2=%d,Nx3=%d\n",
      block,pM->Domain[nl][nd].Nx[1],pM->Domain[nl][nd].Nx[2]);
    }
    if (nDim==2 && pM->Domain[nl][nd].Nx[2]>1) {ath_error(
      "[init_mesh]:2D requires Nx1,Nx2 > 1 but in %s Nx1=%d,Nx2=%d,Nx3=%d\n",
      block,pM->Domain[nl][nd].Nx[0],pM->Domain[nl][nd].Nx[1],
      pM->Domain[nl][nd].Nx[2]);
    }
    for (i=0; i<nDim; i++) {
      xdiv[i] = div(pM->Domain[nl][nd].Nx[i], irefine);
      if (xdiv[i].rem != 0){
        ath_error("[init_mesh]: %s/Nx%d = %d must be divisible by %d\n",
          block,(i+1),pM->Domain[nl][nd].Nx[i],irefine);
      }
    }

/* Set cell size based on level of domain, but only if Ncell > 1 */

    for (i=0; i<3; i++) {
      if (pM->Domain[nl][nd].Nx[i] > 1) {
        pM->Domain[nl][nd].dx[i] = pM->dx[i]/(Real)(irefine);
      } else {
        pM->Domain[nl][nd].dx[i] = pM->dx[i];
      }
    }

/* Set displacement of Domain from origin. By definition, root level has 0
 * displacement, so only read for levels other than root  */

    for (i=0; i<3; i++) pM->Domain[nl][nd].Disp[i] = 0;
    if (nl != 0) {  
      if (par_exist(block,"iDisp") == 0)
        ath_error("[init_mesh]: iDisp does not exist in block %s\n",block);
      pM->Domain[nl][nd].Disp[0] = par_geti(block,"iDisp");

/* jDisp=0 if problem is only 1D */
      if (pM->Nx[1] > 1) {
        if (par_exist(block,"jDisp") == 0)
          ath_error("[init_mesh]: jDisp does not exist in block %s\n",block);
        pM->Domain[nl][nd].Disp[1] = par_geti(block,"jDisp");
      }

/* kDisp=0 if problem is only 2D */
      if (pM->Nx[2] > 1) {
        if (par_exist(block,"kDisp") == 0)
          ath_error("[init_mesh]: kDisp does not exist in block %s\n",block);
        pM->Domain[nl][nd].Disp[2] = par_geti(block,"kDisp");
      }
    }

    for (i=0; i<nDim; i++) {
      xdiv[i] = div(pM->Domain[nl][nd].Disp[i], irefine);
      if (xdiv[i].rem != 0){
        ath_error("[init_mesh]: %s/Disp%d = %d must be divisible by %d\n",
          block,(i+1),pM->Domain[nl][nd].Disp[i],irefine);
      }
    }

/* Use cell size and displacement from origin to compute min/max of x1/x2/x3 on
 * this domain.  Ensure that if Domain touches root grid boundary, the min/max
 * of this Domain are set IDENTICAL to values in root grid  */

    for (i=0; i<3; i++){

      if (pM->Domain[nl][nd].Disp[i] == 0) {
        pM->Domain[nl][nd].MinX[i] = root_xmin[i];
      } else { 
        pM->Domain[nl][nd].MinX[i] = root_xmin[i] 
          + ((Real)(pM->Domain[nl][nd].Disp[i]))*pM->Domain[nl][nd].dx[i];
      }

      izones= (pM->Domain[nl][nd].Disp[i] + pM->Domain[nl][nd].Nx[i])/irefine;
      if(izones == pM->Nx[i]){
        pM->Domain[nl][nd].MaxX[i] = root_xmax[i];
      } else {
        pM->Domain[nl][nd].MaxX[i] = pM->Domain[nl][nd].MinX[i] 
          + ((Real)(pM->Domain[nl][nd].Nx[i]))*pM->Domain[nl][nd].dx[i];
      }

      pM->Domain[nl][nd].RootMinX[i] = root_xmin[i];
      pM->Domain[nl][nd].RootMaxX[i] = root_xmax[i];
    }

  }  /*---------- end loop over domain blocks in input file ------------------*/
    
/*--- Step 4: Check that domains on the same level are non-overlapping. ------*/
/* Compare the integer coordinates of the sides of Domains at the same level.
 * Print error if Domains overlap or touch. */

  for (nl=maxlevel; nl>0; nl--){     /* start at highest level, and skip root */
  for (nd=0; nd<(pM->DomainsPerLevel[nl])-1; nd++){
    for (i=0; i<3; i++) {
      D1.ijkl[i] = pM->Domain[nl][nd].Disp[i];
      D1.ijkr[i] = pM->Domain[nl][nd].Disp[i] + pM->Domain[nl][nd].Nx[i];
    }

    for (ncd=nd+1; ncd<(pM->DomainsPerLevel[nl]); ncd++) {
      for (i=0; i<3; i++) {
        D2.ijkl[i] = pM->Domain[nl][ncd].Disp[i];
        D2.ijkr[i] = pM->Domain[nl][ncd].Disp[i] + pM->Domain[nl][ncd].Nx[i];
      }

      if (D1.ijkl[0] <= D2.ijkr[0] && D1.ijkr[0] >= D2.ijkl[0] &&
          D1.ijkl[1] <= D2.ijkr[1] && D1.ijkr[1] >= D2.ijkl[1] &&
          D1.ijkl[2] <= D2.ijkr[2] && D1.ijkr[2] >= D2.ijkl[2]){
          ath_error("Domains %d and %d at same level overlap or touch\n",
          pM->Domain[nl][nd].InputBlock,pM->Domain[nl][ncd].InputBlock);
      }
    }
  }}

/*--- Step 5: Check for illegal geometry of child/parent Domains -------------*/

  for (nl=0; nl<maxlevel; nl++){
  for (nd=0; nd<pM->DomainsPerLevel[nl]; nd++){
    pD = (DomainS*)&(pM->Domain[nl][nd]);  /* set ptr to this Domain */

    for (i=0; i<3; i++) {
      D1.ijkl[i] = pD->Disp[i];
      D1.ijkr[i] = pD->Disp[i] + pD->Nx[i];
    }

    for (ncd=0; ncd<pM->DomainsPerLevel[nl+1]; ncd++){
      pCD = (DomainS*)&(pM->Domain[nl+1][ncd]);  /* set ptr to potential child*/

      for (i=0; i<3; i++) {
        D2.ijkl[i] = pCD->Disp[i]/2;
        D2.ijkr[i] = 1;
        if (pCD->Nx[i] > 1) D2.ijkr[i] = (pCD->Disp[i] + pCD->Nx[i])/2;
      }

      if (D1.ijkl[0] <= D2.ijkr[0] && D1.ijkr[0] >= D2.ijkl[0] &&
          D1.ijkl[1] <= D2.ijkr[1] && D1.ijkr[1] >= D2.ijkl[1] &&
          D1.ijkl[2] <= D2.ijkr[2] && D1.ijkr[2] >= D2.ijkl[2]){

/* check for child Domains that touch edge of parent (and are not at edges of
 * root), extends past edge of parent, or are < nghost/2 from edge of parent  */

        for (dim=0; dim<nDim; dim++){
          irefine = 1;
          for (i=1;i<=nl;i++) irefine *= 2; /* parent refinement lev */
          roffset = (pCD->Disp[dim] + pCD->Nx[dim])/(2*irefine) - pM->Nx[dim];

          if (((D2.ijkl[dim] == D1.ijkl[dim]) && (pD->Disp[dim] != 0)) ||
              ((D2.ijkr[dim] == D1.ijkr[dim]) && (roffset != 0))) {
            for (i=0; i<nDim; i++) {
              D1.ijkl[i] /= irefine;  /* report indices scaled to root */
              D1.ijkr[i] /= irefine;
              D2.ijkl[i] /= irefine; 
              D2.ijkr[i] /= irefine;
            }
            ath_error("[init_mesh] child Domain D%d[is,ie,js,je,ks,ke]=[%d %d %d %d %d %d] touches parent D%d[is,ie,js,je,ks,ke]=[%d %d %d %d %d %d]\n",
              pCD->InputBlock,D2.ijkl[0],D2.ijkr[0],D2.ijkl[1],D2.ijkr[1],
              D2.ijkl[2],D2.ijkr[2],pD->InputBlock,D1.ijkl[0],D1.ijkr[0],
              D1.ijkl[1],D1.ijkr[1],D1.ijkl[2],D1.ijkr[2]);
          }

          if ((D2.ijkl[dim] < D1.ijkl[dim]) ||
              (D2.ijkr[dim] > D1.ijkr[dim])) {
            for (i=0; i<nDim; i++) {
              D1.ijkl[i] /= irefine;  /* report indices scaled to root */
              D1.ijkr[i] /= irefine;
              D2.ijkl[i] /= irefine; 
              D2.ijkr[i] /= irefine;
            }
            ath_error("[init_mesh] child Domain D%d[is,ie,js,je,ks,ke]=[%d %d %d %d %d %d] extends past parent D%d[is,ie,js,je,ks,ke]=[%d %d %d %d %d %d]\n",
              pCD->InputBlock,D2.ijkl[0],D2.ijkr[0],D2.ijkl[1],D2.ijkr[1],
              D2.ijkl[2],D2.ijkr[2],pD->InputBlock,D1.ijkl[0],D1.ijkr[0],
              D1.ijkl[1],D1.ijkr[1],D1.ijkl[2],D1.ijkr[2]);
          }

          if (((2*(D2.ijkl[dim]-D1.ijkl[dim]) < nghost) &&
               (2*(D2.ijkl[dim]-D1.ijkl[dim]) > 0     )) ||
              ((2*(D1.ijkr[dim]-D2.ijkr[dim]) < nghost) &&
               (2*(D1.ijkr[dim]-D2.ijkr[dim]) > 0     ))) {
            for (i=0; i<nDim; i++) {
              D1.ijkl[i] /= irefine;  /* report indices scaled to root */
              D1.ijkr[i] /= irefine;
              D2.ijkl[i] /= irefine; 
              D2.ijkr[i] /= irefine;
            }
            ath_error("[init_mesh] child Domain D%d[is,ie,js,je,ks,ke]=[%d %d %d %d %d %d] closer than nghost/2 to parent D%d[is,ie,js,je,ks,ke]=[%d %d %d %d %d %d]\n",
              pCD->InputBlock,D2.ijkl[0],D2.ijkr[0],D2.ijkl[1],D2.ijkr[1],
              D2.ijkl[2],D2.ijkr[2],pD->InputBlock,D1.ijkl[0],D1.ijkr[0],
              D1.ijkl[1],D1.ijkr[1],D1.ijkl[2],D1.ijkr[2]);
          }

        }
      }
    }
  }}

/*--- Step 6: Divide each Domain into Grids, and allocate to processor(s)  ---*/
/* Get the number of Grids in each direction.  These are given either in the
 * <domain?> block in the input file, or by automatic decomposition given the
 * number of processor desired for this domain.   */

  next_procID = 0;  /* start assigning processors to Grids at ID=0 */

  for (nl=0; nl<=maxlevel; nl++){
    for (nd=0; nd<(pM->DomainsPerLevel[nl]); nd++){
      pD = (DomainS*)&(pM->Domain[nl][nd]);  /* set ptr to this Domain */
      sprintf(block,"domain%d",pD->InputBlock);

#ifndef MPI_PARALLEL
      for (i=0; i<3; i++) pD->NGrid[i] = 1;
#else
      nproc = par_geti_def(block,"AutoWithNProc",0);

/* Read layout of Grids from input file */

      if (nproc == 0){
        pD->NGrid[0] = par_geti_def(block,"NGrid_x1",1);
        pD->NGrid[1] = par_geti_def(block,"NGrid_x2",1);
        pD->NGrid[2] = par_geti_def(block,"NGrid_x3",1);
        if (pD->NGrid[0] == 0)
          ath_error("[init_mesh] Cannot enter NGrid_x1=0 in %s\n",block);
        if (pD->NGrid[1] == 0)
          ath_error("[init_mesh] Cannot enter NGrid_x2=0 in %s\n",block);
        if (pD->NGrid[2] == 0)
          ath_error("[init_mesh] Cannot enter NGrid_x3=0 in %s\n",block);
      }

/* Auto decompose Domain into Grids.  To use this option, set "AutoWithNProc"
 * to number of processors desired for this Domain  */

      else if (nproc > 0){
        if(dom_decomp(pD->Nx[0],pD->Nx[1],pD->Nx[2],nproc,
           &(pD->NGrid[0]),&(pD->NGrid[1]),&(pD->NGrid[2])))
           ath_error("[init_mesh]: Error in automatic Domain decomposition\n");

        /* Store the domain decomposition in the par database */
        par_seti(block,"NGrid_x1","%d",pD->NGrid[0],"x1 decomp");
        par_seti(block,"NGrid_x2","%d",pD->NGrid[1],"x2 decomp");
        par_seti(block,"NGrid_x3","%d",pD->NGrid[2],"x3 decomp");

      } else {
        ath_error("[init_mesh] invalid AutoWithNProc=%d in %s\n",nproc,block);
      }
#endif /* MPI_PARALLEL */

/* test for conflicts between number of grids and dimensionality */

      for (i=0; i<3; i++){
        if(pD->NGrid[i] > 1 && pD->Nx[i] <= 1)
          ath_error("[init_mesh]: %s/NGrid_x%d = %d and Nx%d = %d\n",block,
          (i+1),pD->NGrid[i],(i+1),pD->Nx[i]);
      }

/* check there are more processors than Grids needed by this Domain. */

      nproc = (pD->NGrid[0])*(pD->NGrid[1])*(pD->NGrid[2]);
      if(nproc > Nproc_Comm_world) ath_error(
        "[init_mesh]: %d Grids requested by block %s and only %d procs\n"
        ,nproc,block,Nproc_Comm_world); 

/* Build 3D array to store data on Grids in this Domain */

      if ((pD->GData = (GridsDataS***)calloc_3d_array(pD->NGrid[2],pD->NGrid[1],
        pD->NGrid[0],sizeof(GridsDataS))) == NULL) ath_error(
        "[init_mesh]: GData calloc returned a NULL pointer\n");

/* Divide the domain into blocks */

      for (i=0; i<3; i++) {
        xdiv[i] = div(pD->Nx[i], pD->NGrid[i]);
      }

/* Distribute cells in Domain to Grids.  Assign each Grid to a processor ID in
 * the MPI_COMM_WORLD communicator.  For single-processor jobs, there is only
 * one ID=0, and the GData array will have only one element. */

      for(n=0; n<(pD->NGrid[2]); n++){
      for(m=0; m<(pD->NGrid[1]); m++){
      for(l=0; l<(pD->NGrid[0]); l++){
        for (i=0; i<3; i++) pD->GData[n][m][l].Nx[i] = xdiv[i].quot;
        pD->GData[n][m][l].ID_Comm_world = next_procID++;
        if (next_procID > ((Nproc_Comm_world)-1)) next_procID=0;
      }}}

/* If the Domain is not evenly divisible put the extra cells on the first
 * Grids in each direction, maintaining the load balance as much as possible */

      for(n=0; n<(pD->NGrid[2]); n++){
        for(m=0; m<(pD->NGrid[1]); m++){
          for(l=0; l<xdiv[0].rem; l++){
            pD->GData[n][m][l].Nx[0]++;
          }
        }
      }
      xdiv[0].rem=0;

      for(n=0; n<(pD->NGrid[2]); n++){
        for(m=0; m<xdiv[1].rem; m++) {
          for(l=0; l<(pD->NGrid[0]); l++){
            pD->GData[n][m][l].Nx[1]++;
          }
        }
      }
      xdiv[1].rem=0;

      for(n=0; n<xdiv[2].rem; n++){
        for(m=0; m<(pD->NGrid[1]); m++){
          for(l=0; l<(pD->NGrid[0]); l++){
            pD->GData[n][m][l].Nx[2]++;
          }
        }
      }
      xdiv[2].rem=0;

/* Initialize displacements from origin for each Grid */

      for(n=0; n<(pD->NGrid[2]); n++){
        for(m=0; m<(pD->NGrid[1]); m++){
          pD->GData[n][m][0].Disp[0] = pD->Disp[0];
          for(l=1; l<(pD->NGrid[0]); l++){
            pD->GData[n][m][l].Disp[0] = pD->GData[n][m][l-1].Disp[0] + 
                                         pD->GData[n][m][l-1].Nx[0];
          }
        }
      }

      for(n=0; n<(pD->NGrid[2]); n++){
        for(l=0; l<(pD->NGrid[0]); l++){
          pD->GData[n][0][l].Disp[1] = pD->Disp[1];
          for(m=1; m<(pD->NGrid[1]); m++){
            pD->GData[n][m][l].Disp[1] = pD->GData[n][m-1][l].Disp[1] + 
                                         pD->GData[n][m-1][l].Nx[1];
          }
        }
      }

      for(m=0; m<(pD->NGrid[1]); m++){
        for(l=0; l<(pD->NGrid[0]); l++){
          pD->GData[0][m][l].Disp[2] = pD->Disp[2];
          for(n=1; n<(pD->NGrid[2]); n++){
            pD->GData[n][m][l].Disp[2] = pD->GData[n-1][m][l].Disp[2] + 
                                         pD->GData[n-1][m][l].Nx[2];
          }
        }
      }

    }  /* end loop over ndomains */
  }    /* end loop over nlevels */

/* check that total number of Grids was partitioned evenly over total number of
 * MPI processes available (equal to one for single processor jobs) */ 

  if (next_procID != 0)
    ath_error("[init_mesh]:total # of Grids != total # of MPI procs\n");

/*--- Step 7: Allocate a Grid for each Domain on this processor --------------*/

  for (nl=0; nl<=maxlevel; nl++){
    for (nd=0; nd<(pM->DomainsPerLevel[nl]); nd++){
      pD = (DomainS*)&(pM->Domain[nl][nd]);  /* set ptr to this Domain */
      sprintf(block,"domain%d",pD->InputBlock);
      pD->Grid = NULL;

/* Loop over GData array, and if there is a Grid assigned to this proc, 
 * allocate it */

      for(n=0; n<(pD->NGrid[2]); n++){
      for(m=0; m<(pD->NGrid[1]); m++){
      for(l=0; l<(pD->NGrid[0]); l++){
        if (pD->GData[n][m][l].ID_Comm_world == myID_Comm_world) {
          if ((pD->Grid = (GridS*)malloc(sizeof(GridS))) == NULL)
            ath_error("[init_mesh]: Failed to malloc a Grid for %s\n",block);
        }
      }}}
    }
  }

/*--- Step 8: Create an MPI Communicator for each Domain ---------------------*/

#ifdef MPI_PARALLEL
/* Allocate memory for ranks[] array */

  max_rank = 0;
  for (nl=0; nl<=maxlevel; nl++){
  for (nd=0; nd<(pM->DomainsPerLevel[nl]); nd++){
    pD = (DomainS*)&(pM->Domain[nl][nd]);  /* set ptr to this Domain */
    Nranks = (pD->NGrid[0])*(pD->NGrid[1])*(pD->NGrid[2]);
    max_rank = MAX(max_rank, Nranks);
  }}
  ranks = (int*)calloc_1d_array(max_rank,sizeof(int));

/* Extract handle of group defined by MPI_COMM_WORLD communicator */

  ierr = MPI_Comm_group(MPI_COMM_WORLD, &world_group);

  for (nl=0; nl<=maxlevel; nl++){
  for (nd=0; nd<(pM->DomainsPerLevel[nl]); nd++){
    pD = (DomainS*)&(pM->Domain[nl][nd]);  /* set ptr to this Domain */

/* Load integer array with ranks of processes in MPI_COMM_WORLD updating Grids
 * on this Domain.  The ranks of these processes in the new Comm_Domain
 * communicator created below are equal to the indices of this array */

    Nranks = (pD->NGrid[0])*(pD->NGrid[1])*(pD->NGrid[2]);
    groupn = 0;

    for(n=0; n<(pD->NGrid[2]); n++){
    for(m=0; m<(pD->NGrid[1]); m++){
    for(l=0; l<(pD->NGrid[0]); l++){
      ranks[groupn] = pD->GData[n][m][l].ID_Comm_world;
      pD->GData[n][m][l].ID_Comm_Domain = groupn;
      groupn++;
    }}}

/* Create a new group for this Domain; use it to create a new communicator */

    ierr = MPI_Group_incl(world_group,Nranks,ranks,&(pD->Group_Domain));
    ierr = MPI_Comm_create(MPI_COMM_WORLD,pD->Group_Domain,&(pD->Comm_Domain));

  }}

  free_1d_array(ranks);
#endif /* MPI_PARALLEL */

/*--- Step 9: Create MPI Communicators for Child and Parent Domains ----------*/

#if defined(MPI_PARALLEL) && defined(STATIC_MESH_REFINEMENT)
/* Initialize communicators to NULL, since not all Domains use them, and
 * allocate memory for ranks[] array */

  for (nl=0; nl<=maxlevel; nl++){
    for (nd=0; nd<(pM->DomainsPerLevel[nl]); nd++){
      pM->Domain[nl][nd].Comm_Parent = MPI_COMM_NULL;
      pM->Domain[nl][nd].Comm_Children = MPI_COMM_NULL;
    }
  }

  if (maxlevel > 0) {
    ranks = (int*)calloc_1d_array(Nproc_Comm_world,sizeof(int));
  }

/* For each Domain up to (maxlevel-1), initialize communicator with children */

  for (nl=0; nl<maxlevel; nl++){
  for (nd=0; nd<pM->DomainsPerLevel[nl]; nd++){
    pD = (DomainS*)&(pM->Domain[nl][nd]);  /* set ptr to this Domain */
    child_found = 0;

/* Load integer array with ranks of processes in MPI_COMM_WORLD updating Grids
 * on this Domain, in case a child Domain is found.  Set IDs in Comm_Children
 * communicator based on index in rank array, in case child found.  If no
 * child is found these ranks will never be used. */

    Nranks = (pD->NGrid[0])*(pD->NGrid[1])*(pD->NGrid[2]);
    groupn = 0;

    for(n=0; n<(pD->NGrid[2]); n++){
    for(m=0; m<(pD->NGrid[1]); m++){
    for(l=0; l<(pD->NGrid[0]); l++){
      ranks[groupn] = pD->GData[n][m][l].ID_Comm_world;
      pD->GData[n][m][l].ID_Comm_Children = groupn;
      groupn++;
    }}}

/* edges of this Domain */
    for (i=0; i<3; i++) {
      D1.ijkl[i] = pD->Disp[i];
      D1.ijkr[i] = pD->Disp[i] + pD->Nx[i];
    }

/* Loop over all Domains at next level, looking for children of this Domain */

    for (ncd=0; ncd<pM->DomainsPerLevel[nl+1]; ncd++){
      pCD = (DomainS*)&(pM->Domain[nl+1][ncd]);  /* set ptr to potential child*/

/* edges of potential child Domain */
      for (i=0; i<3; i++) {
        D2.ijkl[i] = pCD->Disp[i]/2;
        D2.ijkr[i] = 1;
        if (pCD->Nx[i] > 1) D2.ijkr[i] = (pCD->Disp[i] + pCD->Nx[i])/2;
      }

      if (D1.ijkl[0] < D2.ijkr[0] && D1.ijkr[0] > D2.ijkl[0] &&
          D1.ijkl[1] < D2.ijkr[1] && D1.ijkr[1] > D2.ijkl[1] &&
          D1.ijkl[2] < D2.ijkr[2] && D1.ijkr[2] > D2.ijkl[2]){
        child_found = 1;

/* Child found.  Add child processors to ranks array, but only if they are
 * different from processes currently there (including parent and any previously
 * found children).  Set IDs associated with Comm_Parent communicator, since on 
 * the child Domain this is the same as the Comm_Children communicator on the
 * parent Domain  */

        for(n=0; n<(pCD->NGrid[2]); n++){
        for(m=0; m<(pCD->NGrid[1]); m++){
        for(l=0; l<(pCD->NGrid[0]); l++){
          irank = -1;
          for (i=0; i<Nranks; i++) {
            if(pCD->GData[n][m][l].ID_Comm_world == ranks[i]) irank = i;
          }
          if (irank == -1) {
            ranks[groupn] = pCD->GData[n][m][l].ID_Comm_world;
            pCD->GData[n][m][l].ID_Comm_Parent = groupn;
            groupn++;
            Nranks++;
          } else {
            pCD->GData[n][m][l].ID_Comm_Parent = ranks[irank];
          }
        }}}
      }
    }

/* After looping over all potential child Domains, create a new communicator if
 * a child was found */

    if (child_found == 1) {
      ierr = MPI_Group_incl(world_group, Nranks, ranks, &(pD->Group_Children));
      ierr = MPI_Comm_create(MPI_COMM_WORLD,pD->Group_Children,
        &pD->Comm_Children);

/* Loop over children to set Comm_Parent communicators */

      for (ncd=0; ncd<pM->DomainsPerLevel[nl+1]; ncd++){
        pCD = (DomainS*)&(pM->Domain[nl+1][ncd]);  

        for (i=0; i<3; i++) {
          D2.ijkl[i] = pCD->Disp[i]/2;
          D2.ijkr[i] = 1;
          if (pCD->Nx[i] > 1) D2.ijkr[i] = (pCD->Disp[i] + pCD->Nx[i])/2;
        }

        if (D1.ijkl[0] < D2.ijkr[0] && D1.ijkr[0] > D2.ijkl[0] &&
            D1.ijkl[1] < D2.ijkr[1] && D1.ijkr[1] > D2.ijkl[1] &&
            D1.ijkl[2] < D2.ijkr[2] && D1.ijkr[2] > D2.ijkl[2]){
          pCD->Comm_Parent = pD->Comm_Children;
        }
      }
    }
  }}

#endif /* MPI_PARALLEL & STATIC_MESH_REFINEMENT  */

  free(next_domainid);
  return;
}