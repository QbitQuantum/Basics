void CCMiscTools::ComputeBaseVectors(const CCVector3d &N, CCVector3d& X, CCVector3d& Y)
{
	CCVector3d Nunit = N;
	Nunit.normalize();

	//we create a first vector orthogonal to the input one
	X = Nunit.orthogonal(); //X is also normalized

	//we deduce the orthogonal vector to the input one and X
	Y = N.cross(X);
	//Y.normalize(); //should already be normalized!
}