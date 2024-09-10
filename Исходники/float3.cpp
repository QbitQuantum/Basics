float MUST_USE_RESULT float3::ScalarTripleProduct(const float3 &u, const float3 &v, const float3 &w)
{
	return u.Cross(v).Dot(w);
}