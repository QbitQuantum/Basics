/**
 * Loads the plugin into memory using NSPR's shared-library loading
 * mechanism. Handles platform differences in loading shared libraries.
 */
nsresult nsPluginFile::LoadPlugin(PRLibrary **outLibrary)
{
  nsCOMPtr<nsILocalFile> plugin = do_QueryInterface(mPlugin);

  if (!plugin)
    return NS_ERROR_NULL_POINTER;

  PRBool protectCurrentDirectory = PR_TRUE;

  nsAutoString pluginFolderPath;
  plugin->GetPath(pluginFolderPath);

  PRInt32 idx = pluginFolderPath.RFindChar('\\');
  if (kNotFound == idx)
    return NS_ERROR_FILE_INVALID_PATH;

  if (Substring(pluginFolderPath, idx).LowerCaseEqualsLiteral("\\np32dsw.dll")) {
    protectCurrentDirectory = PR_FALSE;
  }

  pluginFolderPath.SetLength(idx);

  BOOL restoreOrigDir = FALSE;
  WCHAR aOrigDir[MAX_PATH + 1];
  DWORD dwCheck = GetCurrentDirectoryW(MAX_PATH, aOrigDir);
  NS_ASSERTION(dwCheck <= MAX_PATH + 1, "Error in Loading plugin");

  if (dwCheck <= MAX_PATH + 1) {
    restoreOrigDir = SetCurrentDirectoryW(pluginFolderPath.get());
    NS_ASSERTION(restoreOrigDir, "Error in Loading plugin");
  }

  if (protectCurrentDirectory) {
    mozilla::NS_SetDllDirectory(NULL);
  }

  nsresult rv = plugin->Load(outLibrary);
  if (NS_FAILED(rv))
      *outLibrary = NULL;

  if (protectCurrentDirectory) {
    mozilla::NS_SetDllDirectory(L"");
  }

  if (restoreOrigDir) {
    BOOL bCheck = SetCurrentDirectoryW(aOrigDir);
    NS_ASSERTION(bCheck, "Error in Loading plugin");
  }

  return rv;
}