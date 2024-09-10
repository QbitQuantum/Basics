void LevelDisplay::draw( ID3D11DeviceContext* device, ID3DX11Effect* fx, World& world, XMFLOAT4& cameraPos, float blockDimensions )
{
    UINT stride = sizeof(DungeonVertex);
    UINT offset = 0;

    //Update the world matrix
    XMMATRIX worldm = XMMatrixIdentity();

    //Set input layout and topology
    device->IASetInputLayout( mInputLayout );
    device->IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    //Update the world matrix
    device->UpdateSubresource( mWorldCB, 0, 0, &worldm, 0, 0 ); 
    device->VSSetConstantBuffers( 1, 1, &mWorldCB );

    //Set the floor texture
    device->PSSetShaderResources(0, 1, &mFloorTexture );

    //Draw the floor
    device->IASetIndexBuffer( mFloorIB, DXGI_FORMAT_R16_UINT, 0 );
    device->IASetVertexBuffers(0, 1, &mFloorVB, &stride, &offset);
    device->DrawIndexed(6 * mBlockCount, 0, 0);

    //Draw the walls
    device->PSSetShaderResources(0, 1, &mWallTexture );

    device->IASetIndexBuffer( mWallsIB, DXGI_FORMAT_R16_UINT, 0 );
    device->IASetVertexBuffers(0, 1, &mWallsVB, &stride, &offset);
    device->DrawIndexed(6 * mWallCount, 0, 0);

    //Draw the ceiling
    device->PSSetShaderResources(0, 1, &mCeilingTexture );

    device->IASetIndexBuffer( mCeilingIB, DXGI_FORMAT_R16_UINT, 0 );
    device->IASetVertexBuffers(0, 1, &mCeilingVB, &stride, &offset);
    device->DrawIndexed(6 * mBlockCount, 0, 0);

	Level& level = world.getLevel();
    float halfBlockDimension = blockDimensions / 2.0f;

    //Draw light meshes at light locations
    for(ushort i = 0; i < level.getNumLights(); i++){
        Level::Light& l = level.getLight( i );

        float xOffset = 0.0f;
        float zOffset = 0.0f;

        if( l.getType() == Level::Light::Type::Torch ){
            xOffset =   l.getAttachedWall() == Level::Light::AttachedWall::Left ? -halfBlockDimension :
                      ( l.getAttachedWall() == Level::Light::AttachedWall::Back ? halfBlockDimension : 0.0f );
            zOffset =   l.getAttachedWall() == Level::Light::AttachedWall::Right ? halfBlockDimension : 
                      ( l.getAttachedWall() == Level::Light::AttachedWall::Front ? -halfBlockDimension : 0.0f );
        }

        float tx = ( static_cast<float>(l.getI()) * blockDimensions ) + halfBlockDimension + xOffset;
        float ty = l.getHeight();
        float tz = ( static_cast<float>(l.getJ()) * blockDimensions ) + halfBlockDimension + zOffset;

        float dx = (cameraPos.x - tx);
        float dz = (cameraPos.z - tz);

        float d = sqrt( (dx * dx) + (dz * dz) );

        //If we are outside the draw range, skip drawing this one
        if( d > mDrawRange ){
            continue;
        }

        worldm = XMMatrixScaling( mLightScale[ l.getType() ], mLightScale[ l.getType() ], mLightScale[ l.getType() ] ) * 
                 XMMatrixRotationY( static_cast<float>( l.getAttachedWall() ) * PI_OVER_2 ) * 
                 XMMatrixTranslation( tx, ty, tz );

        worldm = XMMatrixTranspose( worldm );

        device->UpdateSubresource( mWorldCB, 0, 0, &worldm, 0, 0 ); 
		device->VSSetConstantBuffers( 1, 1, &mWorldCB );

        mLights[ l.getType() - 1 ].draw( device );
    }

    //Draw furniture meshes
    for(uint i = 0; i < level.getNumFurniture(); i++)
	{
        Level::Furniture& f = level.getFurniture(i);

        float dx = (cameraPos.x - f.getPosition().x);
        float dz = (cameraPos.z - f.getPosition().z);

        float d = sqrt( (dx * dx) + (dz * dz) );

        //If we are outside the draw range, skip drawing this one
        if( d > mDrawRange ){
            continue;
        }

        worldm = XMMatrixScaling( mFurnitureScale[ f.getType() ], 
                                  mFurnitureScale[ f.getType() ], 
                                  mFurnitureScale[ f.getType() ]) * 
                 XMMatrixRotationY( f.getYRotation() ) * 
                 XMMatrixTranslation( f.getPosition().x, f.getPosition().y, f.getPosition().z );

		worldm = XMMatrixTranspose( worldm );

		device->UpdateSubresource( mWorldCB, 0, 0, &worldm, 0, 0 ); 
		device->VSSetConstantBuffers( 1, 1, &mWorldCB );

        mFurniture[ f.getType() - 1 ].draw(device);
	}

    //Draw Containers
    for(uint i = 0; i < level.getNumContainer(); i++)
	{
        Level::Container& f = level.getContainer(i);

        float dx = (cameraPos.x - f.getPosition().x);
        float dz = (cameraPos.z - f.getPosition().z);

        float d = sqrt( (dx * dx) + (dz * dz) );

        //If we are outside the draw range, skip drawing this one
        if( d > mDrawRange ){
            continue;
        }

        worldm = XMMatrixScaling( mContainerScale[ f.getCType() ], 
                                  mContainerScale[ f.getCType() ], 
                                  mContainerScale[ f.getCType() ]) * 
                 XMMatrixRotationY( f.getYRotation() ) * 
                 XMMatrixTranslation( f.getPosition().x, f.getPosition().y, f.getPosition().z );

		worldm = XMMatrixTranspose( worldm );

		device->UpdateSubresource( mWorldCB, 0, 0, &worldm, 0, 0 ); 
		device->VSSetConstantBuffers( 1, 1, &mWorldCB );

        mContainers[ f.getCType() - 1 ].draw(device);
	}

    for(uint i = 0; i < level.getNumDoors(); i++)
	{
        Level::Door& f = level.getDoor(i);

        float dx = (cameraPos.x - f.getPosition().x);
        float dz = (cameraPos.z - f.getPosition().z);

        float d = sqrt( (dx * dx) + (dz * dz) );

        //If we are outside the draw range, skip drawing this one
        if( d > mDrawRange ){
            continue;
        }

        worldm = XMMatrixScaling( mDoorScale, 
                                  mDoorScale, 
                                  mDoorScale) * 
                 XMMatrixRotationY( f.getYRotation() ) * 
                 XMMatrixTranslation( f.getPosition().x, f.getPosition().y, f.getPosition().z );

		worldm = XMMatrixTranspose( worldm );

		device->UpdateSubresource( mWorldCB, 0, 0, &worldm, 0, 0 ); 
		device->VSSetConstantBuffers( 1, 1, &mWorldCB );

        mDoor.draw(device);
	}
}