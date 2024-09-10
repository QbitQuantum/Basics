void FSpriteSelectedShape::ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, FWidget::EWidgetMode MoveMode)
{
	if (Geometry.Shapes.IsValidIndex(ShapeIndex))
	{
		FSpriteGeometryShape& Shape = Geometry.Shapes[ShapeIndex];

		const bool bDoRotation = (MoveMode == FWidget::WM_Rotate) || (MoveMode == FWidget::WM_TranslateRotateZ);
		const bool bDoTranslation = (MoveMode == FWidget::WM_Translate) || (MoveMode == FWidget::WM_TranslateRotateZ);
		const bool bDoScale = MoveMode == FWidget::WM_Scale;

		if (bDoTranslation)
		{
			const FVector WorldSpaceDelta = (PaperAxisX * Delta.X) + (PaperAxisY * Delta.Y);
			const FVector2D TextureSpaceDelta = EditorContext->SelectedItemConvertWorldSpaceDeltaToLocalSpace(WorldSpaceDelta);

			Shape.BoxPosition += TextureSpaceDelta;

			Geometry.GeometryType = ESpritePolygonMode::FullyCustom;
		}

		if (bDoScale)
		{
			const float ScaleDeltaX = FVector::DotProduct(Scale3D, PaperAxisX);
			const float ScaleDeltaY = FVector::DotProduct(Scale3D, PaperAxisY);

			const FVector2D OldSize = Shape.BoxSize;
			const FVector2D NewSize(OldSize.X + ScaleDeltaX, OldSize.Y + ScaleDeltaY);

			if (!FMath::IsNearlyZero(NewSize.X, KINDA_SMALL_NUMBER) && !FMath::IsNearlyZero(NewSize.Y, KINDA_SMALL_NUMBER))
			{
				const FVector2D ScaleFactor(NewSize.X / OldSize.X, NewSize.Y / OldSize.Y);
				Shape.BoxSize = NewSize;

				// Now apply it to the verts
				for (FVector2D& Vertex : Shape.Vertices)
				{
					Vertex.X *= ScaleFactor.X;
					Vertex.Y *= ScaleFactor.Y;
				}

				Geometry.GeometryType = ESpritePolygonMode::FullyCustom;
			}
		}

		if (bDoRotation)
		{
			//@TODO: This stuff should probably be wrapped up into a utility method (also used for socket editing)
			const FRotator CurrentRot(Shape.Rotation, 0.0f, 0.0f);
			FRotator SocketWinding;
			FRotator SocketRotRemainder;
			CurrentRot.GetWindingAndRemainder(SocketWinding, SocketRotRemainder);

			const FQuat ActorQ = SocketRotRemainder.Quaternion();
			const FQuat DeltaQ = Rotation.Quaternion();
			const FQuat ResultQ = DeltaQ * ActorQ;
			const FRotator NewSocketRotRem = FRotator(ResultQ);
			FRotator DeltaRot = NewSocketRotRem - SocketRotRemainder;
			DeltaRot.Normalize();

			const FRotator NewRotation(CurrentRot + DeltaRot);

			Shape.Rotation = NewRotation.Pitch;
			Geometry.GeometryType = ESpritePolygonMode::FullyCustom;
		}
	}
}