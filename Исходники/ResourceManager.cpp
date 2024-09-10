QImage* ResourceManager::getImage(QString path, bool recache)
{
    if (recache && sSourceImageHash.contains(path))
    {
        delete sSourceImageHash[path];
        sSourceImageHash.remove(path);
    }

    if (!sSourceImageHash.contains(path))
    {
        QString fullPath = getResourcePath(path, ResourceManager::FileType_Image);
        QFileInfo fileInfo = QFileInfo (fullPath);

        if (!fileInfo.isFile()) {return NULL;}
        try
        {
            sSourceImageHash.insert(path, new QImage(fullPath));
        }
        catch(char *str)
        {
            printf("File:%s couldn't be loaded.", str);
            return NULL;
        }
    };

    return sSourceImageHash[path];
}