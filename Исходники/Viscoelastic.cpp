/* Take increments in strain and calculate new Particle: strains, rotation strain,
	stresses, strain energy,
	du are (gradient rates X time increment) to give deformation gradient change
	For Axisymmetry: x->R, y->Z, z->theta, np==AXISYMMETRIC_MPM, otherwise dvzz=0
	This material tracks pressure and stores deviatoric stress only in particle stress tensor
 */
void Viscoelastic::MPMConstitutiveLaw(MPMBase *mptr,Matrix3 du,double delTime,int np,void *properties,ResidualStrains *res,int historyOffset) const
{
	// current previous deformation gradient and stretch
	Matrix3 pFnm1 = mptr->GetDeformationGradientMatrix();
	
    // get incremental deformation gradient and decompose it
	const Matrix3 dF = du.Exponential(incrementalDefGradTerms);
    Matrix3 dR;
    Matrix3 dVstretch = dF.LeftDecompose(&dR,NULL);
	
	// decompose to get previous stretch
	Matrix3 Vnm1 = pFnm1.LeftDecompose(NULL,NULL);
	
	// get strain increments de = (dV-I) dR Vnma dRT
	dVstretch(0,0) -= 1.;
	dVstretch(1,1) -= 1.;
	dVstretch(2,2) -= 1.;
	Matrix3 Vrot = Vnm1.RMRT(dR);
	Matrix3 detot = dVstretch*Vrot;
	
	// Update total deformation gradient
	Matrix3 pF = dF*pFnm1;
	mptr->SetDeformationGradientMatrix(pF);
	
    // Effective strain by deducting thermal strain (no shear thermal strain because isotropic)
	double eres=CTE*res->dT;
	if(DiffusionTask::active)
		eres+=CME*res->dC;
	
	// update pressure
	double dTq0 = 0.,dispEnergy = 0.;
	double traceDe = detot.trace();
	double delV = traceDe - 3.*eres;
#ifdef USE_KIRCHOFF_STRESS
	// tracking J
	double detdF = dF.determinant();
	double **h =(double **)(mptr->GetHistoryPtr(0));
	double J = detdF*h[mptrHistory][MGJ_HISTORY];
	h[mptrHistory][MGJ_HISTORY] = J;
	UpdatePressure(mptr,delV,res,eres,detdF,J,delTime,dTq0,dispEnergy);
#else
	UpdatePressure(mptr,delV,res,eres,&dF,delTime,dTq0,dispEnergy);
#endif
	
	// deviatoric strains increment in de
	// Actually de is finding 2*(dev e) to avoid many multiplies by two
	Tensor de;
	double dV = traceDe/3.;
	de.xx = 2.*(detot(0,0) - dV);
	de.yy = 2.*(detot(1,1) - dV);
	de.zz = 2.*(detot(2,2) - dV);
	de.xy = 2.*detot(0,1);
	if(np==THREED_MPM)
	{	de.xz = 2.*detot(0,2);
		de.yz = 2.*detot(1,2);
	}
	
	// Find initial 2*e(t) (deviatoric strain) in ed
	Tensor ed;
	double thirdV = Vrot.trace()/3.;
	ed.xx = 2.*(Vrot(0,0)-thirdV);
	ed.yy = 2.*(Vrot(1,1)-thirdV);
	ed.zz = 2.*(Vrot(2,2)-thirdV);
	ed.xy = 2.*Vrot(0,1);
	if(np==THREED_MPM)
	{	ed.xz = 2.*Vrot(0,2);
		ed.yz = 2.*Vrot(1,2);
	}
	
	// increment particle deviatoric stresses - elastic part
	double dsig[6];
	dsig[XX] = Gered*de.xx;
	dsig[YY] = Gered*de.yy;
	dsig[ZZ] = Gered*de.zz;
	dsig[XY] = Gered*de.xy;
	if(np==THREED_MPM)
	{	dsig[XZ] = Gered*de.xz;
		dsig[YZ] = Gered*de.yz;
	}
	
	// get internal variable increments, update them, add to incremental stress, and get dissipated energy6
	Tensor dak;
    double **ak =(double **)(mptr->GetHistoryPtr(0));
	int k;
    for(k=0;k<ntaus;k++)
    {   double tmp = exp(-delTime/tauk[k]);
		double tmpm1 = tmp-1.;
		double tmpp1 = tmp+1.;
		double arg = 0.25*delTime/tauk[k];					// 0.25 because e's have factor of 2
		dak.xx = tmpm1*ak[XX_HISTORY][k] + arg*(tmpp1*ed.xx + de.xx);
		dak.yy = tmpm1*ak[YY_HISTORY][k] + arg*(tmpp1*ed.yy + de.yy);
		dak.xy = tmpm1*ak[XY_HISTORY][k] + arg*(tmpp1*ed.xy + de.xy);
		dak.zz = tmpm1*ak[ZZ_HISTORY][k] + arg*(tmpp1*ed.zz + de.zz);
		ak[XX_HISTORY][k] += dak.xx;
		ak[YY_HISTORY][k] += dak.yy;
		ak[ZZ_HISTORY][k] += dak.zz;
		ak[XY_HISTORY][k] += dak.xy;
		
		// add to stress increments
		dsig[XX] -= TwoGkred[k]*dak.xx;
		dsig[YY] -= TwoGkred[k]*dak.yy;
		dsig[ZZ] -= TwoGkred[k]*dak.zz;
		dsig[XY] -= TwoGkred[k]*dak.xy;
		
		// dissipation
		dispEnergy += TwoGkred[k]*(dak.xx*(0.5*(ed.xx+0.5*de.xx)-ak[XX_HISTORY][k]+0.5*dak.xx)
								   + dak.yy*(0.5*(ed.yy+0.5*de.yy)-ak[YY_HISTORY][k]+0.5*dak.yy)
								   + dak.zz*(0.5*(ed.zz+0.5*de.zz)-ak[ZZ_HISTORY][k]+0.5*dak.zz)
								   + dak.xy*(0.5*(ed.xy+0.5*de.xy)-ak[XY_HISTORY][k]+0.5*dak.xy));
		
		// extra terms for 3D
		if(np==THREED_MPM)
		{	// internal variables
			dak.xz = tmpm1*ak[XZ_HISTORY][k] + arg*(tmpp1*ed.xz + de.xz);
			dak.yz = tmpm1*ak[YZ_HISTORY][k] + arg*(tmpp1*ed.yz + de.yz);
			ak[XZ_HISTORY][k] += dak.xz;
			ak[YZ_HISTORY][k] += dak.yz;
			
			// stresses
			dsig[XZ] -= TwoGkred[k]*dak.xz;
			dsig[YZ] -= TwoGkred[k]*dak.yz;
			
			// dissipation
			dispEnergy += TwoGkred[k]*(dak.xz*(0.5*(ed.xz+0.5*de.xz)-ak[XZ_HISTORY][k]+0.5*dak.xz)
									   + dak.yz*(0.5*(ed.yz+0.5*de.yz)-ak[YZ_HISTORY][k]+0.5*dak.yz));
		}
	}
	
	// Update particle deviatoric stresses
	Tensor *sp=mptr->GetStressTensor();
	//Tensor st0 = *sp;
	if(np==THREED_MPM)
	{	// incremental rotate of prior stress
		Matrix3 stn(sp->xx,sp->xy,sp->xz,sp->xy,sp->yy,sp->yz,sp->xz,sp->yz,sp->zz);
		Matrix3 str = stn.RMRT(dR);

#ifdef USE_KIRCHOFF_STRESS
		// convert sigma(n)/rho(n) to sigma(n)/rho(n+1) and add dsigma/rho(n+1)
		sp->xx = detdF*str(0,0)+J*dsig[XX];
		sp->yy = detdF*str(1,1)+J*dsig[YY];
		sp->xy = detdF*str(0,1)+J*dsig[XY];
		sp->zz = detdF*str(2,2)+J*dsig[ZZ];
		sp->yz = detdF*str(1,2)+J*dsig[YZ];
		sp->xz = detdF*str(0,2)+J*dsig[XZ];
#else
		sp->xx = str(0,0)+dsig[XX];
		sp->yy = str(1,1)+dsig[YY];
		sp->xy = str(0,1)+dsig[XY];
		sp->zz = str(2,2)+dsig[ZZ];
		sp->yz = str(1,2)+dsig[YZ];
		sp->xz = str(0,2)+dsig[XZ];
#endif
	}
	else
	{	// incremental rotate of prior stress
		Matrix3 stn(sp->xx,sp->xy,sp->xy,sp->yy,sp->zz);
		Matrix3 str = stn.RMRT(dR);
		
#ifdef USE_KIRCHOFF_STRESS
		// convert sigma(n)/rho(n) to sigma(n)/rho(n+1) and add dsigma/rho(n+1)
		sp->xx = detdF*str(0,0)+J*dsig[XX];
		sp->yy = detdF*str(1,1)+J*dsig[YY];
		sp->xy = detdF*str(0,1)+J*dsig[XY];
		sp->zz = detdF*sp->zz+J*dsig[ZZ];
#else
		sp->xx = str(0,0)+dsig[XX];
		sp->yy = str(1,1)+dsig[YY];
		sp->xy = str(0,1)+dsig[XY];
		sp->zz += dsig[ZZ];
#endif
	}
	
	// incremental work energy = shear energy (dilation and residual energy done in update pressure)
    double shearEnergy = sp->xx*detot(0,0) + sp->yy*detot(1,1) + sp->zz*detot(2,2) + sp->xy*de.xy;
    if(np==THREED_MPM)
    {   shearEnergy += sp->xz*de.xz + sp->yz*de.yz;
    }
    mptr->AddWorkEnergyAndResidualEnergy(shearEnergy,0.);
	
    // disispated energy per unit mass (dPhi/(rho0 V0)) (nJ/g)
    mptr->AddPlastEnergy(dispEnergy);
    
    // heat energy is Cv dT - dPhi
    // The dPhi is subtracted here because it will show up in next
    //		time step within Cv dT (if adibatic heating occurs)
    // The Cv dT was done in update pressure
    IncrementHeatEnergy(mptr,res->dT,dTq0,dispEnergy);
}