/// Set to the unique library name
void TestPlugin::pluginName(UtlString& name) const
{
   assert(mConfigured);

   name.remove(0);
   name.append(LibraryName);
   name.append("::");
   name.append(mInstanceName);
}