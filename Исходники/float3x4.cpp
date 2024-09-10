void float3x4::Decompose(float3 &translate, Quat &rotate, float3 &scale) const
{
	assume(this->IsColOrthogonal());

	float3x3 r;
	Decompose(translate, r, scale);
	rotate = Quat(r);

	// Test that composing back yields the original float3x4.
	assume(float3x4::FromTRS(translate, rotate, scale).Equals(*this, 0.1f));
}