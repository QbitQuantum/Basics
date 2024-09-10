bool
ProcessMachCore::CanDebug(Target &target, bool plugin_specified_by_name)
{
    if (plugin_specified_by_name)
        return true;

    // For now we are just making sure the file exists for a given module
    if (!m_core_module_sp && m_core_file.Exists())
    {
        ModuleSpec core_module_spec(m_core_file, target.GetArchitecture());
        Error error (ModuleList::GetSharedModule (core_module_spec, 
                                                  m_core_module_sp, 
                                                  NULL,
                                                  NULL, 
                                                  NULL));

        if (m_core_module_sp)
        {
            const llvm::Triple &triple_ref = m_core_module_sp->GetArchitecture().GetTriple();
            if (triple_ref.getVendor() == llvm::Triple::Apple)
            {
                ObjectFile *core_objfile = m_core_module_sp->GetObjectFile();
                if (core_objfile && core_objfile->GetType() == ObjectFile::eTypeCoreFile)
                    return true;
            }
        }
    }
    return false;
}