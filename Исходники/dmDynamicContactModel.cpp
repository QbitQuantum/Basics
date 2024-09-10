void getRotationMatrix(const Vector3F &z_ICS, const Vector3F &n_ICS, Matrix3F & ICS_R_patch)
{
	// z_ICS and n_ICS has to be normalized already !
	Float cosTheta = z_ICS.dot(n_ICS);
	Float Theta = acos(cosTheta);
	Float sinTheta = sin(Theta);

	if(Theta > 0) 
	{	
		Vector3F rotAxis_ICS; 
		rotAxis_ICS<< -n_ICS(1)/sinTheta, n_ICS(0)/sinTheta, 0;
		rotAxis_ICS.normalize();

		ICS_R_patch = Matrix3F::Identity()+ sinTheta*cr3(rotAxis_ICS) + (1-cosTheta)*cr3(rotAxis_ICS)*cr3(rotAxis_ICS);
	}
	else
	{
		ICS_R_patch = Matrix3F::Identity();
	}
}