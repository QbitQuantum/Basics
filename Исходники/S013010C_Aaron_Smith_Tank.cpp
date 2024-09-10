void S013010C_Aaron_Smith_Tank::CreateStraightFeelers(vector<Vector2D> &feelers)
{
	feelers.clear();

	Vector2D ahead = Vec2DNormalize(mVelocity);
	if (ahead.Length() == 0)
		ahead = mHeading;

	double dynamicLength = mVelocity.Length() / GetMaxSpeed();
	double angle = 70;
	int ahead2Amount = 50;
	int ahead1Amount = ahead2Amount / 2;

	mAhead1Distance = GetCentrePosition() + (ahead * dynamicLength * ahead1Amount);
	mAhead2Distance = GetCentrePosition() + (ahead * dynamicLength * (ahead2Amount + 50));

	feelers.push_back(mAhead1Distance);
	feelers.push_back(mAhead2Distance);
}