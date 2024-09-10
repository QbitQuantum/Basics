bool WatcherData::updated(const Path& path)
{
    //printf("updated %s\n", path.constData());
    std::lock_guard<std::mutex> locker(updateMutex);
    const auto h = pathToHandle.find(path);
    if (h == pathToHandle.end()) {
        //printf("handle not found in pathToHandle\n");
        return false;
    }
    FindNextChangeNotification(h->second);

    // notify the main thread
    changedPaths.insert(path);
    SetEvent(wakeupHandle);
    return true;
}