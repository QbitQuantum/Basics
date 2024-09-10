void SpriteSheet::RenderSprite( GameSprite* sprite, ID3D11DeviceContext* d3dContext, ID3D11Buffer* vertexBuffer, ID3D11Buffer* mvpCB, XMMATRIX* vpMatrix )
{
	XMMATRIX world = sprite->GetWorldMatrix( );
	XMMATRIX mvp = XMMatrixMultiply( world, *vpMatrix );
	mvp = XMMatrixTranspose( mvp );

	d3dContext->UpdateSubresource( mvpCB, 0, 0, &mvp, 0, 0 );
	d3dContext->VSSetConstantBuffers( 0, 1, &mvpCB );

	// draw the current sprite
	map<string, vector<XMFLOAT2>>::iterator a = animationMap_.find( sprite->GetCurrentAnimation( ) );
	map<string, float>::iterator f = durationMap_.find( sprite->GetCurrentAnimation( ) );

	// don't draw if the animation is not in the map
	if( a != animationMap_.end( ) )
	{
		unsigned int currentSprite = sprite->GetCurrentSprite( );

		if ( f != durationMap_.end( ) && f->second != -1)
		{
			float frameTime = sprite->GetFrameTime( );

			frameTime += game_->GetDeltaTime( );
			if( frameTime >= f->second )
			{
				currentSprite++;

				if( currentSprite >= a->second.size( ) )
				{
					currentSprite = 0;
				}

				// set the current sprite to the next one in the animation
				sprite->SetCurrentSprite( currentSprite );

				frameTime = 0.0f;
			}

			sprite->SetFrameTime( frameTime );

			// add delta time to the time since this sprite has been on this animation
			sprite->SetChangeAnimationTime( sprite->GetChangeAnimationTime( ) + game_->GetDeltaTime( ) );
		}

		// draw the first sprite in the animtation (background animations only have one sprite per animation)
		activate_ = DrawSprite( a->second.at( currentSprite ).x, a->second.at( currentSprite ).y, sprite->GetWidth( ), sprite->GetHeight( ), sheetWidth_, sheetHeight_, d3dContext, vertexBuffer );
	}
}