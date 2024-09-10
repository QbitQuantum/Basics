//=================================================================================================================
bool TopdownTile::Render(Camera* camera, float blendAmount, XMFLOAT2 offset)
{
	//Render the regular texture below a fog texture that needs transparency
	/*if (m_fogBit != fow_n_non && m_fogBit != fow_n_all && m_bFOW)// || bFowUncovered)
	{
		ZShadeSandboxMesh::MeshRenderParameters mrp;
		mrp.camera = camera;
		mrp.blendAmount = blendAmount;
		mrp.specifyWorld = true;
		mrp.world = XMMatrixIdentity();
		
		if (m_CurrentSequence == NULL)
		{
			if (mBaseMesh == NULL) return false;
			mBaseMesh->UpdateBuffers(m_TopLeftPosition.x + offset.x, m_TopLeftPosition.y + offset.y);
			mBaseMesh->Render(mrp);
		}
		else
		{
			// If the tile has animation render it under the FOW tile
			RenderAnimation(camera, blendAmount, offset);
		}
		
		// Renders a transparent FOW tile above the regular tile
		RenderFow(camera, blendAmount, offset);
		//if (mMesh == NULL) return false;
		//mMesh->UpdateBuffers(m_TopLeftPosition.x + offset.x, m_TopLeftPosition.y + offset.y);
		//mMesh->Render(mrp);
	}
	else if (m_fogBit == fow_n_all && m_bFOW)
	{
		ZShadeSandboxMesh::MeshRenderParameters mrp;
		mrp.camera = camera;
		mrp.blendAmount = blendAmount;
		mrp.specifyWorld = true;
		mrp.world = XMMatrixIdentity();
		if (fow_all_texture == NULL) return false;
		fow_all_texture->UpdateBuffers(m_TopLeftPosition.x + offset.x, m_TopLeftPosition.y + offset.y);
		fow_all_texture->Render(mrp);
	}
	else
	{
		if (m_CurrentSequence == NULL)
		{
			if (mBaseMesh == NULL) return false;
			mBaseMesh->UpdateBuffers(m_TopLeftPosition.x + offset.x, m_TopLeftPosition.y + offset.y);
			ZShadeSandboxMesh::MeshRenderParameters mrp;
			mrp.camera = camera;
			mrp.blendAmount = blendAmount;
			mrp.specifyWorld = true;
			mrp.world = XMMatrixIdentity();
			mBaseMesh->Render(mrp);
		}
		else
		{
			//Render TopdownTile Animation2D
			RenderAnimation(camera, blendAmount, offset);
		}
	}

	if (m_displayHardbox && mHard) RenderHardboxMesh(camera, offset);*/

	if (m_CurrentSequence == NULL)
	{
		if (mBaseMesh == NULL) return false;
		mBaseMesh->UpdateBuffers(m_TopLeftPosition.x + offset.x, m_TopLeftPosition.y + offset.y);
		ZShadeSandboxMesh::MeshRenderParameters mrp;
		mrp.camera = camera;
		mrp.blendAmount = blendAmount;
		mrp.specifyWorld = true;
		mrp.world = XMMatrixIdentity();
		mBaseMesh->Render(mrp);
	}
	else
	{
		//Render TopdownTile Animation2D
		RenderAnimation(camera, blendAmount, offset);
	}

	if (m_displayHardbox && mHard) RenderHardboxMesh(camera, offset);

	return true;
}