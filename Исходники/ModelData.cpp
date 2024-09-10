const float TripleProduct( const Vertex& v0, const Vertex& v1, const Vertex& v2 )
{
	Vect vect0( v0.x, v0.y, v0.z );
	Vect vect1( v1.x, v1.y, v1.z );
	Vect vect2( v2.x, v2.y, v2.z );

	Vect a = vect2 - vect0;
	Vect b = vect1 - vect0;

	Vect normal( v0.nx, v0.ny, v0.nz );

	return a.cross( b ).dot( normal );
}