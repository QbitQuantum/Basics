HttpManager* HttpManager::getInstance() {
    if (httpManager == NULL) {
        cLock.Lock();
        if (httpManager == NULL) {
            httpManager = new HttpManager();
        }
        cLock.Unlock();
    }
    return httpManager;
}