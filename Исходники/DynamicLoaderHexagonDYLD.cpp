/// Checks to see if the target module has changed, updates the target
/// accordingly and returns the target executable module.
ModuleSP
DynamicLoaderHexagonDYLD::GetTargetExecutable()
{
    Target &target = m_process->GetTarget();
    ModuleSP executable = target.GetExecutableModule();

    // There is no executable
    if (! executable.get())
        return executable;

    // The target executable file does not exits
    if (! executable->GetFileSpec().Exists())
        return executable;
    
    // Prep module for loading
    ModuleSpec module_spec(executable->GetFileSpec(), executable->GetArchitecture());
    ModuleSP   module_sp  (new Module (module_spec));

    // Check if the executable has changed and set it to the target executable if they differ.
    if (module_sp.get() && module_sp->GetUUID().IsValid() && executable->GetUUID().IsValid())
    {
        // if the executable has changed ??
        if (module_sp->GetUUID() != executable->GetUUID())
            executable.reset();
    }
    else if (executable->FileHasChanged())
        executable.reset();

    if ( executable.get( ) )
        return executable;

    // TODO: What case is this code used?
    executable = target.GetSharedModule(module_spec);
    if (executable.get() != target.GetExecutableModulePointer())
    {
        // Don't load dependent images since we are in dyld where we will know
        // and find out about all images that are loaded
        const bool get_dependent_images = false;
        target.SetExecutableModule(executable, get_dependent_images);
    }
    
    return executable;
}