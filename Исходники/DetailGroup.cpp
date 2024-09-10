void FDetailGroup::OnGenerateChildren( FDetailNodeList& OutChildren )
{
	for( int32 ChildIndex = 0; ChildIndex < GroupChildren.Num(); ++ChildIndex )
	{
		TSharedRef<FDetailItemNode> NewNode = MakeShareable( new FDetailItemNode( GroupChildren[ChildIndex], ParentCategory.Pin().ToSharedRef(), IsParentEnabled ) );
		NewNode->Initialize();
		OutChildren.Add( NewNode );
	}
}