/*! Given a point that has world transform \a toTarget, this computes the 6x6 Jacobian 
    of this joint relative to that point. The Jacobian is either expressed in global
	world coordinates or in the local coordinates of the target.
*/
void
DynJoint::jacobian(transf toTarget, Matrix *J, bool worldCoords)
{
	transf myTran = getPrevTrans() * getPrevLink()->getTran();
	transf T;
	if (worldCoords) {
		// the translation from joint coordinate system to world coordinate system
		T = transf(Quaternion::IDENTITY, toTarget.translation()) * myTran.inverse();
	} else {
		T = toTarget * myTran.inverse();	
	}
	double M[36];
	T.jacobian(M);
	J->copyMatrix(Matrix(M,6,6,true));
}