void WorldGenerator::AddFloor( float _x, float _y )
{
	Floor* floor = new Floor();
	floor->mPosition = D3DXVECTOR3( _x, -100, _y );
	floor->mModel = mResources->getModel( 801 );
	floor->Initialize( md3dManager );

	mGFS->mFloor.push_back( floor );
}