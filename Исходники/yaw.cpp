void AirframeClass::YawIt(float betcmd, float dt)
{
	// JB 010714 mult by the momentum
	beta   = Math.FLTust(betcmd ,ty02 * auxaeroData->yawMomentum,dt,oldy03);

	if(beta < -180.0F)
	{
		oldy03[0] += 360.0F;
		oldy03[1] += 360.0F;
		oldy03[2] += 360.0F;
		oldy03[3] += 360.0F;
	}
	else if(beta > 180.0F)
	{
		oldy03[0] -= 360.0F;
		oldy03[1] -= 360.0F;
		oldy03[2] -= 360.0F;
		oldy03[3] -= 360.0F;
	}


	ShiAssert(!_isnan(beta));
}