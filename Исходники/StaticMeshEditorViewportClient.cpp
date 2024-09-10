bool FStaticMeshEditorViewportClient::InputWidgetDelta( FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale )
{
	bool bHandled = false;
	if (bManipulating)
	{
		if (CurrentAxis != EAxisList::None)
		{
			UStaticMeshSocket* SelectedSocket = StaticMeshEditorPtr.Pin()->GetSelectedSocket();
			if(SelectedSocket)
			{
				UProperty* ChangedProperty = NULL;
				const FWidget::EWidgetMode MoveMode = GetWidgetMode();
				if(MoveMode == FWidget::WM_Rotate)
				{
					ChangedProperty = FindField<UProperty>( UStaticMeshSocket::StaticClass(), "RelativeRotation" );
					SelectedSocket->PreEditChange(ChangedProperty);

					FRotator CurrentRot = SelectedSocket->RelativeRotation;
					FRotator SocketWinding, SocketRotRemainder;
					CurrentRot.GetWindingAndRemainder(SocketWinding, SocketRotRemainder);

					const FQuat ActorQ = SocketRotRemainder.Quaternion();
					const FQuat DeltaQ = Rot.Quaternion();
					const FQuat ResultQ = DeltaQ * ActorQ;
					const FRotator NewSocketRotRem = FRotator( ResultQ );
					FRotator DeltaRot = NewSocketRotRem - SocketRotRemainder;
					DeltaRot.Normalize();

					SelectedSocket->RelativeRotation += DeltaRot;
					SelectedSocket->RelativeRotation = SelectedSocket->RelativeRotation.Clamp();
				}
				else if(MoveMode == FWidget::WM_Translate)
				{
					ChangedProperty = FindField<UProperty>( UStaticMeshSocket::StaticClass(), "RelativeLocation" );
					SelectedSocket->PreEditChange(ChangedProperty);

					//FRotationMatrix SocketRotTM( SelectedSocket->RelativeRotation );
					//FVector SocketMove = SocketRotTM.TransformVector( Drag );

					SelectedSocket->RelativeLocation += Drag;
				}
				if ( ChangedProperty )
				{			
					FPropertyChangedEvent PropertyChangedEvent( ChangedProperty );
					SelectedSocket->PostEditChangeProperty(PropertyChangedEvent);
				}

				StaticMeshEditorPtr.Pin()->GetStaticMesh()->MarkPackageDirty();
			}
			else
			{
				const bool bSelectedPrim = StaticMeshEditorPtr.Pin()->HasSelectedPrims();
				if (bSelectedPrim && CurrentAxis != EAxisList::None)
				{
					const FWidget::EWidgetMode MoveMode = GetWidgetMode();
					if (MoveMode == FWidget::WM_Rotate)
					{
						StaticMeshEditorPtr.Pin()->RotateSelectedPrims(Rot);
					}
					else if (MoveMode == FWidget::WM_Scale)
					{
						StaticMeshEditorPtr.Pin()->ScaleSelectedPrims(Scale);
					}
					else if (MoveMode == FWidget::WM_Translate)
					{
						StaticMeshEditorPtr.Pin()->TranslateSelectedPrims(Drag);
					}

					StaticMeshEditorPtr.Pin()->GetStaticMesh()->MarkPackageDirty();
				}
			}
		}

		Invalidate();		
		bHandled = true;
	}

	return bHandled;
}