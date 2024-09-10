FVector FGearVR::GetNeckPosition(const FQuat& CurrentOrientation, const FVector& CurrentPosition, const FVector& PositionScale)
{
	const auto frame = GetFrame();
	if (!frame)
	{
		return FVector::ZeroVector;
	}
	FVector UnrotatedPos = CurrentOrientation.Inverse().RotateVector(CurrentPosition);
	UnrotatedPos.X -= frame->Settings->NeckToEyeInMeters.X * frame->WorldToMetersScale;
	UnrotatedPos.Z -= frame->Settings->NeckToEyeInMeters.Y * frame->WorldToMetersScale;
	return UnrotatedPos;
}