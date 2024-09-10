void DrawDebugDirectionalArrow(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
{
	// no debug line drawing on dedicated server
	if (GEngine->GetNetMode(InWorld) != NM_DedicatedServer)
	{
		if (ArrowSize <= 0)
		{
			ArrowSize = 10.f;
		}

		DrawDebugLine(InWorld, LineStart, LineEnd, Color, bPersistentLines, LifeTime);

		FVector Dir = (LineEnd-LineStart);
		Dir.Normalize();
		FVector Up(0, 0, 1);
		FVector Right = Dir ^ Up;
		if (!Right.IsNormalized())
		{
			Dir.FindBestAxisVectors(Up, Right);
		}
		FVector Origin = FVector::ZeroVector;
		FMatrix TM;
		// get matrix with dir/right/up
		TM.SetAxes(&Dir, &Right, &Up, &Origin);

		// since dir is x direction, my arrow will be pointing +y, -x and -y, -x
		float ArrowSqrt = FMath::Sqrt(ArrowSize);
		FVector ArrowPos;
		DrawDebugLine(InWorld, LineEnd, LineEnd + TM.TransformPosition(FVector(-ArrowSqrt, ArrowSqrt, 0)), Color, bPersistentLines, LifeTime, DepthPriority);
		DrawDebugLine(InWorld, LineEnd, LineEnd + TM.TransformPosition(FVector(-ArrowSqrt, -ArrowSqrt, 0)), Color, bPersistentLines, LifeTime, DepthPriority);
	}
}