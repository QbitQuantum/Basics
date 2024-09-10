IdentInterface *ModuleManager::CreateProviderInstance(const PluginID & providerID,
                                                      const wxString & path)
{
   if (path.IsEmpty() && mDynModules.find(providerID) != mDynModules.end())
   {
      return mDynModules[providerID];
   }

   return LoadModule(path);
}