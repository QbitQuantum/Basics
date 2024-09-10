Error
ModuleCache::Put (const FileSpec &root_dir_spec,
                  const char *hostname,
                  const ModuleSpec &module_spec,
                  const FileSpec &tmp_file)
{
    const auto module_spec_dir = GetModuleDirectory (root_dir_spec, module_spec.GetUUID ());
    auto error = MakeDirectory (module_spec_dir);
    if (error.Fail ())
        return error;

    const auto module_file_path = JoinPath (module_spec_dir, module_spec.GetFileSpec ().GetFilename ().AsCString ());

    const auto tmp_file_path = tmp_file.GetPath ();
    const auto err_code = llvm::sys::fs::copy_file (tmp_file_path.c_str (), module_file_path.GetPath ().c_str ());
    if (err_code)
    {
        error.SetErrorStringWithFormat ("failed to copy file %s to %s: %s",
                                        tmp_file_path.c_str (),
                                        module_file_path.GetPath ().c_str (),
                                        err_code.message ().c_str ());
    }

    // Create sysroot link to a module.
    const auto sysroot_module_path_spec = GetHostSysRootModulePath (root_dir_spec, hostname, module_spec.GetFileSpec ());
    return CreateHostSysRootModuleSymLink (sysroot_module_path_spec, module_file_path);
}