void P_RunEffect (AActor *actor, int effects)
{
	DAngle moveangle = actor->Vel.Angle();

	FParticle *particle;
	int i;

	if ((effects & FX_ROCKET) && (cl_rockettrails & 1))
	{
		// Rocket trail
		double backx = -actor->radius * 2 * moveangle.Cos();
		double backy = -actor->radius * 2 * moveangle.Sin();
		double backz = actor->Height * ((2. / 3) - actor->Vel.Z / 8);

		DAngle an = moveangle + 90.;
		double speed;

		particle = JitterParticle (actor->Level, 3 + (M_Random() & 31));
		if (particle) {
			double pathdist = M_Random() / 256.;
			DVector3 pos = actor->Vec3Offset(
				backx - actor->Vel.X * pathdist,
				backy - actor->Vel.Y * pathdist,
				backz - actor->Vel.Z * pathdist);
			particle->Pos = pos;
			speed = (M_Random () - 128) * (1./200);
			particle->Vel.X += speed * an.Cos();
			particle->Vel.Y += speed * an.Sin();
			particle->Vel.Z -= 1./36;
			particle->Acc.Z -= 1./20;
			particle->color = yellow;
			particle->size = 2;
		}
		for (i = 6; i; i--) {
			FParticle *particle = JitterParticle (actor->Level, 3 + (M_Random() & 31));
			if (particle) {
				double pathdist = M_Random() / 256.;
				DVector3 pos = actor->Vec3Offset(
					backx - actor->Vel.X * pathdist,
					backy - actor->Vel.Y * pathdist,
					backz - actor->Vel.Z * pathdist + (M_Random() / 64.));
				particle->Pos = pos;

				speed = (M_Random () - 128) * (1./200);
				particle->Vel.X += speed * an.Cos();
				particle->Vel.Y += speed * an.Sin();
				particle->Vel.Z += 1. / 80;
				particle->Acc.Z += 1. / 40;
				if (M_Random () & 7)
					particle->color = grey2;
				else
					particle->color = grey1;
				particle->size = 3;
			} else
				break;
		}
	}
	if ((effects & FX_GRENADE) && (cl_rockettrails & 1))
	{
		// Grenade trail

		DVector3 pos = actor->Vec3Angle(-actor->radius * 2, moveangle, -actor->Height * actor->Vel.Z / 8 + actor->Height * (2. / 3));

		P_DrawSplash2 (actor->Level, 6, pos, moveangle + 180, 2, 2);
	}
	if (actor->fountaincolor)
	{
		// Particle fountain

		static const int *fountainColors[16] = 
			{ &black,	&black,
			  &red,		&red1,
			  &green,	&green1,
			  &blue,	&blue1,
			  &yellow,	&yellow1,
			  &purple,	&purple1,
			  &black,	&grey3,
			  &grey4,	&white
			};
		int color = actor->fountaincolor*2;
		MakeFountain (actor, *fountainColors[color], *fountainColors[color+1]);
	}
	if (effects & FX_RESPAWNINVUL)
	{
		// Respawn protection

		static const int *protectColors[2] = { &yellow1, &white };

		for (i = 3; i > 0; i--)
		{
			particle = JitterParticle (actor->Level, 16);
			if (particle != NULL)
			{
				DAngle ang = M_Random() * (360 / 256.);
				DVector3 pos = actor->Vec3Angle(actor->radius, ang, 0);
				particle->Pos = pos;
				particle->color = *protectColors[M_Random() & 1];
				particle->Vel.Z = 1;
				particle->Acc.Z = M_Random () / 512.;
				particle->size = 1;
				if (M_Random () < 128)
				{ // make particle fall from top of actor
					particle->Pos.Z += actor->Height;
					particle->Vel.Z = -particle->Vel.Z;
					particle->Acc.Z = -particle->Acc.Z;
				}
			}
		}
	}
}