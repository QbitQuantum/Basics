void TerrainTextureOverlay::RenderAfterWater()
{
	CTerrain* terrain = g_Game->GetWorld()->GetTerrain();

	ssize_t w = (ssize_t)(terrain->GetTilesPerSide() * m_TexelsPerTile);
	ssize_t h = (ssize_t)(terrain->GetTilesPerSide() * m_TexelsPerTile);

	pglActiveTextureARB(GL_TEXTURE0);

	// Recreate the texture with new size if necessary
	if (round_up_to_pow2(w) != m_TextureW || round_up_to_pow2(h) != m_TextureH)
	{
		m_TextureW = round_up_to_pow2(w);
		m_TextureH = round_up_to_pow2(h);

		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_TextureW, m_TextureH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	u8* data = (u8*)calloc(w * h, 4);
	BuildTextureRGBA(data, w, h);

	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);

	CMatrix3D matrix;
	matrix.SetZero();
	matrix._11 = m_TexelsPerTile / (m_TextureW * TERRAIN_TILE_SIZE);
	matrix._23 = m_TexelsPerTile / (m_TextureH * TERRAIN_TILE_SIZE);
	matrix._44 = 1;

	g_Renderer.GetTerrainRenderer().RenderTerrainOverlayTexture(matrix);
}