int PinnedMediaManager_InsertOrUpdatePinnedMediaItem(const std::string& path, const std::string& object_id, u64 device_id)
{
    int rv = 0;
    MutexAutoLock lock(VPLLazyInitMutex_GetMutex(&m_mutex));
    if (!is_initialized) {
        LOG_ERROR("Need to call PinnedMediaManager_Init()");
        return CCD_ERROR_NOT_INIT;
    }

    rv = pinned_media_db_manager.beginTransaction() ||
         pinned_media_db_manager.insertPinnedMediaItem(path, object_id, device_id) ||
         pinned_media_db_manager.commitTransaction();
    if (rv) {
        LOG_ERROR("Failed to insert pinned_media_item, rv = %d (path=%s, object_id=%s, device_id="FMTu64")",
                rv, path.c_str(), object_id.c_str(), device_id);
    }
    return rv;
}