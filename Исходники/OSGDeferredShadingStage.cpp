void DeferredShadingStage::updateGBuffer(
    TextureBuffer *buf, UInt32 index, Int32 width, Int32 height)
{
    TextureObjChunk *bufTex = buf   ->getTexture();
    Image           *bufImg = bufTex->getImage  ();

    if((_changeCache & (PixelFormatsFieldMask |
                        PixelTypesFieldMask    )) != 0)
    {
        bufImg->setPixelFormat(_mfPixelFormats[index]);
        bufImg->setDataType   (_mfPixelTypes  [index]);
    }

    if(_targetSizeChanged == true)
    {
        bufImg->setWidth (width );
        bufImg->setHeight(height);
    }
}