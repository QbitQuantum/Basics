void getcenterpoint()
{
	VectorXd dlambda;
	dlambda = (A.transpose()*A).inverse()*(A.transpose()*dB);

	a1 = a1 + dlambda[0];
	xx0 = xx0 + dlambda[1];
	yy0 = yy0 + dlambda[2];
	sigma = sigma + dlambda[3];
}