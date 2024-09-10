	Vec2 Min( const Vec2 &A, const Vec2 &B )
	{
		return Vec2( Min( A.X(), B.X() ), Min( A.Y(), B.Y() ) );
	}