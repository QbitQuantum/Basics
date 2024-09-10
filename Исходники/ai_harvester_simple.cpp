//
// Event_OnProjectileLaunch()
//
void hhHarvesterSimple::Event_OnProjectileLaunch(hhProjectile *proj) {
	
	// Can't launch again yet
	float min = spawnArgs.GetFloat( "dda_delay_min" );
	float max = spawnArgs.GetFloat( "dda_delay_max" );
	float delay = min + (max - min) * (1.0f - gameLocal.GetDDAValue());

	if(gameLocal.GetTime() - lastAntiProjectileAttack < delay)
		return;	
	
	// The person who launched this projectile wasn't someone to worry about
	if(proj->GetOwner() && !(ReactionTo(proj->GetOwner()) & (ATTACK_ON_SIGHT | ATTACK_ON_DAMAGE)))
		return;
	
	// TODO: more intelligent checks for if we should launch the anti-projectile chaff
	idVec3 fw		= viewAxis[0];
	idVec3 projFw	= proj->GetAxis()[0]; 
	if(proj->GetOwner())
		projFw = proj->GetOwner()->GetAxis()[0];
	float dot = fw * projFw;
	if(dot > -.7f)
		return;

	ProcessEvent(&MA_AntiProjectileAttack, proj);
}