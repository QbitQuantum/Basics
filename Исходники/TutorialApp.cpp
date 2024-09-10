TutorialApp::TutorialApp()
{
	// Set square size
	mSize = 100.0f;
	const vec2 sz( mSize );

	// We are going to create two UiTrees for each type of transform:
	// one which uses velocity and one that does not.
	for ( size_t i = Transform_None + 1; i < Transform_Count; ++i ) {
		for ( size_t j = 0; j < 2; ++j ) {
			
			// Define the data structure.
			UiData data;
			data.mColor			= Colorf( randFloat(), randFloat(), randFloat() );
			data.mTransform		= (Transform)i;
			data.mUseVelocity	= j == 1;


			// Create the node and set its data.
			UiTree& node = mUiTree.createAndReturnChild()
				.data( data )
				.scale( sz );
			const Rectf bounds	= calcBounds( node );
			const vec2 p		= bounds.getCenter() - sz * 0.5f;
			node.translate( p );
		}
	}
}