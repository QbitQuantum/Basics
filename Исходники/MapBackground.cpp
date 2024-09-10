void MapBackground::CreateMapTileImage(MapTile* pMapTile, void* gResult, uint32 gResultLen, bool isJpg)
{
	if (!IsTileVisible(pMapTile))
	{
		return;
	}
	CIwImage image;
	if (!isJpg)
	{
		//pMapTile->pTexture = g_pNotFoundTexture;
		s3eFile* tempfile = s3eFileOpenFromMemory((void*)gResult, gResultLen);
		image.ReadFile(tempfile);

		//image.LoadFromFile("tiles/r0302322130033033130.png");

		if (image.GetWidth())
		{
			pMapTile->pTexture = new CIwTexture;
			pMapTile->pTexture->CopyFromImage(&image);
			pMapTile->pTexture->Upload();
		}

		s3eFileClose(tempfile);
	}
	else
	{
		JPEGImage(gResult, gResultLen, image);
		pMapTile->pTexture = new CIwTexture;
		pMapTile->pTexture->CopyFromImage(&image);
		pMapTile->pTexture->Upload();
	}
}