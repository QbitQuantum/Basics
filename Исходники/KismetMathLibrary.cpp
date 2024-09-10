FRotator UKismetMathLibrary::NegateRotator( FRotator A )
{
	FQuat AQuat = FQuat(A);
	return FRotator(AQuat.Inverse());
}