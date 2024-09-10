//////////////////////////////////////////////////////////////////////////
// update
//virtual
void ScnModelComponent::postUpdate( BcF32 Tick )
{
	Super::postUpdate( Tick );

	UpdateFence_.increment();
	updateNodes( BaseTransform_ * getParentEntity()->getWorldMatrix() );

#if DEBUG_RENDER_NODES
	BcU32 NoofNodes = Model_->pHeader_->NoofNodes_;
	for( BcU32 NodeIdx = 0; NodeIdx < NoofNodes; ++NodeIdx )
	{
		ScnModelNodeTransformData* pNodeTransformData = &pNodeTransformData_[ NodeIdx ];
		ScnModelNodePropertyData* pNodePropertyData = &Model_->pNodePropertyData_[ NodeIdx ];

		MaMat4d ThisMatrix = pNodeTransformData->WorldTransform_;
		MaMat4d ParentMatrix = pNodePropertyData->ParentIndex_ != BcErrorCode ? 
			pNodeTransformData_[ pNodePropertyData->ParentIndex_ ].WorldTransform_ :
			getParentEntity()->getWorldMatrix();

		ScnDebugRenderComponent::pImpl()->drawMatrix( 
			ThisMatrix, RsColour::WHITE, 2000 );
		ScnDebugRenderComponent::pImpl()->drawLine( 
			ParentMatrix.translation(), 
			ThisMatrix.translation(), 
			RsColour::WHITE, 1000 );
	}

#endif // DEBUG_RENDER_NODES
}