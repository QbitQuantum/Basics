bool CMetadataResolverMusic::FindLocalThumbnail(CResolvedAlbum& album, const CResolvingFolder& folder)
{
  // Go over all files in the folder that could be an album thumb (basically, picture files)
  for (int i = 0; i < (int)folder.vecThumbs.size(); i++)
  {
    CStdString strThumbFileName = CUtil::GetFileName(folder.vecThumbs[i]);

    // Get all possible thumbnail file names from the settings
    CStdStringArray thumbs;
    StringUtils::SplitString(g_advancedSettings.m_musicThumbs, "|", thumbs);
    for (unsigned int j = 0; j < thumbs.size(); ++j)
    {

      if (strThumbFileName.CompareNoCase(thumbs[j]) == 0)
      {
        album.strCover = folder.vecThumbs[i];
        return true;
      }
    }

    CUtil::RemoveExtension(strThumbFileName);

    // Handle the case that folder name is the same as the jpeg name
    if (strThumbFileName == folder.strEffectiveFolderName) 
    {
      album.strCover = folder.vecThumbs[i];
      return true;
    }

    if (strThumbFileName == album.strName)
    {
      album.strCover = folder.vecThumbs[i];
      return true;
    }

    if (strThumbFileName.ToLower() == "folder")
    {
      album.strCover = folder.vecThumbs[i];
      return true;
    }

    // TODO: Add more cases
  }

  return false;
}