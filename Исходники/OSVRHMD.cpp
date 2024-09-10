void FOSVRHMD::ApplyHmdRotation(APlayerController* PC, FRotator& ViewRotation)
{
    ViewRotation.Normalize();

    FQuat lastHmdOrientation, hmdOrientation;
    FVector lastHmdPosition, hmdPosition;
    UpdateHeadPose(lastHmdOrientation, lastHmdPosition, hmdOrientation, hmdPosition);

    const FRotator DeltaRot = ViewRotation - PC->GetControlRotation();
    DeltaControlRotation = (DeltaControlRotation + DeltaRot).GetNormalized();

    // Pitch from other sources is never good, because there is an absolute up and down that must be respected to avoid motion sickness.
    // Same with roll. Retain yaw by default - mouse/controller based yaw movement still isn't pleasant, but
    // it's necessary for sitting VR experiences.
    DeltaControlRotation.Pitch = 0;
    DeltaControlRotation.Roll = 0;
    DeltaControlOrientation = DeltaControlRotation.Quaternion();

    ViewRotation = FRotator(DeltaControlOrientation * hmdOrientation);
}