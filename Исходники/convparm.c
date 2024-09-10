static void assign_param(t_functype ftype,t_iparams *newparam,
			 real old[MAXFORCEPARAM],int comb,double reppow)
{
  int  i,j;
  real tmp;

  /* Set to zero */
  for(j=0; (j<MAXFORCEPARAM); j++) 
    {
      newparam->generic.buf[j]=0.0;
    }
  switch (ftype) {
  case F_G96ANGLES:
    /* Post processing of input data: store cosine iso angle itself */
    newparam->harmonic.rA =cos(old[0]*DEG2RAD);
    newparam->harmonic.krA=old[1];
    newparam->harmonic.rB =cos(old[2]*DEG2RAD);
    newparam->harmonic.krB=old[3];
    break;
  case F_G96BONDS:
    /* Post processing of input data: store square of length itself */
    newparam->harmonic.rA =sqr(old[0]);
    newparam->harmonic.krA=old[1];
    newparam->harmonic.rB =sqr(old[2]);
    newparam->harmonic.krB=old[3];
    break;
  case F_FENEBONDS:
    newparam->fene.bm=old[0];
    newparam->fene.kb=old[1];
    break;
  case F_RESTRBONDS:
    newparam->restraint.lowA = old[0];
    newparam->restraint.up1A = old[1];
    newparam->restraint.up2A = old[2];
    newparam->restraint.kA   = old[3];
    newparam->restraint.lowB = old[4];
    newparam->restraint.up1B = old[5];
    newparam->restraint.up2B = old[6];
    newparam->restraint.kB   = old[7];
    break;
  case F_TABBONDS:
  case F_TABBONDSNC:
  case F_TABANGLES:
  case F_TABDIHS:
    newparam->tab.table = round_check(old[0],0,ftype,"table index");
    newparam->tab.kA    = old[1];
    newparam->tab.kB    = old[3];
    break;
  case F_CROSS_BOND_BONDS:
    newparam->cross_bb.r1e=old[0];
    newparam->cross_bb.r2e=old[1];
    newparam->cross_bb.krr=old[2];
    break;
  case F_CROSS_BOND_ANGLES:
    newparam->cross_ba.r1e=old[0];
    newparam->cross_ba.r2e=old[1];
    newparam->cross_ba.r3e=old[2];
    newparam->cross_ba.krt=old[3];
    break;
  case F_UREY_BRADLEY:
    newparam->u_b.thetaA=old[0];
    newparam->u_b.kthetaA=old[1];
    newparam->u_b.r13A=old[2];
    newparam->u_b.kUBA=old[3];
    newparam->u_b.thetaB=old[4];
    newparam->u_b.kthetaB=old[5];
    newparam->u_b.r13B=old[6];
    newparam->u_b.kUBB=old[7];
    break;
  case F_QUARTIC_ANGLES:
    newparam->qangle.theta=old[0];
    for(i=0; i<5; i++)
      newparam->qangle.c[i]=old[i+1];
    break;
  case F_LINEAR_ANGLES:
    newparam->linangle.aA    = old[0];
    newparam->linangle.klinA = old[1];
    newparam->linangle.aB    = old[2];
    newparam->linangle.klinB = old[3];
    break;
  case F_BONDS:
  case F_ANGLES:
  case F_HARMONIC:
  case F_IDIHS:
    newparam->harmonic.rA =old[0];
    newparam->harmonic.krA=old[1];
    newparam->harmonic.rB =old[2];
    newparam->harmonic.krB=old[3];
    break;
  case F_MORSE:
    newparam->morse.b0A    =old[0];
    newparam->morse.cbA    =old[1];
    newparam->morse.betaA  =old[2];
    newparam->morse.b0B    =old[3];
    newparam->morse.cbB    =old[4];
    newparam->morse.betaB  =old[5];
    break;
  case F_CUBICBONDS:
    newparam->cubic.b0    =old[0];
    newparam->cubic.kb    =old[1];
    newparam->cubic.kcub  =old[2];
    break;
  case F_CONNBONDS:
    break;
  case F_POLARIZATION:
    newparam->polarize.alpha = old[0];
    break;
  case F_ANHARM_POL:
    newparam->anharm_polarize.alpha = old[0];
    newparam->anharm_polarize.drcut = old[1];
    newparam->anharm_polarize.khyp  = old[2];
    break;
  case F_WATER_POL:
    newparam->wpol.al_x   =old[0];
    newparam->wpol.al_y   =old[1];
    newparam->wpol.al_z   =old[2];
    newparam->wpol.rOH    =old[3];
    newparam->wpol.rHH    =old[4];
    newparam->wpol.rOD    =old[5];
    break;
  case F_THOLE_POL:
    newparam->thole.a      = old[0];
    newparam->thole.alpha1 = old[1];
    newparam->thole.alpha2 = old[2];
    if ((old[1] > 0) && (old[2] > 0))
      newparam->thole.rfac = old[0]*pow(old[1]*old[2],-1.0/6.0);
    else
      newparam->thole.rfac = 1;
    break;
  case F_BHAM:
    newparam->bham.a = old[0];
    newparam->bham.b = old[1];
    newparam->bham.c = old[2];
    break;
  case F_LJ14:
    set_ljparams(comb,reppow,old[0],old[1],&newparam->lj14.c6A,&newparam->lj14.c12A);
    set_ljparams(comb,reppow,old[2],old[3],&newparam->lj14.c6B,&newparam->lj14.c12B);
    break;
  case F_LJC14_Q:
    newparam->ljc14.fqq = old[0];
    newparam->ljc14.qi  = old[1];
    newparam->ljc14.qj  = old[2];
    set_ljparams(comb,reppow,old[3],old[4],&newparam->ljc14.c6,&newparam->ljc14.c12);
    break;
  case F_LJC_PAIRS_NB:
    newparam->ljcnb.qi = old[0];
    newparam->ljcnb.qj = old[1];
    set_ljparams(comb,reppow,old[2],old[3],&newparam->ljcnb.c6,&newparam->ljcnb.c12);
    break;
  case F_LJ:
    set_ljparams(comb,reppow,old[0],old[1],&newparam->lj.c6,&newparam->lj.c12);
    break;
  case F_PDIHS:
  case F_PIDIHS:
  case F_ANGRES:
  case F_ANGRESZ:
    newparam->pdihs.phiA = old[0];
    newparam->pdihs.cpA  = old[1];
		  
    /* Dont do any checks if all parameters are zero (such interactions will be removed).
     * Change 20100720: Amber occasionally uses negative multiplicities (mathematically OK),
     * so I have changed the lower limit to -99 /EL
     *
     * Second, if the force constant is zero in both A and B states, we set the phase
     * and multiplicity to zero too so the interaction gets removed during clean-up.
     */	
    newparam->pdihs.phiB = old[3];
    newparam->pdihs.cpB  = old[4];
          
    if( fabs(newparam->pdihs.cpA) < GMX_REAL_MIN && fabs(newparam->pdihs.cpB) < GMX_REAL_MIN )
    {
        newparam->pdihs.phiA = 0.0; 
        newparam->pdihs.phiB = 0.0; 
        newparam->pdihs.mult = 0; 
    } 
    else
    {
        newparam->pdihs.mult = round_check(old[2],-99,ftype,"multiplicity");
    }
          
    break;
  case F_POSRES:
    newparam->posres.fcA[XX]   = old[0];
    newparam->posres.fcA[YY]   = old[1];
    newparam->posres.fcA[ZZ]   = old[2];
    newparam->posres.fcB[XX]   = old[3];
    newparam->posres.fcB[YY]   = old[4];
    newparam->posres.fcB[ZZ]   = old[5];
    newparam->posres.pos0A[XX] = old[6];
    newparam->posres.pos0A[YY] = old[7];
    newparam->posres.pos0A[ZZ] = old[8];
    newparam->posres.pos0B[XX] = old[9];
    newparam->posres.pos0B[YY] = old[10];
    newparam->posres.pos0B[ZZ] = old[11];
    break;
  case F_FBPOSRES:
    newparam->fbposres.geom     = round_check(old[0],0,ftype,"geometry");
    if ( ! (newparam->fbposres.geom > efbposresZERO && newparam->fbposres.geom < efbposresNR))
    {
      gmx_fatal(FARGS,"Invalid geometry for flat-bottomed position restraint.\n"
		"Expected number between 1 and %d. Found %d\n", efbposresNR-1,
		newparam->fbposres.geom);
    }
    newparam->fbposres.r        = old[1];
    newparam->fbposres.k        = old[2];
    newparam->fbposres.pos0[XX] = old[3];
    newparam->fbposres.pos0[YY] = old[4];
    newparam->fbposres.pos0[ZZ] = old[5];
    break;
  case F_DISRES:
    newparam->disres.label = round_check(old[0],0,ftype,"label");
    newparam->disres.type  = round_check(old[1],1,ftype,"type'");
    newparam->disres.low   = old[2];
    newparam->disres.up1   = old[3];
    newparam->disres.up2   = old[4];
    newparam->disres.kfac  = old[5];
    break;
  case F_ORIRES:
    newparam->orires.ex    = round_check(old[0],1,ftype,"experiment") - 1;
    newparam->orires.label = round_check(old[1],1,ftype,"label");
    newparam->orires.power = round_check(old[2],0,ftype,"power");
    newparam->orires.c     = old[3];
    newparam->orires.obs   = old[4];
    newparam->orires.kfac  = old[5];
    break;
  case F_DIHRES:
    newparam->dihres.phiA  = old[0];
    newparam->dihres.dphiA = old[1];
    newparam->dihres.kfacA = old[2];
    newparam->dihres.phiB   = old[3];
    newparam->dihres.dphiB  = old[4];
    newparam->dihres.kfacB  = old[5];
    break;
  case F_RBDIHS:
    for (i=0; (i<NR_RBDIHS); i++) {
      newparam->rbdihs.rbcA[i]=old[i]; 
      newparam->rbdihs.rbcB[i]=old[NR_RBDIHS+i]; 
    }
    break;
  case F_FOURDIHS:
    /* Read the dihedral parameters to temporary arrays,
     * and convert them to the computationally faster
     * Ryckaert-Bellemans form.
     */   
    /* Use conversion formula for OPLS to Ryckaert-Bellemans: */
    newparam->rbdihs.rbcA[0]=old[1]+0.5*(old[0]+old[2]);
    newparam->rbdihs.rbcA[1]=0.5*(3.0*old[2]-old[0]);
    newparam->rbdihs.rbcA[2]=4.0*old[3]-old[1];
    newparam->rbdihs.rbcA[3]=-2.0*old[2];
    newparam->rbdihs.rbcA[4]=-4.0*old[3];
    newparam->rbdihs.rbcA[5]=0.0;

    newparam->rbdihs.rbcB[0]=old[NR_FOURDIHS+1]+0.5*(old[NR_FOURDIHS+0]+old[NR_FOURDIHS+2]);
    newparam->rbdihs.rbcB[1]=0.5*(3.0*old[NR_FOURDIHS+2]-old[NR_FOURDIHS+0]);
    newparam->rbdihs.rbcB[2]=4.0*old[NR_FOURDIHS+3]-old[NR_FOURDIHS+1];
    newparam->rbdihs.rbcB[3]=-2.0*old[NR_FOURDIHS+2];
    newparam->rbdihs.rbcB[4]=-4.0*old[NR_FOURDIHS+3];
    newparam->rbdihs.rbcB[5]=0.0;
    break;    
  case F_CONSTR:
  case F_CONSTRNC:
    newparam->constr.dA = old[0];
    newparam->constr.dB = old[1];
    break;
  case F_SETTLE:
    newparam->settle.doh=old[0];
    newparam->settle.dhh=old[1];
    break;
  case F_VSITE2:
  case F_VSITE3:
  case F_VSITE3FD:
  case F_VSITE3OUT:
  case F_VSITE4FD:
  case F_VSITE4FDN:
    newparam->vsite.a=old[0];
    newparam->vsite.b=old[1];
    newparam->vsite.c=old[2];
    newparam->vsite.d=old[3];
    newparam->vsite.e=old[4];
    newparam->vsite.f=old[5];
    break;
  case F_VSITE3FAD:
    newparam->vsite.a=old[1] * cos(DEG2RAD * old[0]);
    newparam->vsite.b=old[1] * sin(DEG2RAD * old[0]);
    newparam->vsite.c=old[2];
    newparam->vsite.d=old[3];
    newparam->vsite.e=old[4];
    newparam->vsite.f=old[5];
    break;
  case F_VSITEN:
    newparam->vsiten.n = round_check(old[0],1,ftype,"number of atoms");
    newparam->vsiten.a = old[1];
    break;
  case F_CMAP:
    newparam->cmap.cmapA=old[0];
    newparam->cmap.cmapB=old[1];
    break;
  case F_GB12:
  case F_GB13:
  case F_GB14:
    newparam->gb.sar  = old[0];
    newparam->gb.st   = old[1];
    newparam->gb.pi   = old[2];
    newparam->gb.gbr  = old[3];
    newparam->gb.bmlt = old[4];
    break;
  default:
    gmx_fatal(FARGS,"unknown function type %d in %s line %d",
	      ftype,__FILE__,__LINE__);
  }
}