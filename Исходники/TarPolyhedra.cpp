void Target_Octahedron::GenerateVertices(void)
{
	const real sqrt2 = (real)1. / Sqrt((real)2.);
	const real al = sqrt2 * shpar[0];
 	vertices[0].Set(zero_, zero_,    al);
	vertices[1].Set(   al, zero_, zero_);
	vertices[2].Set(zero_,    al, zero_);
	vertices[3].Set(  -al, zero_, zero_);
	vertices[4].Set(zero_,   -al, zero_);
	vertices[5].Set(zero_, zero_,   -al);
}