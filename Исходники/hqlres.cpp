bool ResourceManager::addCompress(const char * type, unsigned len, const void * data, IPropertyTree *manifestEntry, unsigned id, bool addToManifest)
{
    bool isCompressed=false;
    if (len>=32) //lzw assert if too small
    {
        isCompressed = true;
        MemoryBuffer compressed;
        compressResource(compressed, len, data);
        addNamed(type, compressed.length(), compressed.toByteArray(), manifestEntry, id, addToManifest, isCompressed);
    }
    else
        addNamed(type, len, data, manifestEntry, id, addToManifest, isCompressed);
    return isCompressed;
}