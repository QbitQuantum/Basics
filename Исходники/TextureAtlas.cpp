void TextureAtlas::addImage(ImageHandle newImageHandle, Rectangle newRect)
{
    Image* newImage = newImageHandle.Resolve();

    bool wasRotated = newImage->getWidth() == newRect.height &&
                      newImage->getHeight() == newRect.width;

    Image* atlasImage = atlasImageHandle.Resolve();

    assert(newImage->getPixelFormat() == atlasImage->getPixelFormat());

    if (wasRotated)
        RotateImage(newImage,atlasImage,Vector2i(newRect.x,newRect.y));
    else
        atlasImage->setBuffer(newImage,Vector2i(newRect.x,newRect.y));

    SubTexture subTexture;
    subTexture.atlas = this;

    float bottom = (float)(newRect.y+newRect.height)/atlasSize;
    float top = (float)newRect.y/atlasSize;
    float right = (float)(newRect.x+newRect.width)/atlasSize;
    float left = (float)newRect.x/atlasSize;

    if(!wasRotated)
    {
        subTexture.leftTopUV = Vector2(left,top);
        subTexture.rightTopUV = Vector2(right,top);
        subTexture.rightBottomUV = Vector2(right,bottom);
        subTexture.leftBottomUV = Vector2(left,bottom);
    } 
    else 
    {
        subTexture.rightTopUV = Vector2(left,top);
        subTexture.rightBottomUV = Vector2(right,top);
        subTexture.leftBottomUV = Vector2(right,bottom);
        subTexture.leftTopUV = Vector2(left,bottom);
    }

    imageSubTextures[newImageHandle] = subTexture;
}