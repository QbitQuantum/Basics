bool OpenGL11::isTextureSupported(TextureType type, const Image& image) const
{
    if (!glTextureTypeEnum[type])
        return false;

    if ((type == Texture2D && !image.isValid2DImage()) || (type == Texture3D && !image.isValid3DImage()) ||
        (type == TextureCubemap && !image.isValidCubemapImage()))
        return false;

    auto maximumTextureSize = getMaximumTextureSize(type);
    if (image.getWidth() > maximumTextureSize || image.getHeight() > maximumTextureSize ||
        image.getDepth() > maximumTextureSize)
        return false;

    if (image.isNPOT() && !isNonPowerOfTwoTextureSupported(type))
        return false;

    if (!isPixelFormatSupported(image.getPixelFormat(), type))
        return false;

    return true;
}