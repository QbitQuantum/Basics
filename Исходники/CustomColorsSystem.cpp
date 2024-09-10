bool CustomColorsSystem::LoadTexture( const DAVA::FilePath &filePath, bool createUndo /* = true */ )
{
	if(filePath.IsEmpty())
		return false;

    Vector<Image*> images;
    ImageSystem::Instance()->Load(filePath, images);
	if(images.empty())
		return false;

	Image* image = images.front();
	if(image)
	{
		Texture* texture = Texture::CreateFromData(image->GetPixelFormat(),
												   image->GetData(),
												   image->GetWidth(),
												   image->GetHeight(),
												   false);
		Sprite* sprite = Sprite::CreateFromTexture(texture, 0, 0, texture->GetWidth(), texture->GetHeight());

		if (createUndo)
		{
			StoreOriginalState();
		}
		RenderManager::Instance()->SetRenderTarget(drawSystem->GetCustomColorsProxy()->GetSprite());
        
        Sprite::DrawState drawState;
		sprite->Draw(&drawState);
        
		RenderManager::Instance()->RestoreRenderTarget();
		AddRectToAccumulator(Rect(Vector2(0.f, 0.f), Vector2(texture->GetWidth(), texture->GetHeight())));

		SafeRelease(sprite);
		SafeRelease(texture);
		for_each(images.begin(), images.end(), SafeRelease<Image>);

		if (createUndo)
		{
			((SceneEditor2*)GetScene())->BeginBatch("Load custom colors texture");
			StoreSaveFileName(filePath);
			CreateUndoPoint();
			((SceneEditor2*)GetScene())->EndBatch();
		}
	}

    return true;
}