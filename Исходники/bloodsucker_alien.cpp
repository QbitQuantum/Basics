BOOL CAlienEffectorPP::Process(SPPInfo& pp)
{
	inherited::Process(pp);

	if (fsimilar(factor, target_factor)) {
		target_factor = (target_factor > 0.5f) ? .3f : .6f;
	}
	
	def_lerp			(factor,target_factor, PERIOD_SPEED, Device.fTimeDelta);
	pp.lerp				(pp_identity,state,factor);

	return TRUE;
}