void CCollisionRay::setDirection( const SVector3& direction ) 
{
	SVector3 d = direction;
	d.normalize();
	mRay.mDir = convert( d ); 
}