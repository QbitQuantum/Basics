bool HLSLCompiler::initialize()
{
#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
#if defined(ANGLE_PRELOADED_D3DCOMPILER_MODULE_NAMES)
    // Find a D3DCompiler module that had already been loaded based on a predefined list of versions.
    static const char *d3dCompilerNames[] = ANGLE_PRELOADED_D3DCOMPILER_MODULE_NAMES;

    for (size_t i = 0; i < ArraySize(d3dCompilerNames); ++i)
    {
        if (GetModuleHandleExA(0, d3dCompilerNames[i], &mD3DCompilerModule))
        {
            break;
        }
    }
#endif  // ANGLE_PRELOADED_D3DCOMPILER_MODULE_NAMES

    // Load the compiler DLL specified by the environment, or default to QT_D3DCOMPILER_DLL
    const wchar_t *defaultCompiler = _wgetenv(L"QT_D3DCOMPILER_DLL");
    if (!defaultCompiler)
        defaultCompiler = QT_D3DCOMPILER_DLL;

    const wchar_t *compilerDlls[] = {
        defaultCompiler,
        L"d3dcompiler_47.dll",
        L"d3dcompiler_46.dll",
        L"d3dcompiler_45.dll",
        L"d3dcompiler_44.dll",
        L"d3dcompiler_43.dll",
        0
    };

    // Load the first available known compiler DLL
    for (int i = 0; compilerDlls[i]; ++i)
    {
        mD3DCompilerModule = LoadLibrary(compilerDlls[i]);
        if (mD3DCompilerModule)
            break;
    }

    if (!mD3DCompilerModule)
    {
        // Load the version of the D3DCompiler DLL associated with the Direct3D version ANGLE was built with.
        mD3DCompilerModule = LoadLibrary(D3DCOMPILER_DLL);
    }

    if (!mD3DCompilerModule)
    {
        ERR("No D3D compiler module found - aborting!\n");
        return false;
    }

    mD3DCompileFunc = reinterpret_cast<pD3DCompile>(GetProcAddress(mD3DCompilerModule, "D3DCompile"));
    ASSERT(mD3DCompileFunc);

    mD3DDisassembleFunc = reinterpret_cast<pD3DDisassemble>(GetProcAddress(mD3DCompilerModule, "D3DDisassemble"));
    ASSERT(mD3DDisassembleFunc);

#else
    // D3D Shader compiler is linked already into this module, so the export
    // can be directly assigned.
    mD3DCompilerModule = NULL;
    mD3DCompileFunc = reinterpret_cast<pD3DCompile>(D3DCompile);
    mD3DDisassembleFunc = reinterpret_cast<pD3DDisassemble>(D3DDisassemble);
#endif

    return mD3DCompileFunc != NULL;
}