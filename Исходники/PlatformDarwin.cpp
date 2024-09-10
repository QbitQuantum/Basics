Error
PlatformDarwin::ResolveSymbolFile (Target &target,
                                   const ModuleSpec &sym_spec,
                                   FileSpec &sym_file)
{
    Error error;
    sym_file = sym_spec.GetSymbolFileSpec();
    if (sym_file.Exists())
    {
        if (sym_file.GetFileType() == FileSpec::eFileTypeDirectory)
        {
            sym_file = Symbols::FindSymbolFileInBundle (sym_file,
                                                        sym_spec.GetUUIDPtr(),
                                                        sym_spec.GetArchitecturePtr());
        }
    }
    else
    {
        if (sym_spec.GetUUID().IsValid())
        {
            
        }
    }
    return error;
    
}