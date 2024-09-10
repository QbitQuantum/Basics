void ProcessFreeBSD::DoDidExec() {
  Target *target = &GetTarget();
  if (target) {
    PlatformSP platform_sp(target->GetPlatform());
    assert(platform_sp.get());
    if (platform_sp) {
      ProcessInstanceInfo process_info;
      platform_sp->GetProcessInfo(GetID(), process_info);
      ModuleSP exe_module_sp;
      ModuleSpec exe_module_spec(process_info.GetExecutableFile(),
                                 target->GetArchitecture());
      FileSpecList executable_search_paths(
          Target::GetDefaultExecutableSearchPaths());
      Status error = platform_sp->ResolveExecutable(
          exe_module_spec, exe_module_sp,
          executable_search_paths.GetSize() ? &executable_search_paths : NULL);
      if (!error.Success())
        return;
      target->SetExecutableModule(exe_module_sp, eLoadDependentsYes);
    }
  }
}