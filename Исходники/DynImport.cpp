/// <summary>
/// Load function into database
/// </summary>
/// <param name="name">Function name</param>
/// <param name="module">Module name</param>
/// <returns>true on success</returns>
FARPROC DynImport::load( const std::string& name, const std::wstring& module )
{
    auto mod = GetModuleHandleW( module.c_str() );
    return load( name, mod );
}