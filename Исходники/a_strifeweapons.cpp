AActor *P_SpawnSubMissile (AActor *source, PClassActor *type, AActor *target)
{
	AActor *other = Spawn (type, source->Pos(), ALLOW_REPLACE);

	if (other == NULL)
	{
		return NULL;
	}

	other->target = target;
	other->Angles.Yaw = source->Angles.Yaw;
	other->VelFromAngle();

	if (other->flags4 & MF4_SPECTRAL)
	{
		if (source->flags & MF_MISSILE && source->flags4 & MF4_SPECTRAL)
		{
			other->FriendPlayer = source->FriendPlayer;
		}
		else
		{
			other->SetFriendPlayer(target->player);
		}
	}

	if (P_CheckMissileSpawn (other, source->radius))
	{
		DAngle pitch = P_AimLineAttack (source, source->Angles.Yaw, 1024.);
		other->Vel.Z = -other->Speed * pitch.Sin();
		return other;
	}
	return NULL;
}