void FDetailCategoryImpl::GenerateNodesFromCustomizations( const FCustomizationList& InCustomizationList, bool bDefaultLayouts, FDetailNodeList& OutNodeList, bool &bOutLastItemHasMultipleColumns )
{
	bOutLastItemHasMultipleColumns = false;
	for( int32 CustomizationIndex = 0; CustomizationIndex < InCustomizationList.Num(); ++CustomizationIndex )
	{
		const FDetailLayoutCustomization& Customization = InCustomizationList[CustomizationIndex];
		// When building default layouts cull default properties which have been customized
		if( Customization.IsValidCustomization() && ( !bDefaultLayouts || !IsCustomProperty( Customization.GetPropertyNode() ) ) )
		{
			bool bParentEnabled = true;
			TSharedRef<FDetailItemNode> NewNode = MakeShareable( new FDetailItemNode( Customization, AsShared(), bParentEnabled ) );
			NewNode->Initialize();

			if( CustomizationIndex == InCustomizationList.Num()-1 )
			{
				bOutLastItemHasMultipleColumns = NewNode->HasMultiColumnWidget();
			}

			OutNodeList.Add( NewNode );
		}
	}
}