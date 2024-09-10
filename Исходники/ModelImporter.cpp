bool ModelImporter::ImportAnimations()
{
    if (!animationInfo_.Size())
    {
       if (!ImportAnimation(asset_->GetPath(), "RootAnim"))
           return false;
    }

    // embedded animations
    for (unsigned i = 0; i < animationInfo_.Size(); i++)
    {
        const SharedPtr<AnimationImportInfo>& info = animationInfo_[i];
        if (!ImportAnimation(asset_->GetPath(), info->GetName(), info->GetStartTime(), info->GetEndTime()))
            return false;
    }

    // add @ animations

    FileSystem* fs = GetSubsystem<FileSystem>();
    String pathName, fileName, ext;
    SplitPath(asset_->GetPath(), pathName, fileName, ext);

    Vector<String> results;

    fs->ScanDir(results, pathName, ext, SCAN_FILES, false);

    for (unsigned i = 0; i < results.Size(); i++)
    {
        const String& result = results[i];

        if (result.Contains("@"))
        {
            Vector<String> components = GetFileName(result).Split('@');

            if (components.Size() == 2 && components[1].Length() && components[0] == fileName)
            {
                String animationName = components[1];
                AssetDatabase* db = GetSubsystem<AssetDatabase>();
                Asset* asset = db->GetAssetByPath(pathName + result);
                assert(asset);
                assert(asset->GetImporter()->GetType() == ModelImporter::GetTypeStatic());

                ModelImporter* importer = (ModelImporter*) asset->GetImporter();

                if (!importer->animationInfo_.Size())
                {
                   if (!ImportAnimation(asset->GetPath(), animationName))
                       return false;
                }
                else
                {
                    // embedded animations
                    for (unsigned i = 0; i < importer->animationInfo_.Size(); i++)
                    {
                        const SharedPtr<AnimationImportInfo>& info = importer->animationInfo_[i];
                        if (!ImportAnimation(asset->GetPath(), info->GetName(), info->GetStartTime(), info->GetEndTime()))
                            return false;
                    }
                }


            }
        }
    }



    return true;
}