bool EV_Teleport (int tid, int tag, line_t *line, int side, AActor *thing, int flags)
{
	AActor *searcher;
	double z;
	DAngle angle = 0.;
	double s = 0, c = 0;
	double vx = 0, vy = 0;
	DAngle badangle = 0.;

	if (thing == NULL)
	{ // Teleport function called with an invalid actor
		return false;
	}
	bool predicting = (thing->player && (thing->player->cheats & CF_PREDICTING));
	if (thing->flags2 & MF2_NOTELEPORT)
	{
		return false;
	}
	if (side != 0)
	{ // Don't teleport if hit back of line, so you can get out of teleporter.
		return 0;
	}
	searcher = SelectTeleDest(tid, tag, predicting);
	if (searcher == NULL)
	{
		return false;
	}
	// [RH] Lee Killough's changes for silent teleporters from BOOM
	if ((flags & (TELF_ROTATEBOOM|TELF_ROTATEBOOMINVERSE)) && line)
	{
		// Get the angle between the exit thing and source linedef.
		// Rotate 90 degrees, so that walking perpendicularly across
		// teleporter linedef causes thing to exit in the direction
		// indicated by the exit thing.
		angle = line->Delta().Angle() - searcher->Angles.Yaw + 90.;
		if (flags & TELF_ROTATEBOOMINVERSE) angle = -angle;

		// Sine, cosine of angle adjustment
		s = angle.Sin();
		c = angle.Cos();

		// Velocity of thing crossing teleporter linedef
		vx = thing->Vel.X;
		vy = thing->Vel.Y;

		z = searcher->Z();
	}
	else if (searcher->IsKindOf (PClass::FindClass(NAME_TeleportDest2)))
	{
		z = searcher->Z();
	}
	else
	{
		z = ONFLOORZ;
	}
	if ((i_compatflags2 & COMPATF2_BADANGLES) && (thing->player != NULL))
	{
		badangle = 0.01;
	}
	if (P_Teleport (thing, DVector3(searcher->Pos(), z), searcher->Angles.Yaw + badangle, flags))
	{
		// [RH] Lee Killough's changes for silent teleporters from BOOM
		if (line)
		{
			if (flags & (TELF_ROTATEBOOM| TELF_ROTATEBOOMINVERSE))
			{
				// Rotate thing according to difference in angles (or not - Boom got the direction wrong here.)
				thing->Angles.Yaw += angle;

				// Rotate thing's velocity to come out of exit just like it entered
				thing->Vel.X = vx*c - vy*s;
				thing->Vel.Y = vy*c + vx*s;
			}
		}
		if (vx == 0 && vy == 0 && thing->player != NULL && thing->player->mo == thing && !predicting)
		{
			thing->player->mo->PlayIdle ();
		}
		return true;
	}
	return false;
}