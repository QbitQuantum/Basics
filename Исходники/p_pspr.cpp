void P_BobWeapon (player_t *player, float *x, float *y, double ticfrac)
{
	static float curbob;
	double xx[2], yy[2];

	AWeapon *weapon;
	float bobtarget;

	weapon = player->ReadyWeapon;

	if (weapon == nullptr || weapon->WeaponFlags & WIF_DONTBOB)
	{
		*x = *y = 0;
		return;
	}

	// [XA] Get the current weapon's bob properties.
	int bobstyle = weapon->BobStyle;
	float BobSpeed = (weapon->BobSpeed * 128);
	float Rangex = weapon->BobRangeX;
	float Rangey = weapon->BobRangeY;

	for (int i = 0; i < 2; i++)
	{
		// Bob the weapon based on movement speed. ([SP] And user's bob speed setting)
		FAngle angle = (BobSpeed * player->userinfo.GetWBobSpeed() * 35 /
			TICRATE*(level.time - 1 + i)) * (360.f / 8192.f);

		// [RH] Smooth transitions between bobbing and not-bobbing frames.
		// This also fixes the bug where you can "stick" a weapon off-center by
		// shooting it when it's at the peak of its swing.
		bobtarget = float((player->WeaponState & WF_WEAPONBOBBING) ? player->bob : 0.);
		if (curbob != bobtarget)
		{
			if (fabsf(bobtarget - curbob) <= 1)
			{
				curbob = bobtarget;
			}
			else
			{
				float zoom = MAX(1.f, fabsf(curbob - bobtarget) / 40);
				if (curbob > bobtarget)
				{
					curbob -= zoom;
				}
				else
				{
					curbob += zoom;
				}
			}
		}

		if (curbob != 0)
		{
			float bobx = float(player->bob * Rangex);
			float boby = float(player->bob * Rangey);
			switch (bobstyle)
			{
			case AWeapon::BobNormal:
				xx[i] = bobx * angle.Cos();
				yy[i] = boby * fabsf(angle.Sin());
				break;

			case AWeapon::BobInverse:
				xx[i] = bobx*angle.Cos();
				yy[i] = boby * (1.f - fabsf(angle.Sin()));
				break;

			case AWeapon::BobAlpha:
				xx[i] = bobx * angle.Sin();
				yy[i] = boby * fabsf(angle.Sin());
				break;

			case AWeapon::BobInverseAlpha:
				xx[i] = bobx * angle.Sin();
				yy[i] = boby * (1.f - fabsf(angle.Sin()));
				break;

			case AWeapon::BobSmooth:
				xx[i] = bobx*angle.Cos();
				yy[i] = 0.5f * (boby * (1.f - ((angle * 2).Cos())));
				break;

			case AWeapon::BobInverseSmooth:
				xx[i] = bobx*angle.Cos();
				yy[i] = 0.5f * (boby * (1.f + ((angle * 2).Cos())));
			}
		}
		else
		{
			xx[i] = 0;
			yy[i] = 0;
		}
	}
	*x = (float)(xx[0] * (1. - ticfrac) + xx[1] * ticfrac);
	*y = (float)(yy[0] * (1. - ticfrac) + yy[1] * ticfrac);
}