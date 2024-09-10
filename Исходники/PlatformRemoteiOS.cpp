Error
PlatformRemoteiOS::GetSharedModule (const ModuleSpec &module_spec,
                                    ModuleSP &module_sp,
                                    const FileSpecList *module_search_paths_ptr,
                                    ModuleSP *old_module_sp_ptr,
                                    bool *did_create_ptr)
{
    // For iOS, the SDK files are all cached locally on the host
    // system. So first we ask for the file in the cached SDK,
    // then we attempt to get a shared module for the right architecture
    // with the right UUID.
    const FileSpec &platform_file = module_spec.GetFileSpec();

    FileSpec local_file;
    const UUID *module_uuid_ptr = module_spec.GetUUIDPtr();
    Error error (GetSymbolFile (platform_file, module_uuid_ptr, local_file));
    if (error.Success())
    {
        error = ResolveExecutable (local_file, module_spec.GetArchitecture(), module_sp, NULL);
        if (module_sp && ((module_uuid_ptr == NULL) || (module_sp->GetUUID() == *module_uuid_ptr)))
        {
            //printf ("found in user specified SDK\n");
            error.Clear();
            return error;
        }

        char platform_file_path[PATH_MAX];
        if (platform_file.GetPath(platform_file_path, sizeof(platform_file_path)))
        {
            FileSpec local_file;
            const uint32_t num_sdk_infos = m_sdk_directory_infos.size();
            // Try the last SDK index if it is set as most files from an SDK
            // will tend to be valid in that same SDK.
            if (m_last_module_sdk_idx < num_sdk_infos)
            {
                if (GetFileInSDK (platform_file_path, m_last_module_sdk_idx, local_file))
                {
                    //printf ("sdk[%u] last: '%s'\n", m_last_module_sdk_idx, local_file.GetPath().c_str());
                    module_sp.reset();
                    error = ResolveExecutable (local_file,
                                               module_spec.GetArchitecture(),
                                               module_sp,
                                               NULL);
                    if (module_sp && ((module_uuid_ptr == NULL) || (module_sp->GetUUID() == *module_uuid_ptr)))
                    {
                        //printf ("sdk[%u] last found\n", m_last_module_sdk_idx);
                        error.Clear();
                        return error;
                    }
                }
            }
            
            // First try for an exact match of major, minor and update
            for (uint32_t sdk_idx=0; sdk_idx<num_sdk_infos; ++sdk_idx)
            {
                if (m_last_module_sdk_idx == sdk_idx)
                {
                    // Skip the last module SDK index if we already searched
                    // it above
                    continue;
                }
                if (GetFileInSDK (platform_file_path, sdk_idx, local_file))
                {
                    //printf ("sdk[%u]: '%s'\n", sdk_idx, local_file.GetPath().c_str());
                    
                    error = ResolveExecutable (local_file,
                                               module_spec.GetArchitecture(),
                                               module_sp,
                                               NULL);
                    if (module_sp && ((module_uuid_ptr == NULL) || (module_sp->GetUUID() == *module_uuid_ptr)))
                    {
                        // Remember the index of the last SDK that we found a file
                        // in in case the wrong SDK was selected.
                        m_last_module_sdk_idx = sdk_idx;
                        //printf ("sdk[%u]: found (setting last to %u)\n", sdk_idx, m_last_module_sdk_idx);
                        error.Clear();
                        return error;
                    }
                }
            }
        }
        // Not the module we are looking for... Nothing to see here...
        module_sp.reset();
    }
    else
    {
        // This may not be an SDK-related module.  Try whether we can bring in the thing to our local cache.
        error = GetSharedModuleWithLocalCache(module_spec, module_sp, module_search_paths_ptr, old_module_sp_ptr, did_create_ptr);
        if (error.Success())
            return error;
        else
            error.Clear(); // Clear the error and fall-through.
    }

    const bool always_create = false;
    error = ModuleList::GetSharedModule (module_spec, 
                                         module_sp,
                                         module_search_paths_ptr,
                                         old_module_sp_ptr,
                                         did_create_ptr,
                                         always_create);

    if (module_sp)
        module_sp->SetPlatformFileSpec(platform_file);

    return error;
}