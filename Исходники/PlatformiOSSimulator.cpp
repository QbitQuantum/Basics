Error PlatformiOSSimulator::ResolveExecutable(
    const ModuleSpec &module_spec, lldb::ModuleSP &exe_module_sp,
    const FileSpecList *module_search_paths_ptr) {
    Error error;
    // Nothing special to do here, just use the actual file and architecture

    ModuleSpec resolved_module_spec(module_spec);

    // If we have "ls" as the exe_file, resolve the executable loation based on
    // the current path variables
    // TODO: resolve bare executables in the Platform SDK
    //    if (!resolved_exe_file.Exists())
    //        resolved_exe_file.ResolveExecutableLocation ();

    // Resolve any executable within a bundle on MacOSX
    // TODO: verify that this handles shallow bundles, if not then implement one
    // ourselves
    Host::ResolveExecutableInBundle(resolved_module_spec.GetFileSpec());

    if (resolved_module_spec.GetFileSpec().Exists()) {
        if (resolved_module_spec.GetArchitecture().IsValid()) {
            error = ModuleList::GetSharedModule(resolved_module_spec, exe_module_sp,
                                                NULL, NULL, NULL);

            if (exe_module_sp && exe_module_sp->GetObjectFile())
                return error;
            exe_module_sp.reset();
        }
        // No valid architecture was specified or the exact ARM slice wasn't
        // found so ask the platform for the architectures that we should be
        // using (in the correct order) and see if we can find a match that way
        StreamString arch_names;
        ArchSpec platform_arch;
        for (uint32_t idx = 0; GetSupportedArchitectureAtIndex(
                    idx, resolved_module_spec.GetArchitecture());
                ++idx) {
            // Only match x86 with x86 and x86_64 with x86_64...
            if (!module_spec.GetArchitecture().IsValid() ||
                    module_spec.GetArchitecture().GetCore() ==
                    resolved_module_spec.GetArchitecture().GetCore()) {
                error = ModuleList::GetSharedModule(resolved_module_spec, exe_module_sp,
                                                    NULL, NULL, NULL);
                // Did we find an executable using one of the
                if (error.Success()) {
                    if (exe_module_sp && exe_module_sp->GetObjectFile())
                        break;
                    else
                        error.SetErrorToGenericError();
                }

                if (idx > 0)
                    arch_names.PutCString(", ");
                arch_names.PutCString(platform_arch.GetArchitectureName());
            }
        }

        if (error.Fail() || !exe_module_sp) {
            if (resolved_module_spec.GetFileSpec().Readable()) {
                error.SetErrorStringWithFormat(
                    "'%s' doesn't contain any '%s' platform architectures: %s",
                    resolved_module_spec.GetFileSpec().GetPath().c_str(),
                    GetPluginName().GetCString(), arch_names.GetString().c_str());
            } else {
                error.SetErrorStringWithFormat(
                    "'%s' is not readable",
                    resolved_module_spec.GetFileSpec().GetPath().c_str());
            }
        }
    } else {
        error.SetErrorStringWithFormat("'%s' does not exist",
                                       module_spec.GetFileSpec().GetPath().c_str());
    }

    return error;
}