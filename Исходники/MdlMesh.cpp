//////////////////////////////////////////////////////////////////////////
// bakeTransform
void MdlMesh::bakeTransform( const MaMat4d& Transform )
{
	MaMat4d NrmTransform = Transform;
	NrmTransform.translation( MaVec3d( 0.0f, 0.0f, 0.0f ) );
	for( BcU32 i = 0; i < aVertices_.size(); ++i )
	{
		aVertices_[ i ].Position_ = aVertices_[ i ].Position_ * Transform;
		aVertices_[ i ].Normal_ = aVertices_[ i ].Normal_ * NrmTransform;
		aVertices_[ i ].Normal_.normalise();
		aVertices_[ i ].Tangent_ = aVertices_[ i ].Tangent_ * NrmTransform;
		aVertices_[ i ].Tangent_.normalise();
	}
}