	Vector2 Flee::CalcVelocity()
	{
		Vector2 v = mActor->GetPosition() - mTarget;
		v.Normalize();
		v = mActor->GetMaxVelocity() * v;
		v -= mActor->GetVelocity();

		return v;
	}