void FDetailCustomBuilderRow::OnGenerateChildren( FDetailNodeList& OutChildren )
{
	ChildrenBuilder = MakeShareable( new FCustomChildrenBuilder( ParentCategory.Pin().ToSharedRef() ) );

	CustomNodeBuilder->GenerateChildContent( *ChildrenBuilder );
		
	const TArray< FDetailLayoutCustomization >& ChildRows = ChildrenBuilder->GetChildCustomizations();

	for( int32 ChildIndex = 0; ChildIndex < ChildRows.Num(); ++ChildIndex )
	{
		TSharedRef<FDetailItemNode> ChildNodeItem = MakeShareable( new FDetailItemNode( ChildRows[ChildIndex], ParentCategory.Pin().ToSharedRef(), IsParentEnabled ) );
		ChildNodeItem->Initialize();
		OutChildren.Add( ChildNodeItem );
	}
}