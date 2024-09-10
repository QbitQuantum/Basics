ModuleSP DynamicLoader::GetTargetExecutable() {
  Target &target = m_process->GetTarget();
  ModuleSP executable = target.GetExecutableModule();

  if (executable) {
    if (FileSystem::Instance().Exists(executable->GetFileSpec())) {
      ModuleSpec module_spec(executable->GetFileSpec(),
                             executable->GetArchitecture());
      auto module_sp = std::make_shared<Module>(module_spec);

      // Check if the executable has changed and set it to the target
      // executable if they differ.
      if (module_sp && module_sp->GetUUID().IsValid() &&
          executable->GetUUID().IsValid()) {
        if (module_sp->GetUUID() != executable->GetUUID())
          executable.reset();
      } else if (executable->FileHasChanged()) {
        executable.reset();
      }

      if (!executable) {
        executable = target.GetOrCreateModule(module_spec, true /* notify */);
        if (executable.get() != target.GetExecutableModulePointer()) {
          // Don't load dependent images since we are in dyld where we will
          // know and find out about all images that are loaded
          target.SetExecutableModule(executable, eLoadDependentsNo);
        }
      }
    }
  }
  return executable;
}