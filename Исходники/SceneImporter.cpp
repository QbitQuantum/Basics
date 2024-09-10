void SceneImporter::computeTransform( const aiMatrix4x4 &m, Transformation &t )
{
	aiVector3D position, scaling;
 	aiQuaternion rotation;
 	m.Decompose( scaling, rotation, position );

 	t.setTranslate( position.x, position.y, position.z );
 	t.setScale( ( scaling.x + scaling.y + scaling.z ) / 3.0f );
 	t.setRotate( Quaternion4f( rotation.x, rotation.y, rotation.z, rotation.w ) );
}