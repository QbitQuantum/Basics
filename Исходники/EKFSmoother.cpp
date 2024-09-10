EKFSmoother::EKFSmoother( int n, float q, float r )
	: EKFSmoother( n, Vector4f( q, q, q, q ), Vector4f( r, r, r, r ) )
{
}