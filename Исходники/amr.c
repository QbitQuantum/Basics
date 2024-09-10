void L_mark_cells(int level,struct RUNPARAMS *param, struct OCT **firstoct, int nsmooth, REAL threshold, struct CPUINFO *cpu, struct PACKET **sendbuffer, struct PACKET **recvbuffer){

  int nmark;
  int marker;
  int ismooth;
  REAL dx;
  int pass;
  struct OCT *nextoct;
  struct OCT *curoct;
  struct OCT *newoct;
  struct OCT *desoct;
  int icell,ii,il,ip;
  int smark;
  int vnei[6],vcell[6];
  int vnei2[6],vcell2[6];
  int vnei3[6],vcell3[6];
  struct CELL *newcell;
  struct CELL *newcell2;
  struct CELL *newcell3;
  int ichild;
  REAL mcell;
  REAL mmax=0.;
  int stati[3]={0,0,0};
  REAL rin;

  if(cpu->rank==RANK_DISP) printf("==> start marking");
  //    for(level=levelmax;level>=param->lcoarse;level--) // looping over octs
  marker=0;
  nmark=0;
  for(ismooth=0;ismooth<nsmooth;ismooth++)
    {
	  //printf("level=%d ",level);
	  dx=1./POW(2,level);

#ifdef ZOOM
 	  rin=param->rzoom*POW(param->fzoom,param->lmaxzoom-level-1);
	  //printf("rin=%e\n",rin);
#endif
	  for(pass=0;pass<3;pass++)
	    {
	      marker++;
	      nextoct=firstoct[level-1];
	      if(nextoct==NULL){
		//printf("Mark on level %d skipped by proc %d\n",level,cpu->rank);
	      }
	      else{
		do
		  {
		    curoct=nextoct;
		    nextoct=curoct->next;
		    if(curoct->cpu!=cpu->rank) continue;
		    for(icell=0;icell<8;icell++) // looping over cells in oct
		      {
			if((pass==0)&&(ismooth==0)){
			  if(curoct->cell[icell].marked>0){
          printf("marked>0 check amr.c\n");
          abort();
			  }
			}

			switch(pass){
			  //=========================================================
			case 0: // marking cell already refined or marked marker=1/4
			  smark=0;
			  if((curoct->cell[icell].child!=NULL)&&(curoct->cell[icell].marked==0)){ // CHECK IF ACTING ON ORIGINAL OR COPY
			    newoct=curoct->cell[icell].child;
			    for(ichild=0;ichild<8;ichild++){
			      smark+=((newoct->cell[ichild].marked!=0)||(newoct->cell[ichild].child!=NULL));
			    }
			  }
			  if(smark!=0){
			    curoct->cell[icell].marked=marker;
			    nmark++;
			    stati[0]++;
			  }
			  break;
			  //=========================================================
			case 1: //marking neighbors marker=2/5
			  if((curoct->cell[icell].marked<marker)&&(curoct->cell[icell].marked>0)){
			    getcellnei(icell, vnei, vcell);
			    for(ii=0;ii<6;ii++){ // marking the 6 cardinal neighbors
			      if(vnei[ii]==6){
				newcell=&(curoct->cell[vcell[ii]]);
				if(curoct->cell[vcell[ii]].marked==0){
				  curoct->cell[vcell[ii]].marked=marker;
				  nmark++;stati[1]++;
				}
			      }
			      else{
				// Note that the neibourgh cell may not exist therefore we have to check
				if(curoct->nei[vnei[ii]]->child!=NULL){
#ifdef TRANSXM
				  if((ii==0)&&(curoct->x==0.)){
				    newcell=NULL;
				    continue;
				  }
#endif

#ifdef TRANSXP
				  if((ii==1)&&((curoct->x+2.*dx)==1.)){
				    newcell=NULL;
				    continue;
				  }
#endif

#ifdef TRANSYM
				  if((ii==2)&&(curoct->y==0.)){
				    newcell=NULL;
				    continue;
				  }
#endif

#ifdef TRANSYP
				  if((ii==3)&&(curoct->y+2.*dx==1.)){
				    newcell=NULL;
				    continue;
				  }
#endif

#ifdef TRANSZM
				  if((ii==4)&&(curoct->z==0.)){
				    newcell=NULL;
				    continue;
				  }
#endif

#ifdef TRANSZP
				  if((ii==5)&&(curoct->z+2.*dx==1.)){
				    newcell=NULL;
				    continue;
				  }
#endif

				  newcell=&(curoct->nei[vnei[ii]]->child->cell[vcell[ii]]);
				  if(curoct->nei[vnei[ii]]->child->cell[vcell[ii]].marked==0) {
				    curoct->nei[vnei[ii]]->child->cell[vcell[ii]].marked=marker;
				    nmark++;stati[1]++;
				  }
				}
				else{
				  newcell=NULL;
				}
			      }

			      // each of the 6 cardinal neighbors will mark 4 side neighbors
			      if(newcell!=NULL){
				newoct=cell2oct(newcell); // we get the parent oct
				getcellnei(newcell->idx, vnei2, vcell2); //we get the neighbors
				for(il=0;il<6;il++){
				  if((il/2)==(ii/2)) continue;
				  if(vnei2[il]==6){
				    newcell2=&(newoct->cell[vcell2[il]]);
				    if(newoct->cell[vcell2[il]].marked==0){
				      newoct->cell[vcell2[il]].marked=marker;
				      nmark++;stati[1]++;
				    }
				  }
				  else{
				    if(newoct->nei[vnei2[il]]->child!=NULL){
#ifdef TRANSXM
				      if((il==0)&&(newoct->x==0.)){
					newcell2=NULL;
					continue;
				      }
#endif

#ifdef TRANSXP
				      if((il==1)&&((newoct->x+2.*dx)==1.)){
					newcell2=NULL;
					continue;
				      }
#endif

#ifdef TRANSYM
				      if((il==2)&&(newoct->y==0.)){
					newcell2=NULL;
					continue;
				      }
#endif

#ifdef TRANSYP
				      if((il==3)&&(newoct->y+2.*dx==1.)){
					newcell2=NULL;
					continue;
				      }
#endif

#ifdef TRANSZM
				      if((il==4)&&(newoct->z==0.)){
					newcell2=NULL;
					continue;
				      }
#endif

#ifdef TRANSZP
				      if((il==5)&&(newoct->z+2.*dx==1.)){
					newcell2=NULL;
					continue;
				      }
#endif



				      newcell2=&(newoct->nei[vnei2[il]]->child->cell[vcell2[il]]);
				      if(newoct->nei[vnei2[il]]->child->cell[vcell2[il]].marked==0){
					newoct->nei[vnei2[il]]->child->cell[vcell2[il]].marked=marker;
					nmark++;stati[1]++;
				      }
				    }
				    else{
				      newcell2=NULL;
				    }
				  }

				  // ecah of the 4 side neighbors will mark 2 corners
				  if(newcell2!=NULL){
				    desoct=cell2oct(newcell2);
				    getcellnei(newcell2->idx, vnei3, vcell3);
				    for(ip=0;ip<6;ip++){
				      if(((ip/2)==(il/2))||((ip/2)==(ii/2))) continue;
				      if(vnei3[ip]==6){
					if(desoct->cell[vcell3[ip]].marked==0){
					  desoct->cell[vcell3[ip]].marked=marker;
					  nmark++;stati[1]++;
					}
				      }
				      else{
					if(desoct->nei[vnei3[ip]]->child!=NULL){
#ifdef TRANSXM
					  if((ip==0)&&(desoct->x==0.)){
					    continue;
					  }
#endif

#ifdef TRANSXP
					  if((ip==1)&&((desoct->x+2.*dx)==1.)){
					    continue;
					  }
#endif

#ifdef TRANSYM
					  if((ip==2)&&(desoct->y==0.)){
					    continue;
					  }
#endif

#ifdef TRANSYP
					  if((ip==3)&&(desoct->y+2.*dx==1.)){
					    continue;
					  }
#endif

#ifdef TRANSZM
					  if((ip==4)&&(desoct->z==0.)){
					    continue;
					  }
#endif

#ifdef TRANSZP
					  if((ip==5)&&(desoct->z+2.*dx==1.)){
					    continue;
					  }
#endif
					  if(desoct->nei[vnei3[ip]]->child->cell[vcell3[ip]].marked==0){
					    desoct->nei[vnei3[ip]]->child->cell[vcell3[ip]].marked=marker;

					    nmark++;stati[1]++;
					  }
					}
				      }
				    }
				  }
				}
			      }
			    }
			  }
			  break;
			  //=========================================================
			case 2: // marking cells satisfying user defined criterion marker=3/6
			  if((curoct->level<=param->lmax)&&(ismooth==0)){ // we don't need to test the finest level


#ifdef ZOOM
			    // if within zoomed region the cell is marked in any case
			    int flagzoom=0;
			    if(level<param->lmaxzoom){
			      flagzoom=queryzoom(curoct,icell,dx,rin);
			      if((flagzoom)&&(curoct->cell[icell].marked==0)) {
				curoct->cell[icell].marked=marker;
				nmark++;stati[2]++;
			      }
			    }
#endif

			    REAL den;

#ifdef EVRARD
			    // ===================== EVRARD TEST ================

 			    mcell=comp_grad_hydro(curoct, icell)*(curoct->level>=param->lcoarse);
			    if(mcell>mmax) mmax=mcell;
			    if((mcell>(threshold))&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }

#else
			    // ===================== AMR COSMO ================

			    // First we define the density
#ifdef TESTCOSMO

#ifdef WGRAV
			    den=curoct->cell[icell].gdata.d+1.;
#endif // WGRAV

#ifdef ZELDOVICH
#ifdef WHYDRO2
			    den=curoct->cell[icell].field.d;
#endif // WHYDRO2
#endif // ZELDOVICH

#else // #ifndef TESTCOSMO

#ifdef WGRAV
			    // ->> utilise pour la cosmo // le gaz est utilise
			    den=curoct->cell[icell].gdata.d;
#endif // WGRAV
#endif // TESTCOSMO

			    // Second we apply a criterion

#ifdef PIC
#ifdef EDBERT
			    mcell=den*(curoct->level>=param->lcoarse)*dx*dx*dx;
			    if(mcell>mmax) mmax=mcell;
			    if((mcell>threshold)&&(curoct->cell[icell].marked==0)) {
 			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }

#else // #ifndef EDBERT
#ifdef ZELDOVICH
			    mcell=den*(curoct->level>=param->lcoarse);
			    if(mcell>mmax) mmax=mcell;
			    if((mcell>threshold)&&(curoct->cell[icell].marked==0)) {
 			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }
#else // #ifndef ZELDOVICH

			    // --------------- MAIN AMR COSMO

			    int refarea=1;
#ifdef ZOOM
			    refarea=(curoct->level>=param->lmaxzoom);
#endif // ZOOM

#ifndef AMRPART
			    mcell=den*(curoct->level>=param->lcoarse)*dx*dx*dx*refarea;
#else // #ifdef AMRPART

#ifdef PIC
			    int npart=0;
			    if(curoct->level>=param->lcoarse){
			      countpartDM(&curoct->cell[icell],&npart);
			    }
			    mcell=npart;
			    threshold=param->amrthresh0;

#else // #ifndef PIC
			    printf("AMR on particles SET ON without PIC enabled\n");
			    abort();
#endif // PIC
#endif // AMRPART
			    if(mcell>mmax) mmax=mcell;
			    if((mcell>threshold)&&(curoct->cell[icell].marked==0)) {
  			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }

			    // --------------- MAIN AMR COSMO
#endif // ZELDOVICH
#endif // EDBERT
#else // #ifndef PIC

			    // ===================== AMR NO COSMO ================

#ifdef WGRAV
			    mcell=den*(curoct->level>=param->lcoarse);
			    if((mcell>threshold)&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }
#endif // WGRAV

#ifdef SNTEST
/*
          threshold=1e-5;

			    mcell=comp_grad_hydro(curoct, icell)*(curoct->level>=param->lcoarse);//*(fabs(curoct->y-0.5)<0.05)*(fabs(curoct->z-0.5)<0.05);
			    if(mcell>mmax) mmax=mcell;
			    if((mcell>(threshold))&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }
*/
        //if (cpu->nsteps >= 50)
        {
          REAL epsilon = 1e-1;
          REAL threshold = 1. + epsilon;
          mcell=curoct->cell[icell].field.d;
			    if( (mcell>threshold)&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }
        }



#endif // SNTEST

#ifdef WRAD
#ifdef WRADTEST
			    // == START AMR STRATEGY FOR RAD TESTS
			    mcell=comp_grad_rad(curoct, icell)*(curoct->level>=param->lcoarse);

#ifdef TESTCLUMP
			    REAL den2;
			    den2=curoct->cell[icell].rfield.nh*param->unit.unit_N;
			    den=-1;

			    //mcell=(curoct->cell[icell].rfield.src>0.);
			    if((((den<8e-1)&&(den>1e-1))||(den2>250.))&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }

#else
			    //mcell=0.;
			    den=curoct->cell[icell].rfield.nhplus/curoct->cell[icell].rfield.nh; // xion
#endif // TESTCLUMP


 			    //mcell=(curoct->cell[icell].rfield.src>0.);
			    if(((den<8e-1)&&(den>1e-2))&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }

			    // == END AMR STRATEGY FOR RAD TESTS
#else

#ifdef WCHEM
			    mcell=comp_grad_rad(curoct, icell)*(curoct->level>=param->lcoarse);
			    if((mcell>(threshold))&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }

#endif // WCHEM
#endif // WRADTEST
#endif // WRAD
#endif // PIC

#ifdef TUBE
#ifdef SED
			    mcell=curoct->cell[icell].field.d;
#else
			    mcell=comp_grad_hydro(curoct, icell)*(curoct->level>=param->lcoarse);//*(fabs(curoct->y-0.5)<0.05)*(fabs(curoct->z-0.5)<0.05);
#endif
			    if(mcell>mmax) mmax=mcell;
			    if((mcell>(1.1))&&(curoct->cell[icell].marked==0)) {
			      curoct->cell[icell].marked=marker;
			      nmark++;stati[2]++;
			    }
#endif // TUBE
#endif // EVRARD

			  }

			}
		      }
		  }while(nextoct!=NULL);
		//printf("pass=%d nmark=%d\n",pass,nmark);
	      }
#ifdef WMPI
	      MPI_Barrier(cpu->comm);
	      // we correct from the marker diffusion
	      if(marker%3==2) mpi_cic_correct_level(cpu, cpu->sendbuffer, cpu->recvbuffer, 1,level);

#endif

	    }
	  //printf("\n");
    }

 // printf("stat0=%d stat1=%d stat2=%d on rank %d\n",stati[0],stati[1],stati[2],cpu->rank);

#ifdef WMPI
  int stat0,stat1,stat2;
  REAL MMAX;
  MPI_Allreduce(&stati[0],&stat0,1,MPI_INT,MPI_SUM,cpu->comm);
  stati[0]=stat0;
  MPI_Allreduce(&stati[1],&stat1,1,MPI_INT,MPI_SUM,cpu->comm);
  stati[1]=stat1;
  MPI_Allreduce(&stati[2],&stat2,1,MPI_INT,MPI_SUM,cpu->comm);
  stati[2]=stat2;

  MPI_Allreduce(&mmax,&MMAX,1,MPI_REEL,MPI_MAX,cpu->comm);
  mmax=MMAX;
#endif

  if(cpu->rank==RANK_DISP) printf(" STAT MARK 0:%d 1:%d 2:%d mmax=%e thresh=%e\n",stati[0],stati[1],stati[2],mmax,threshold);

}