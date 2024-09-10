void AssetDatabase::HandleFileChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace FileChanged;
    const String& fullPath = eventData[P_FILENAME].GetString();

    FileSystem* fs = GetSubsystem<FileSystem>();

    String pathName, fileName, ext;

    SplitPath(fullPath, pathName, fileName, ext);

    // ignore changes in the Cache resource dir
    if (fullPath == GetCachePath() || pathName.StartsWith(GetCachePath()))
        return;

    // don't care about directories and asset file changes
    if (fs->DirExists(fullPath) || ext == ".asset")
        return;

    Asset* asset = GetAssetByPath(fullPath);

    if (!asset && fs->FileExists(fullPath))
    {
        Scan();
        return;
    }

    if (asset)
    {
        if(!fs->Exists(fullPath))
        {
            DeleteAsset(asset);
        }
        else
        {
            if (asset->GetFileTimestamp() != fs->GetLastModifiedTime(asset->GetPath()))
            {
                asset->SetDirty(true);
                Scan();
            }
        }
    }
}