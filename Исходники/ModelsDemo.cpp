bool ModelsDemo::DrawGameObject( GameObject * game_object )
{
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	// THESE OPERATIONS ARE NOT ENCAPSULATED YET !!!

	// activate the vertex layout on the graphics card
	d3dContext_->IASetInputLayout( inputLayout_ );

	// activate the vertex shader on the graphics card
	d3dContext_->VSSetShader( textureMapVS_, 0, 0 );
	
	// activate the pixel shader on the graphics card
	d3dContext_->PSSetShader( textureMapPS_, 0, 0 );

	// activate the texture sampler on the graphics card
	d3dContext_->PSSetSamplers( 0, 1, &colorMapSampler_ );

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	// get the display object from the game object
	DisplayObject * display_object = game_object->GetDisplayObject();

	// activate the GameObject's vertex buffer on the graphics card
	display_object->GetModel()->Render( d3dContext_ );

	// activate the GameObject's texture buffer on the graphics card
	display_object->GetTexture()->Render( d3dContext_ );

	// create matrices to create a single world matrix for the GameObject's transform
	XMMATRIX scale_mat = XMMatrixScaling(game_object->getSX(), game_object->getSY(), game_object->getSZ());
	XMMATRIX rotation_mat = XMMatrixRotationRollPitchYaw(game_object->getRX(), game_object->getRY(), game_object->getRZ());
	XMMATRIX position_mat = XMMatrixTranslation(game_object->getX(), game_object->getY(), game_object->getZ());
	
	// 1) scale 
	// 2) rotate 
	// 3) position
	XMMATRIX world_mat = XMMatrixTranspose( scale_mat * rotation_mat * position_mat );

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	// THESE OPERATIONS ARE NOT ENCAPSULATED YET !!!

	// update the world matrix on the graphics card
	d3dContext_->UpdateSubresource( worldCB_, 0, 0, &world_mat, 0, 0 );

	// set the world matrix on the vertex shader
	d3dContext_->VSSetConstantBuffers( 0, 1, &worldCB_ );

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	d3dContext_->Draw( display_object->GetModel()->GetVertexCount(), 0 );

	return true;
}