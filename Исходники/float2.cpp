void float2::Orthogonalize(const float2 &a, float2 &b)
{
	assume(!a.IsZero());
	b -= a.Dot(b) / a.Length() * a;
}