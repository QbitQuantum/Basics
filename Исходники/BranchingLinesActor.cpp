void ABranchingLinesActor::CreateSegments()
{
	// We create the branching structure by constantly subdividing a line between two points by creating a new point in the middle.
	// We then take that point and offset it in a random direction, by a random amount defined within limits.
	// Next we take both of the newly created line halves, and subdivide them the same way.
	// Each new midpoint also has a chance to create a new branch
	// TODO This should really be recursive
	Segments.Empty();
	float CurrentBranchOffset = MaxBranchOffset;

	if (bMaxBranchOffsetAsPercentageOfLength)
	{
		CurrentBranchOffset = (Start - End).Size() * (FMath::Clamp(MaxBranchOffset, 0.1f, 100.0f) / 100.0f);
	}

	// Pre-calc a few floats from percentages
	float ChangeOfFork = FMath::Clamp(ChanceOfForkPercentage, 0.0f, 100.0f) / 100.0f;
	float BranchOffsetReductionEachGeneration = FMath::Clamp(BranchOffsetReductionEachGenerationPercentage, 0.0f, 100.0f) / 100.0f;

	// Add the first segment which is simply between the start and end points
	Segments.Add(FBranchSegment(Start, End, TrunkWidth));

	for (int32 iGen = 0; iGen < Iterations; iGen++)
	{
		TArray<FBranchSegment> newGen;

		for (const FBranchSegment& EachSegment : Segments)
		{
			FVector Midpoint = (EachSegment.End + EachSegment.Start) / 2;

			// Offset the midpoint by a random number along the normal
			FVector normal = FVector::CrossProduct(EachSegment.End - EachSegment.Start, OffsetDirections[RngStream.RandRange(0, 1)]);
			normal.Normalize();
			Midpoint += normal * RngStream.RandRange(-CurrentBranchOffset, CurrentBranchOffset);

			 // Create two new segments
			newGen.Add(FBranchSegment(EachSegment.Start, Midpoint, EachSegment.Width, EachSegment.ForkGeneration));
			newGen.Add(FBranchSegment(Midpoint, EachSegment.End, EachSegment.Width, EachSegment.ForkGeneration));

			// Chance of fork?
			if (RngStream.FRand() > (1 - ChangeOfFork))
			{
				// TODO Normalize the direction vector and calculate a new total length and then subdiv that for X generations
				FVector direction = Midpoint - EachSegment.Start;
				FVector splitEnd = (direction * RngStream.FRandRange(ForkLengthMin, ForkLengthMax)).RotateAngleAxis(RngStream.FRandRange(ForkRotationMin, ForkRotationMax), OffsetDirections[RngStream.RandRange(0, 1)]) + Midpoint;
				newGen.Add(FBranchSegment(Midpoint, splitEnd, EachSegment.Width * WidthReductionOnFork, EachSegment.ForkGeneration + 1));
			}
		}

		Segments.Empty();
		Segments = newGen;

		// Reduce the offset slightly each generation
		CurrentBranchOffset = CurrentBranchOffset * BranchOffsetReductionEachGeneration;
	}
}