std::string
getConfigDirectory()
{
   PWSTR path;
   auto result = std::string { "." };

   if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path))) {
      result = platform::fromWinApiString(path);
      CoTaskMemFree(path);
   }

   return result;
}