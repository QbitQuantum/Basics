// start loading based on the vector of library names.  First success
// terminates the loading attempts.  Needed for CentOS6 and OpenCL.
// The Catalyst installer (at least in Catalyst 12.1) creates libOpenCL.so.1
// but no symbolic link to libOpenCL.so.  This symbolic link exists on other
// distributions where multi-step repackaging is required (build a .deb, run it)
bool DynamicLibraryModule::LoadModule(const std::vector<std::string>& names)
{
    bool    loaded = false;

    for (std::vector<std::string>::const_iterator it = names.begin(); it != names.end(); it++)
    {
        loaded = LoadModule(*it);

        if (loaded)
        {
            return loaded;
        }
    }

    return loaded;
}