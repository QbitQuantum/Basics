void SoundSource3D::SetAngleAttenuation(float innerAngle, float outerAngle)
{
    innerAngle_ = Clamp(innerAngle, 0.0f, DEFAULT_ANGLE);
    outerAngle_ = Clamp(outerAngle, 0.0f, DEFAULT_ANGLE);
    MarkNetworkUpdate();
}