void LandscapeEditorCustomColors::LoadTextureAction(const FilePath &pathToFile)
{
	if(pathToFile.IsEmpty())
		return;

	Vector<Image*> images = ImageLoader::CreateFromFile(pathToFile);
	if(images.empty())
		return;

	Image* image = images.front();
	if(image)
	{
		Texture* texture = Texture::CreateFromData(image->GetPixelFormat(),
												   image->GetData(),
												   image->GetWidth(),
												   image->GetHeight(),
												   false);

		SafeRelease(colorSprite);
		colorSprite = Sprite::CreateAsRenderTarget(texSurf->GetWidth(), texSurf->GetHeight(), FORMAT_RGBA8888);
		Sprite* sprite = Sprite::CreateFromTexture(texture, 0, 0, texture->GetWidth(), texture->GetHeight());

		StoreOriginalState();

		RenderManager::Instance()->SetRenderTarget(colorSprite);
		sprite->Draw();
		RenderManager::Instance()->RestoreRenderTarget();
		PerformLandscapeDraw();

		SafeRelease(sprite);
		SafeRelease(texture);
		for_each(images.begin(), images.end(), SafeRelease<Image>);

		StoreSaveFileName(pathToFile);

		CreateUndoPoint();
	}
}