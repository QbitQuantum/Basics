bool ActionEffector::SetDashAction(double power, AngleDeg dir)
{
	Assert(dir > -180.0 - FLOAT_EPS && dir < 180.0 + FLOAT_EPS);

	if (mIsDash == true || mIsMutex == true)
	{
		return false;
	}

	power = GetNormalizeDashPower(power);
    dir = GetNormalizeDashAngle(dir);

    // 注意，在rcssserver13.1.0版本下，dash只需要考虑下面四种情况即可：
    // @ -power 0.0
    // @ +power 0.0
    // @ +power 90.0
    // @ +power -90.0
    //
    // from rcssserver13.1.0

    // 注意，在rcssserver v14 下，dash需要考虑的情况包括：
    // @ +power, 0
    // @ +power, 45
    // @ +power, 90
    // @ +power, 135 | -power, -45
    // @ -power, 0 | +power, 180
    // @ +power, -45
    // @ +power, -90
    // @ -power, 45 | +power, -135
    if (ServerParam::instance().dashAngleStep() < FLOAT_EPS )
    {
        // players can dash in any direction.
    }
    else
    {
        // The dash direction is discretized by server::dash_angle_step
        dir = ServerParam::instance().dashAngleStep() * Rint(dir / ServerParam::instance().dashAngleStep());
    }

    TransformDash(power, dir);

	double max_stamina = mSelfState.GetStamina() + mSelfState.GetExtraStamina();
	if (power < 0.0)
	{
		if ((-2.0 * power) > max_stamina)
		{
			power = -max_stamina * 0.5 + FLOAT_EPS;
		}
	}
	else
	{
		if (power > max_stamina)
		{
			power = max_stamina - FLOAT_EPS;
		}
	}

	if (!mAgent.GetSelf().IsOutOfStamina()) {
		power = mAgent.GetSelf().CorrectDashPowerForStamina(power); // 保证不降到最低体力以下
	}

    if (std::fabs(power) < FLOAT_EPS) return false;

    TransformDash(power, dir);

	mDash.Plan(power, dir);
	mDash.Execute(mCommandQueue);
	++mDashCount;
	mIsDash = true;
	mIsMutex = true;
	return true;
}