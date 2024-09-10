bool MHLabelsStore::RemoveEntry(MHStoreEntry* entry)
{
    if (entry == NULL) {
        LOG.error("%s: invalid parameter", __FUNCTION__);
        return false;
    }
    
    MHLabelInfo* itemInfo = dynamic_cast<MHLabelInfo*>(entry);
    if (itemInfo == NULL) {
        LOG.error("%s: invalid parameter", __FUNCTION__);
        return false;
    }

    if (store_status != store_status_initialized) {
        LOG.error("%s: can't add entry: cache is not initialized", __FUNCTION__);
        return false;
    }
    
    
    StringBuffer sql;
    sql.sprintf(delete_row_id_stmt_fmt, store_name.c_str(), itemInfo->getLuid());
    
    if (sql.empty()) {
        LOG.error("%s: error formatting delete-entry statement", __FUNCTION__);
        return false;
    }
    
    //LOG.debug("%s: > SQL exec: '%s'", __FUNCTION__, sql.c_str());
    pthread_mutex_lock(&store_access_mutex);
    int ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    int changes = sqlite3_changes(db);
    pthread_mutex_unlock(&store_access_mutex);
    
    if (ret != SQLITE_OK) {
        LOG.error("%s: error executing SQL statement: %s", __FUNCTION__, sqlite3_errmsg(db));
        return false;
    } else if (changes == 0) {
        LOG.info("%s: cannot remove item %u", __FUNCTION__, itemInfo->getLuid());
        return false;
    }
    else {
        cache_items_count = getCount();
        cache_items_count--;
        return true;
    }
}