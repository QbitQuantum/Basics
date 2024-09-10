//------------------------------------------------------
void DatabaseService::mergeLoad(const std::string &filename,
                                uint32_t loadMask) {
    FileGroupPtr db = getDBFileNamed(filename);
    uint32_t ft = getFileType(db);

    LOG_DEBUG("DatabaseService::mergeLoad - Merge load of file %s",
              filename.c_str());

    mLoadingStatus.reset();
    mLoadingStatus.totalCoarse += mListeners.size();

    broadcastOnDBLoad(db, ft & loadMask);

    LOG_DEBUG("DatabaseService::mergeLoad - end()");
}