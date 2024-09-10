void QGLBlurTextureCache::clearBlurTextureInfo(quint64 cacheKey)
{
    cache.remove(cacheKey);
}