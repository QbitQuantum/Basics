void float3x3::Decompose(Quat &rotate, float3 &scale) const
{
    assume(this->IsOrthogonal());

    float3x3 r;
    Decompose(r, scale);
    rotate = Quat(r);

    // Test that composing back yields the original float3x3.
    assume(float3x3::FromRS(rotate, scale).Equals(*this, 0.1f));
}