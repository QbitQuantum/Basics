IC static void generate_orthonormal_basis1(const Fvector& dir,Fvector& updir, Fvector& right)
{

	right.crossproduct(dir,updir); //. <->
	right.normalize();
	updir.crossproduct(right,dir);
}