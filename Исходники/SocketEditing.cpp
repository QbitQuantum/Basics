void FSpriteSelectedSocket::ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, FWidget::EWidgetMode MoveMode)
{
	if (UPrimitiveComponent* PreviewComponent = PreviewComponentPtr.Get())
	{
		UObject* AssociatedAsset = const_cast<UObject*>(PreviewComponent->AdditionalStatObject());
		if (UPaperSprite* Sprite = Cast<UPaperSprite>(AssociatedAsset))
		{
			if (FPaperSpriteSocket* Socket = Sprite->FindSocket(SocketName))
			{
				const bool bDoRotation = (MoveMode == FWidget::WM_Rotate) || (MoveMode == FWidget::WM_TranslateRotateZ);
				const bool bDoTranslation = (MoveMode == FWidget::WM_Translate) || (MoveMode == FWidget::WM_TranslateRotateZ);
				const bool bDoScale = MoveMode == FWidget::WM_Scale;

				if (bDoTranslation)
				{
					//@TODO: Currently sockets are in unflipped pivot space,
					const FVector Delta3D_UU = (PaperAxisX * Delta.X) + (PaperAxisY * -Delta.Y);
					const FVector Delta3D = Delta3D_UU * Sprite->GetPixelsPerUnrealUnit();
					Socket->LocalTransform.SetLocation(Socket->LocalTransform.GetLocation() + Delta3D);
				}

				if (bDoRotation)
				{
					const FRotator CurrentRot = Socket->LocalTransform.GetRotation().Rotator();
					FRotator SocketWinding;
					FRotator SocketRotRemainder;
					CurrentRot.GetWindingAndRemainder(SocketWinding, SocketRotRemainder);

					const FQuat ActorQ = SocketRotRemainder.Quaternion();
					const FQuat DeltaQ = Rotation.Quaternion();
					const FQuat ResultQ = DeltaQ * ActorQ;
					const FRotator NewSocketRotRem = FRotator( ResultQ );
					FRotator DeltaRot = NewSocketRotRem - SocketRotRemainder;
					DeltaRot.Normalize();

					const FRotator NewRotation(CurrentRot + DeltaRot);
					Socket->LocalTransform.SetRotation(NewRotation.Quaternion());
				}
				
				if (bDoScale)
				{
					const FVector4 LocalSpaceScaleOffset = Socket->LocalTransform.TransformVector(Scale3D);

					Socket->LocalTransform.SetScale3D(Socket->LocalTransform.GetScale3D() + LocalSpaceScaleOffset);
				}
			}
		}
	}
}