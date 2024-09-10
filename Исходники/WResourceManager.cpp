//ResourceManagerImpl
void ResourceManagerImpl::DebugRender()
{
    JRenderer* renderer = JRenderer::GetInstance();
    WFont * font = ResourceManagerImpl::Instance()->GetWFont(Fonts::MAIN_FONT);
    if (!font || !renderer) return;

    font->SetColor(ARGB(255,255,255,255));
    font->SetScale(DEFAULT_MAIN_FONT_SCALE);
    renderer->FillRect(0, 0, SCREEN_WIDTH, 40, ARGB(128,155,0,0));

    renderer->FillRect(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 40, ARGB(128,155,0,0));
    char buf[512];

    unsigned long man = 0;
    unsigned int misses = 0;

    if (textureWCache.cacheItems < textureWCache.cache.size()) misses = textureWCache.cache.size() - textureWCache.cacheItems;

    if (textureWCache.totalSize > textureWCache.cacheSize) man = textureWCache.totalSize - textureWCache.cacheSize;

    sprintf(buf, "Textures %u+%llu (of %u) items (%u misses), Pixels: %lu (of %lu) + %lu", textureWCache.cacheItems,
            (long long unsigned int) textureWCache.managed.size(), textureWCache.maxCached, misses,
            textureWCache.cacheSize, textureWCache.maxCacheSize, man);
    font->DrawString(buf, 10, 5);

#ifdef PSP
    //deliberately off - these functions aren't thread safe!
    //int maxLinear = ramAvailableLineareMax();
    //int ram = ramAvailable();

    //sprintf(buf, "Ram : linear max: %i - total : %i sceSize : %i\n", maxLinear, ram, sceSize);
    //font->DrawString(buf, 10, 20);
#endif

    sprintf(buf, "Time: %u. Total Size: %lu (%lu cached, %lu managed). ", lastTime, Size(), SizeCached(), SizeManaged());
    font->DrawString(buf, SCREEN_WIDTH - 10, SCREEN_HEIGHT - 15, JGETEXT_RIGHT);

#ifdef DEBUG_CACHE
    if(debugMessage.size())
        font->DrawString(debugMessage.c_str(), SCREEN_WIDTH-10,SCREEN_HEIGHT-25,JGETEXT_RIGHT);

#endif
}