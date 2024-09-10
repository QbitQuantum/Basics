SPtr<Texture> TextureManager::createTexture(TextureType texType, UINT32 width, UINT32 height, UINT32 depth, int numMipmaps,
        PixelFormat format, int usage, bool hwGamma, UINT32 multisampleCount, UINT32 numArraySlices)
{
    Texture* tex = new (bs_alloc<Texture>()) Texture(texType, width, height, depth, numMipmaps, format, usage, hwGamma, multisampleCount, numArraySlices);
    SPtr<Texture> ret = bs_core_ptr<Texture>(tex);

    ret->_setThisPtr(ret);
    ret->initialize();

    return ret;
}