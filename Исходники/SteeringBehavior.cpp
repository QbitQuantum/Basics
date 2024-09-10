AVector SteeringBehavior::Seek (APoint toPosition)
{
	AVector desiredVelocity = mActor->GetPosition() - actorPosition;
	desiredVelocity.Normalize();

	desiredVelocity *= mActor->GetMaxSpeed();

	return (desiredVelocity - mActor->GetVelocity());
}