void CEFX::SetAirAbsorptionFactor(ALfloat value)
{
	airAbsorptionFactor = Clamp(value, AL_MIN_AIR_ABSORPTION_FACTOR, AL_MAX_AIR_ABSORPTION_FACTOR);
}