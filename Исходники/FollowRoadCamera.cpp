void AFollowRoadCamera::Tick(float Delta) {
    if (!Running) {
        return;
    }

    if (!Roadmap) {
        return;
    }

    float SpeedCMs = Speed / 0.036;

    float CurrentTime = GetWorld()->GetTimeSeconds();

    float TimePassed = CurrentTime - StartTime;

    float DistancePassed = TimePassed * SpeedCMs;

    if (Rev) {
        DistancePassed = MaxDist - DistancePassed;
    }

    float TValue = SplineInfoDistance.Eval(DistancePassed, 0);

    FVector Location = Roadmap->SplineInfo.Eval(TValue, FVector(0, 0, 0));
    FVector Tangent = Roadmap->SplineInfo.EvalDerivative(TValue, FVector(0, 0, 0)).GetSafeNormal2D();
    FVector Side = FVector::CrossProduct(FVector::UpVector, Tangent);

    Location += Tangent * Offset.X;
    Location += Side * Offset.Y;
    Location += FVector::UpVector * Offset.Z;

    FVector LookAtLocation;

    if (ReplayPlayer && ReplayPlayer->LookAtActor) {
        LookAtLocation = ReplayPlayer->LookAtActor->GetActorLocation();
    }
    else {

        float DistanceLookAt = 0;

        if (Rev) {
            DistanceLookAt = DistancePassed - LookAtDistance;
        }
        else {
            DistanceLookAt = DistancePassed + LookAtDistance;
        }

        float TValueLookAt = SplineInfoDistance.Eval(DistanceLookAt, 0);
        LookAtLocation = Roadmap->SplineInfo.Eval(TValueLookAt, FVector(0, 0, 0));
        FVector LookAtTangent = Roadmap->SplineInfo.EvalDerivative(TValueLookAt, FVector(0, 0, 0)).GetSafeNormal2D();
        FVector LookAtSide = FVector::CrossProduct(FVector::UpVector, LookAtTangent);

        LookAtLocation += LookAtTangent * LookAtOffset.X;
        LookAtLocation += LookAtSide * LookAtOffset.Y;
        LookAtLocation += FVector::UpVector * LookAtOffset.Z;
    }

    FRotator NewRotation = (LookAtLocation - Location).Rotation();
    NewRotation.Pitch += DegreesAboveFollow;

    if (FirstTick) {
        SetActorLocation(Location);
        SetActorRotation(NewRotation);
        FirstTick = false;
        return;
    }

    FVector LastLocation = GetActorLocation();
    FRotator LastRotation = GetActorRotation();
    // Note: This will not work if LastRotation and NewRotation are too far from
    // each other (more than 20 degrees), however, in that case, nothing will
    // work...
    GetNiceRotatorValue(NewRotation, LastRotation);
    NewRotation = NewRotation * (1-FollowSmooth) + LastRotation * FollowSmooth;
    NewRotation.Normalize();
    SetActorLocation(Location * 0.1 + LastLocation * 0.9);
    SetActorRotation(NewRotation);
}