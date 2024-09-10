cQuaternion cQuaternion::AppliedTo( const cQuaternion& q )
{
	return *this * ( q * Conjugate() );
}