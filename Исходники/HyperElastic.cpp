/*  Given matrix of incremental deformation dF = exp(dt*grad v), increment particle strain,
        rotation, and LeftCauchy Green strain (latter is assumed to be stored in the particle's
        plastic strain tensor (which is accessed also with GetAltStrainTensor().
    New new F is dF.F, which is used to find new strain
    New B = dF.(Old B).dF^T
    Returns |dF|
*/
double HyperElastic::IncrementDeformation(MPMBase *mptr,Matrix3 du,Tensor *Btrial,int np) const
{
    // get incremental deformation gradient
	const Matrix3 dF = du.Exponential(incrementalDefGradTerms);
	
	// current deformation gradient
	Matrix3 pF = mptr->GetDeformationGradientMatrix();
	
	// new deformation matrix
	const Matrix3 F = dF*pF;
    mptr->SetDeformationGradientMatrix(F);
	
    // increment Left Cauchy tensor B = F.F^T = dF.old B.dF^T
    // plain stress will need to update B.zz when known
    Matrix3 pBold = mptr->GetElasticLeftCauchyMatrix();
    
    // elements of dF.B
    Matrix3 dFoldB = dF*pBold;
    
    // return trial B (if provided) or store new B on the particle
    Tensor *pB = Btrial!=NULL ? Btrial : mptr->GetAltStrainTensor() ;
    pB->xx = dFoldB(0,0)*dF(0,0) + dFoldB(0,1)*dF(0,1) + dFoldB(0,2)*dF(0,2);
    pB->xy = dFoldB(0,0)*dF(1,0) + dFoldB(0,1)*dF(1,1) + dFoldB(0,2)*dF(1,2);
    
    pB->yy = dFoldB(1,0)*dF(1,0) + dFoldB(1,1)*dF(1,1) + dFoldB(1,2)*dF(1,2);
    
    pB->zz = dFoldB(2,0)*dF(2,0) + dFoldB(2,1)*dF(2,1) + dFoldB(2,2)*dF(2,2);
    
    if(np == THREED_MPM)
    {   pB->xz = dFoldB(0,0)*dF(2,0) + dFoldB(0,1)*dF(2,1) + dFoldB(0,2)*dF(2,2);
        pB->yz = dFoldB(1,0)*dF(2,0) + dFoldB(1,1)*dF(2,1) + dFoldB(1,2)*dF(2,2);
    }
    
    // return |dF|
    return dF.determinant();
}