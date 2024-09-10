void PluginDatabase::loadPersistentMetadataCache()
{
    if (!isPersistentMetadataCacheEnabled() || persistentMetadataCachePath().isEmpty())
        return;

    PlatformFileHandle file;
    String absoluteCachePath = pathByAppendingComponent(persistentMetadataCachePath(), persistentPluginMetadataCacheFilename);
    file = openFile(absoluteCachePath, OpenForRead);

    if (!isHandleValid(file))
        return;

    // Mark cache as loaded regardless of success or failure. If
    // there's error in the cache, we won't try to load it anymore.
    m_persistentMetadataCacheIsLoaded = true;

    Vector<char> fileContents;
    fillBufferWithContentsOfFile(file, fileContents);
    closeFile(file);

    if (fileContents.size() < 2 || fileContents.first() != schemaVersion || fileContents.last() != '\0') {
        LOG_ERROR("Unable to read plugin metadata cache: corrupt schema");
        deleteFile(absoluteCachePath);
        return;
    }

    char* bufferPos = fileContents.data() + 1;
    char* end = fileContents.data() + fileContents.size();

    PluginSet cachedPlugins;
    HashMap<String, time_t> cachedPluginPathsWithTimes;
    HashMap<String, RefPtr<PluginPackage> > cachedPluginsByPath;

    while (bufferPos < end) {
        String path;
        time_t lastModified;
        String name;
        String desc;
        String mimeDesc;
        if (!(readUTF8String(path, bufferPos, end)
              && readTime(lastModified, bufferPos, end)
              && readUTF8String(name, bufferPos, end)
              && readUTF8String(desc, bufferPos, end)
              && readUTF8String(mimeDesc, bufferPos, end))) {
            LOG_ERROR("Unable to read plugin metadata cache: corrupt data");
            deleteFile(absoluteCachePath);
            return;
        }

        // Skip metadata that points to plugins from directories that
        // are not part of plugin directory list anymore.
        String pluginDirectoryName = directoryName(path);
        if (m_pluginDirectories.find(pluginDirectoryName) == WTF::notFound)
            continue;

        RefPtr<PluginPackage> package = PluginPackage::createPackageFromCache(path, lastModified, name, desc, mimeDesc);

        if (package && cachedPlugins.add(package).isNewEntry) {
            cachedPluginPathsWithTimes.add(package->path(), package->lastModified());
            cachedPluginsByPath.add(package->path(), package);
        }
    }

    m_plugins.swap(cachedPlugins);
    m_pluginsByPath.swap(cachedPluginsByPath);
    m_pluginPathsWithTimes.swap(cachedPluginPathsWithTimes);
}