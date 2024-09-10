float vParticleImpulseGen::GetImpulse( vParticle *parent )
{
	Assert( parent != NULL );

	float val = 0;

	switch ( mode )
	{
	case PARTICLEIMPULSEGENERATOR_FRAMETIME:
		val = CFrameTimeHelper::GetFrameTime() * impulse_multiplier;
		break;
	case PARTICLEIMPULSEGENERATOR_LIFETIME_LINEAR:
		val = NORMALIZE( ( CFrameTimeHelper::GetCurrentTime() - parent->GetCreationTime() ) / parent->GetLifeDuration() ) * impulse_multiplier;
		break;
	case PARTICLEIMPULSEGENERATOR_LIFETIME_SINE:
		val = NORMALIZE( ( CFrameTimeHelper::GetCurrentTime() - parent->GetCreationTime() ) / parent->GetLifeDuration() );
		val = NORMALIZE( abs( sin( M_PI_F * val * impulse_multiplier ) ) );
		break;
	case PARTICLEIMPULSEGENERATOR_VELOCITY_LINEAR:
		val = parent->vecVelocity.Length() * impulse_multiplier;
		break;
	case PARTICLEIMPULSEGENERATOR_ANGULAR_VELOCITY_LINEAR:
		val = abs( parent->flAngularVelocity ) * impulse_multiplier;
		break;
	case PARTICLEIMPULSEGENERATOR_CURTIME_SINE:
		val = NORMALIZE( abs( sin( M_PI_F * CFrameTimeHelper::GetCurrentTime() * impulse_multiplier ) ) );
		break;
	case PARTICLEIMPULSEGENERATOR_CURTIME_SINE_SIGNED:
		val = ( ( sin( M_PI_F * CFrameTimeHelper::GetCurrentTime() * impulse_multiplier ) ) );
		break;
	default:
		Assert(0);
		break;
	}

	Assert( IsFinite(val) );

	float sign = Sign( val );
	val = sign * Bias( abs(val), impulse_bias );

	val = RemapVal( val, 0.0f, 1.0f, reference_min, reference_max );

	return val;
}