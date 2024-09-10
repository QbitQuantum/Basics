Error
PlatformDarwinKernel::GetSharedModule (const ModuleSpec &module_spec,
                                       Process *process,
                                       ModuleSP &module_sp,
                                       const FileSpecList *module_search_paths_ptr,
                                       ModuleSP *old_module_sp_ptr,
                                       bool *did_create_ptr)
{
    Error error;
    module_sp.reset();
    const FileSpec &platform_file = module_spec.GetFileSpec();

    // Treat the file's path as a kext bundle ID (e.g. "com.apple.driver.AppleIRController") and search our kext index.
    std::string kext_bundle_id = platform_file.GetPath();
    if (!kext_bundle_id.empty())
    {
        ConstString kext_bundle_cs(kext_bundle_id.c_str());
        if (m_name_to_kext_path_map.count(kext_bundle_cs) > 0)
        {
            for (BundleIDToKextIterator it = m_name_to_kext_path_map.begin (); it != m_name_to_kext_path_map.end (); ++it)
            {
                if (it->first == kext_bundle_cs)
                {
                    error = ExamineKextForMatchingUUID (it->second, module_spec.GetUUID(), module_spec.GetArchitecture(), module_sp);
                    if (module_sp.get())
                    {
                        return error;
                    }
                }
            }
        }
    }

    if (kext_bundle_id.compare("mach_kernel") == 0 && module_spec.GetUUID().IsValid())
    {
        for (auto possible_kernel : m_kernel_binaries)
        {
            if (possible_kernel.Exists())
            {
                ModuleSpec kern_spec (possible_kernel);
                kern_spec.GetUUID() = module_spec.GetUUID();
                ModuleSP module_sp (new Module (kern_spec));
                if (module_sp && module_sp->GetObjectFile() && module_sp->MatchesModuleSpec (kern_spec))
                {
                    Error error;
                    error = ModuleList::GetSharedModule (kern_spec, module_sp, NULL, NULL, NULL);
                    if (module_sp && module_sp->GetObjectFile())
                    {
                        return error;
                    }
                }
            }
        }
    }

    // Else fall back to treating the file's path as an actual file path - defer to PlatformDarwin's GetSharedModule.
    return PlatformDarwin::GetSharedModule (module_spec, process, module_sp, module_search_paths_ptr, old_module_sp_ptr, did_create_ptr);
}