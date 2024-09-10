//------------------------------------------------------------------------
void CMelee::Hit(geom_contact *contact, const Vec3 &dir, float damageScale, bool remote)
{
	CActor *pOwner = m_pWeapon->GetOwnerActor();

	if (!pOwner)
	{
		return;
	}

	Vec3 view(0.0f, 1.0f, 0.0f);

	if (IMovementController *pMC = pOwner->GetMovementController())
	{
		SMovementState state;
		pMC->GetMovementState(state);
		view = state.eyeDirection;
	}

	// some corrections to make sure the impulse is always away from the camera, and is not a backface collision
	bool backface = dir.Dot(contact->n) > 0;
	bool away = dir.Dot(view.normalized()) > 0; // away from cam?
	Vec3 normal = contact->n;
	Vec3 ndir = dir;

	if (backface)
	{
		if (away)
		{
			normal = -normal;
		}
		else
		{
			ndir = -dir;
		}
	}
	else
	{
		if (!away)
		{
			ndir = -dir;
			normal = -normal;
		}
	}

	IPhysicalEntity *pCollider = gEnv->pPhysicalWorld->GetPhysicalEntityById(contact->iPrim[0]);
	Hit(contact->pt, ndir, normal, pCollider, contact->iPrim[1], 0, contact->id[1], damageScale, remote);
}