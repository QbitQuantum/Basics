Image *LandscapeEditorHeightmap::CreateToolImage(int32 sideSize)
{
    RenderManager::Instance()->LockNonMain();
    
    Image *image = currentTool->image;
    Sprite *dstSprite = Sprite::CreateAsRenderTarget((float32)sideSize, (float32)sideSize, FORMAT_RGBA8888);
    Texture *srcTex = Texture::CreateFromData(image->GetPixelFormat(), image->GetData(), 
                                              image->GetWidth(), image->GetHeight(), false);
    Sprite *srcSprite = Sprite::CreateFromTexture(srcTex, 0, 0, (float32)image->GetWidth(), (float32)image->GetHeight());
    
    RenderManager::Instance()->SetRenderTarget(dstSprite);
    
    RenderManager::Instance()->SetColor(Color::Black());
    RenderHelper::Instance()->FillRect(Rect(0, 0, (float32)dstSprite->GetTexture()->GetWidth(), (float32)dstSprite->GetTexture()->GetHeight()));
    
    RenderManager::Instance()->SetBlendMode(BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA);
    RenderManager::Instance()->SetColor(Color::White());
    
    srcSprite->SetScaleSize((float32)sideSize, (float32)sideSize);
    srcSprite->SetPosition(Vector2((dstSprite->GetTexture()->GetWidth() - sideSize)/2.0f, 
                                   (dstSprite->GetTexture()->GetHeight() - sideSize)/2.0f));
    srcSprite->Draw();
    RenderManager::Instance()->RestoreRenderTarget();
    
    Image *retImage = dstSprite->GetTexture()->CreateImageFromMemory();
    
    SafeRelease(srcSprite);
    SafeRelease(srcTex);
    SafeRelease(dstSprite);
    
    RenderManager::Instance()->UnlockNonMain();
    
    return retImage;
}