Matrix3d ConsState::strainTensor(Matrix3d F)
{
	Matrix3d G = (F.inverse().transpose())*(F.inverse());	
	return G;
}