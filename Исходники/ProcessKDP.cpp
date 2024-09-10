bool
ProcessKDP::CanDebug(TargetSP target_sp, bool plugin_specified_by_name)
{
    if (plugin_specified_by_name)
        return true;

    // For now we are just making sure the file exists for a given module
    Module *exe_module = target_sp->GetExecutableModulePointer();
    if (exe_module)
    {
        const llvm::Triple &triple_ref = target_sp->GetArchitecture().GetTriple();
        switch (triple_ref.getOS())
        {
            case llvm::Triple::Darwin:  // Should use "macosx" for desktop and "ios" for iOS, but accept darwin just in case
            case llvm::Triple::MacOSX:  // For desktop targets
            case llvm::Triple::IOS:     // For arm targets
                if (triple_ref.getVendor() == llvm::Triple::Apple)
                {
                    ObjectFile *exe_objfile = exe_module->GetObjectFile();
                    if (exe_objfile->GetType() == ObjectFile::eTypeExecutable && 
                        exe_objfile->GetStrata() == ObjectFile::eStrataKernel)
                        return true;
                }
                break;

            default:
                break;
        }
    }
    return false;
}