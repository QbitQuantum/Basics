void
plane::
setNormPt ( const vec3& norm, const vec3& ptOnplane )
{
	offset = norm.dot ( ptOnplane );
	normal = norm;
}