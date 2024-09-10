///////////////////////////////////////////////////////////////////////////////////////////////////
// PackTerrain: pack the terrain onto the end of the output data stream
//		- data: map size, heightmap, list of textures used by map, texture tile assignments
void CMapWriter::PackTerrain(CFilePacker& packer, CTerrain* pTerrain)
{
	// pack map size
	const ssize_t mapsize = pTerrain->GetPatchesPerSide();
	packer.PackSize(mapsize);

	// pack heightmap
	packer.PackRaw(pTerrain->GetHeightMap(),sizeof(u16)*SQR(pTerrain->GetVerticesPerSide()));

	// the list of textures used by map
	std::vector<CStr> terrainTextures;
	// descriptions of each tile
	std::vector<STileDesc> tiles;

	// build lists by scanning through the terrain
	EnumTerrainTextures(pTerrain, terrainTextures, tiles);

	// pack texture names
	const size_t numTextures = terrainTextures.size();
	packer.PackSize(numTextures);
	for (size_t i=0;i<numTextures;i++)
		packer.PackString(terrainTextures[i]);

	// pack tile data
	packer.PackRaw(&tiles[0],sizeof(STileDesc)*tiles.size());
}