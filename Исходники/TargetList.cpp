Error
TargetList::CreateTargetInternal (Debugger &debugger,
                                  const char *user_exe_path,
                                  const ArchSpec& specified_arch,
                                  bool get_dependent_files,
                                  lldb::PlatformSP &platform_sp,
                                  lldb::TargetSP &target_sp,
                                  bool is_dummy_target)
{

    Timer scoped_timer (__PRETTY_FUNCTION__,
                        "TargetList::CreateTarget (file = '%s', arch = '%s')",
                        user_exe_path,
                        specified_arch.GetArchitectureName());
    Error error;

    ArchSpec arch(specified_arch);

    if (arch.IsValid())
    {
        if (!platform_sp || !platform_sp->IsCompatibleArchitecture(arch, false, NULL))
            platform_sp = Platform::GetPlatformForArchitecture(specified_arch, &arch);
    }
    
    if (!platform_sp)
        platform_sp = debugger.GetPlatformList().GetSelectedPlatform();

    if (!arch.IsValid())
        arch = specified_arch;

    FileSpec file (user_exe_path, false);
    if (!file.Exists() && user_exe_path && user_exe_path[0] == '~')
    {
        // we want to expand the tilde but we don't want to resolve any symbolic links
        // so we can't use the FileSpec constructor's resolve flag
        llvm::SmallString<64> unglobbed_path(user_exe_path);
        FileSpec::ResolveUsername(unglobbed_path);

        if (unglobbed_path.empty())
            file = FileSpec(user_exe_path, false);
        else
            file = FileSpec(unglobbed_path.c_str(), false);
    }

    bool user_exe_path_is_bundle = false;
    char resolved_bundle_exe_path[PATH_MAX];
    resolved_bundle_exe_path[0] = '\0';
    if (file)
    {
        if (file.GetFileType() == FileSpec::eFileTypeDirectory)
            user_exe_path_is_bundle = true;

        if (file.IsRelative() && user_exe_path)
        {
            // Ignore paths that start with "./" and "../"
            if (!((user_exe_path[0] == '.' && user_exe_path[1] == '/') ||
                  (user_exe_path[0] == '.' && user_exe_path[1] == '.' && user_exe_path[2] == '/')))
            {
                char cwd[PATH_MAX];
                if (getcwd (cwd, sizeof(cwd)))
                {
                    std::string cwd_user_exe_path (cwd);
                    cwd_user_exe_path += '/';
                    cwd_user_exe_path += user_exe_path;
                    FileSpec cwd_file (cwd_user_exe_path.c_str(), false);
                    if (cwd_file.Exists())
                        file = cwd_file;
                }
            }
        }

        ModuleSP exe_module_sp;
        if (platform_sp)
        {
            FileSpecList executable_search_paths (Target::GetDefaultExecutableSearchPaths());
            ModuleSpec module_spec(file, arch);
            error = platform_sp->ResolveExecutable (module_spec,
                                                    exe_module_sp, 
                                                    executable_search_paths.GetSize() ? &executable_search_paths : NULL);
        }

        if (error.Success() && exe_module_sp)
        {
            if (exe_module_sp->GetObjectFile() == NULL)
            {
                if (arch.IsValid())
                {
                    error.SetErrorStringWithFormat("\"%s\" doesn't contain architecture %s",
                                                   file.GetPath().c_str(),
                                                   arch.GetArchitectureName());
                }
                else
                {
                    error.SetErrorStringWithFormat("unsupported file type \"%s\"",
                                                   file.GetPath().c_str());
                }
                return error;
            }
            target_sp.reset(new Target(debugger, arch, platform_sp, is_dummy_target));
            target_sp->SetExecutableModule (exe_module_sp, get_dependent_files);
            if (user_exe_path_is_bundle)
                exe_module_sp->GetFileSpec().GetPath(resolved_bundle_exe_path, sizeof(resolved_bundle_exe_path));
        }
    }
    else
    {
        // No file was specified, just create an empty target with any arch
        // if a valid arch was specified
        target_sp.reset(new Target(debugger, arch, platform_sp, is_dummy_target));
    }

    if (target_sp)
    {
        // Set argv0 with what the user typed, unless the user specified a
        // directory. If the user specified a directory, then it is probably a
        // bundle that was resolved and we need to use the resolved bundle path
        if (user_exe_path)
        {
            // Use exactly what the user typed as the first argument when we exec or posix_spawn
            if (user_exe_path_is_bundle && resolved_bundle_exe_path[0])
            {
                target_sp->SetArg0 (resolved_bundle_exe_path);
            }
            else
            {
                // Use resolved path
                target_sp->SetArg0 (file.GetPath().c_str());
            }
        }
        if (file.GetDirectory())
        {
            FileSpec file_dir;
            file_dir.GetDirectory() = file.GetDirectory();
            target_sp->GetExecutableSearchPaths ().Append (file_dir);
        }

        // Don't put the dummy target in the target list, it's held separately.
        if (!is_dummy_target)
        {
            Mutex::Locker locker(m_target_list_mutex);
            m_selected_target_idx = m_target_list.size();
            m_target_list.push_back(target_sp);
            // Now prime this from the dummy target:
            target_sp->PrimeFromDummyTarget(debugger.GetDummyTarget());
        }
        else
        {
            m_dummy_target_sp = target_sp;
        }
    }

    return error;
}