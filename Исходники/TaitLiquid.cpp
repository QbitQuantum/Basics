// Apply Constitutive law, check np to know what type
void TaitLiquid::MPMConstitutiveLaw(MPMBase *mptr,Matrix3 du,double delTime,int np,void *properties,ResidualStrains *res) const
{
#ifdef NO_SHEAR_MODEL
    // get incremental deformation gradient
	const Matrix3 dF = du.Exponential(incrementalDefGradTerms);
    
    // decompose dF into dR and dU
    Matrix3 dR;
    Matrix3 dU = dF.RightDecompose(&dR,NULL);
	
	// current deformation gradient
    double detdF = dF.determinant();
	Matrix3 pF = mptr->GetDeformationGradientMatrix();
    Matrix3 F = dR*pF;
    if(np==THREED_MPM)
        F.Scale(pow(detdF,1./3.));
    else
        F.Scale2D(sqrt(detdF));
	
	// new deformation matrix with volume change onle
    mptr->SetDeformationGradientMatrix(F);
#else

	// Update total deformation gradient, and calculate trial B
	double detdF = IncrementDeformation(mptr,du,NULL,np);
#endif
    
    // Get new J and save result on the particle
	double J = detdF * mptr->GetHistoryDble(J_history);
    mptr->SetHistoryDble(J_history,J);
    
    // account for residual stresses
	double dresStretch,resStretch = GetResidualStretch(mptr,dresStretch,res);
	double Jres = resStretch*resStretch*resStretch;
    double Jeff = J/Jres;

    // new Kirchhoff pressure (over rho0) from Tait equation
	double p0=mptr->GetPressure();
    double pressure = J*TAIT_C*Ksp*(exp((1.-Jeff)/TAIT_C)-1.);
    mptr->SetPressure(pressure);
    
	// incremental energy per unit mass - dilational part
    double avgP = 0.5*(p0+pressure);
    double delV = 1. - 1./detdF;
    double workEnergy = -avgP*delV;
    
	// incremental residual energy per unit mass
	double delVres = 1. - 1./(dresStretch*dresStretch*dresStretch);
	double resEnergy = -avgP*delVres;
	
    // viscosity term = 2 eta (0.5(grad v) + 0.5*(grad V)^T - (1/3) tr(grad v) I)
    // (i.e., divatoric part of the symmetric strain tensor, 2 is for conversion to engineering shear strain)
    Matrix3 shear;
    double c[3][3];
    c[0][0] = (2.*du(0,0)-du(1,1)-du(2,2))/3.;
    c[1][1] = (2.*du(1,1)-du(0,0)-du(2,2))/3.;
    c[2][2] = (2.*du(2,2)-du(0,0)-du(1,1))/3.;
    c[0][1] = 0.5*(du(0,1)+du(1,0));
    c[1][0] = c[0][1];
    if(np==THREED_MPM)
    {   c[0][2] = 0.5*(du(0,2)+du(2,0));
        c[2][0] = c[0][2];
        c[1][2] = 0.5*(du(1,2)+du(2,1));
        c[2][1] = c[1][2];
        shear.set(c);
    }
    else
        shear.set(c[0][0],c[0][1],c[1][0],c[1][1],c[2][2]);
    
    // Get Kirchoff shear stress (over rho0)
    shear.Scale(J*TwoEtasp/delTime);
    
    // update deviatoric stress
	Tensor *sp=mptr->GetStressTensor();
    sp->xx = shear(0,0);
    sp->yy = shear(1,1);
    sp->zz = shear(2,2);
    sp->xy = shear(0,1);
    if(np==THREED_MPM)
    {   sp->xz = shear(0,2);
        sp->yz = shear(1,2);
    }
    
    // shear work per unit mass = tau.du = tau.tau*delTime/TwoEtasp
    double shearWork = sp->xx*sp->xx + sp->yy*sp->yy + sp->zz*sp->zz + 2.*sp->xy*sp->xy;
    if(np==THREED_MPM) shearWork += 2.*(sp->xz*sp->xz + sp->yz*sp->yz);
    shearWork *= delTime/TwoEtasp;
    mptr->AddWorkEnergyAndResidualEnergy(workEnergy+shearWork,resEnergy);
    
    // particle isentropic temperature increment dT/T = - J (K/K0) gamma0 Delta(V)/V
    // Delta(V)/V = 1. - 1/detdF (total volume)
	double Kratio = Jeff*(1.+pressure/(TAIT_C*Ksp));
	double dTq0 = -J*Kratio*gamma0*mptr->pPreviousTemperature*delV;
    
    // heat energy is Cv (dT - dTq0) -dPhi
	// Here do Cv (dT - dTq0)
    // dPhi = shearWork is lost due to shear term
    IncrementHeatEnergy(mptr,res->dT,dTq0,shearWork);
}