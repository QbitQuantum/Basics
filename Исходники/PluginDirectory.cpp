void CPluginDirectory::LoadPluginStrings(const CURL &url)
{
  // Path where the plugin resides
  CStdString pathToPlugin = "U:\\plugins\\";
  CUtil::AddFileToFolder(pathToPlugin, url.GetHostName(), pathToPlugin);
  CUtil::AddFileToFolder(pathToPlugin, url.GetFileName(), pathToPlugin);

  // Replace the / at end, GetFileName() leaves a / at the end
  pathToPlugin.Replace("/", "\\");

  // Path where the language strings reside
  CStdString pathToLanguageFile = pathToPlugin;
  CStdString pathToFallbackLanguageFile = pathToPlugin;
  CUtil::AddFileToFolder(pathToLanguageFile, "resources", pathToLanguageFile);
  CUtil::AddFileToFolder(pathToFallbackLanguageFile, "resources", pathToFallbackLanguageFile);
  CUtil::AddFileToFolder(pathToLanguageFile, "language", pathToLanguageFile);
  CUtil::AddFileToFolder(pathToFallbackLanguageFile, "language", pathToFallbackLanguageFile);
  CUtil::AddFileToFolder(pathToLanguageFile, g_guiSettings.GetString("region.language"), pathToLanguageFile);
  CUtil::AddFileToFolder(pathToFallbackLanguageFile, "english", pathToFallbackLanguageFile);
  CUtil::AddFileToFolder(pathToLanguageFile, "strings.xml", pathToLanguageFile);
  CUtil::AddFileToFolder(pathToFallbackLanguageFile, "strings.xml", pathToFallbackLanguageFile);

  // Load language strings temporarily
  g_localizeStringsTemp.Load(pathToLanguageFile, pathToFallbackLanguageFile);
}