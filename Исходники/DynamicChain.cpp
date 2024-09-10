//B*ddq + C*dq = fext
void DynamicChain2D::GetAcceleration(Vector& ddq, const Vector& fext)
{
	Matrix B;
	GetKineticEnergyMatrix(B);
	CholeskyDecomposition<Real> cholesky;
	if(!cholesky.set(B)) {
		LOG4CXX_ERROR(KrisLibrary::logger(),"Kinetic energy matrix is not positive definite!");
		LOG4CXX_ERROR(KrisLibrary::logger(),B);
		Abort();
	}

	Vector Cdq;
	GetCoriolisForces(Cdq);
	Vector f_Cdq;
	if(fext.n==0) f_Cdq.setNegative(Cdq);
	else f_Cdq.sub(fext,Cdq);
	cholesky.backSub(f_Cdq,ddq);
}