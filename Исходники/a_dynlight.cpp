//==========================================================================
//
//
//
//==========================================================================
void ADynamicLight::UpdateLocation()
{
	double oldx= X();
	double oldy= Y();
	double oldradius= radius;
	float intensity;

	if (IsActive())
	{
		if (target)
		{
			DAngle angle = target->Angles.Yaw;
			double s = angle.Sin();
			double c = angle.Cos();

			DVector3 pos = target->Vec3Offset(m_off.X * c + m_off.Y * s, m_off.X * s - m_off.Y * c, m_off.Z + target->GetBobOffset());
			SetXYZ(pos); // attached lights do not need to go into the regular blockmap
			Prev = target->Pos();
			subsector = R_PointInSubsector(Prev);
			Sector = subsector->sector;
		}


		// The radius being used here is always the maximum possible with the
		// current settings. This avoids constant relinking of flickering lights

		if (lighttype == FlickerLight || lighttype == RandomFlickerLight || lighttype == PulseLight)
		{
			intensity = float(MAX(m_Radius[0], m_Radius[1]));
		}
		else
		{
			intensity = m_currentRadius;
		}
		radius = intensity * 2.0f * gl_lights_size;

		if (X() != oldx || Y() != oldy || radius != oldradius)
		{
			//Update the light lists
			LinkLight();
		}
	}
}