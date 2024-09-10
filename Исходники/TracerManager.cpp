//------------------------------------------------------------------------
void CTracer::Reset(const Vec3 &pos, const Vec3 &dest)
{
	m_pos.zero();
	m_dest.zero();
	m_startingPos=pos;
	m_age=0.0f;
	m_lifeTime=1.5f;
	m_tracerFlags &= ~kTracerFlag_scaleToDistance;
	m_startFadeOutTime = 0.0f;
	m_slideFrac = 0.f;

	if (IEntity *pEntity=gEnv->pEntitySystem->GetEntity(m_entityId))
	{
		pEntity->FreeSlot(TRACER_GEOM_SLOT);
		pEntity->FreeSlot(TRACER_FX_SLOT);

		Vec3 dir = dest - pos;
		dir.Normalize();

		Matrix34 tm;
		
		tm.SetIdentity();

		if(!dir.IsZero())
		{
			tm = Matrix33::CreateRotationVDir(dir);
		}
		
		tm.AddTranslation(pos);
		pEntity->SetWorldTM(tm);
	}
}