bool outputClippingPlane( const ScenePlug *scene, const ScenePlug::ScenePath &path, IECore::Renderer *renderer )
{
	IECore::ConstClippingPlanePtr clippingPlane = runTimeCast<const IECore::ClippingPlane>( scene->object( path ) );
	if( !clippingPlane )
	{
		return false;
	}

	if( !visible( scene, path ) )
	{
		return false;
	}

	const M44f transform = scene->fullTransform( path );

	TransformBlock transformBlock( renderer );
	renderer->concatTransform( transform );
	clippingPlane->render( renderer );

	return true;
}