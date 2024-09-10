	Vector2 Evasion::CalcVelocity()
	{
		Vector2 offset = mActor->GetPosition()  - mTarget->GetPosition();
		float distance = offset.Length();
		float timeInterval = std::min(0.1f, distance / mActor->GetMaxVelocity());
		Vector2 v = mActor->GetPosition() - mTarget->PredictFuturePosition(timeInterval); // Inefficient!!!

		v.Normalize();
		v = mActor->GetMaxVelocity() * v;
		v -= mActor->GetVelocity();

		// Limit
		v.Normalize();
		v = mActor->GetMaxVelocity() * v;

		return v;
	}