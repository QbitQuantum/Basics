void UKUIInterfaceElement::CalculateAlignLocation( TArray<UKUIInterfaceElement*>& arAlignStack )
{
	if ( HasValidAlignLocation() )
		return;

	// Avoid recursive layout dependencies.
	if ( arAlignStack.Contains( this ) )
		return;

	if ( GetContainer() != NULL && GetContainer()->IsChildsLayoutManaged( this ) )
	{
		//SetAlignLocation( FVector2D::ZeroVector );

		// Caused circular layout dependencies.
		//if ( !GetContainer()->HasValidLayout() )
			//GetContainer()->DoLayout();

		return;
	}

	UKUIInterfaceElement* oAlignedTo = GetAlignedTo();

	if ( oAlignedTo == NULL )
		oAlignedTo = GetContainer();

	if ( oAlignedTo == NULL )
	{
		SetAlignLocation( FVector2D::ZeroVector );
		return;
	}

	arAlignStack.Add( this );

	if ( !oAlignedTo->HasValidAlignLocation() )
		oAlignedTo->CalculateAlignLocation( arAlignStack );

	const FVector2D v2Size = GetSize() + GetMarginSize();
	FVector2D v2AlignLocation = FVector2D::ZeroVector;
	FVector2D v2AlignSize = FVector2D::ZeroVector;
	FVector2D v2AlignRenderLocation = FVector2D::ZeroVector;

	// If we're aligned to something in this container, use local space
	if ( oAlignedTo->GetContainer() == GetContainer() )	
	{
		v2AlignRenderLocation = oAlignedTo->GetRenderLocation() - oAlignedTo->GetMarginOffset();
		v2AlignSize = oAlignedTo->GetSize() + oAlignedTo->GetMarginSize();
	}

	// If we're aligned to something outside our container, use its screen location
	else if ( oAlignedTo != GetContainer() )
	{
		v2AlignRenderLocation = oAlignedTo->GetScreenLocation() - oAlignedTo->GetMarginOffset();
		v2AlignSize = oAlignedTo->GetSize() + oAlignedTo->GetMarginSize();
	}

	// We're aligned to the container, so use 0, 0
	else
	{
		v2AlignRenderLocation = FVector2D::ZeroVector;
		v2AlignSize = oAlignedTo->GetSize();
	}

	v2AlignLocation = CalculateAlignLocation( 
		v2AlignRenderLocation, 
		v2AlignSize, 
		v2Size
	);

	// If we're aligned to something outside of our container, move the align location back into local space.
	if ( oAlignedTo != GetContainer() && oAlignedTo->GetContainer() != GetContainer() )
		v2AlignLocation += oAlignedTo->GetScreenLocation() - GetContainer()->GetScreenLocation();

	arAlignStack.Remove( this );
	SetAlignLocation( v2AlignLocation );
}