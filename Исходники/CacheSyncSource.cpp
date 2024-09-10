StringBuffer CacheSyncSource::getItemSignature(StringBuffer& key) {

    void* content       = NULL;
    size_t size         = 0;
    
    if (key.length() <= 0) {
        return NULL;
    }
    
    LOG.debug("[%s] Getting signature for item with key %s", getName(), key.c_str());
    
    content = getItemContent(key, &size);                      
    StringBuffer s;
    s.sprintf("%ld", calculateCRC(content, size));
    if (content) { delete [] (char*)content; content = NULL; }    
    return s;
}