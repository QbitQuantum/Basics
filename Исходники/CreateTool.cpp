bool CreateTool::ValidPosition( const AlignedBox& bounds, const Vector3& translation, float minDistance )
{
	Editor::HierarchyNode* node = Reflect::SafeCast<Editor::HierarchyNode>( m_Instance );

	FrustumPickVisitor frustumPick( m_Scene->GetViewport()->GetCamera(), Frustum( bounds ) );
	m_Scene->Pick( &frustumPick );

	V_PickHitSmartPtr::const_iterator resultsItr = frustumPick.GetHits().begin();
	V_PickHitSmartPtr::const_iterator resultsEnd = frustumPick.GetHits().end();
	for ( ; resultsItr != resultsEnd; ++resultsItr )
	{
		Editor::HierarchyNode* currentNode = Reflect::SafeCast<Editor::HierarchyNode>( (*resultsItr)->GetHitObject() );
		if ( !currentNode->IsTransient() && ( s_PaintPreventAnyOverlap || node->IsSimilar( currentNode ) ) )
		{
			const Editor::Transform* transform = currentNode->GetTransform();
			if ( !transform )
			{
				return false;
			}

			Vector3 position( transform->GetGlobalTransform().t.x, transform->GetGlobalTransform().t.y, transform->GetGlobalTransform().t.z );
			Vector3 differenceVector = translation - position;
			if ( differenceVector.Length() < minDistance )
			{
				return false;
			}
		}
	}

	return true;
}