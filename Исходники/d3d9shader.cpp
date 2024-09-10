void DumpShader(trace::Writer &writer, const DWORD *tokens)
{
    static BOOL firsttime = TRUE;

    /*
     * TODO: Consider using d3dcompile_xx.dll per
     * http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx
     */

    static HMODULE hD3DXModule = NULL;
    static PD3DXDISASSEMBLESHADER pfnD3DXDisassembleShader = NULL;

    if (firsttime) {
        if (!hD3DXModule) {
            unsigned release;
            int version;
            for (release = 0; release <= 1; ++release) {
                /* Version 41 corresponds to Mar 2009 version of DirectX Runtime / SDK */
                for (version = 41; version >= 0; --version) {
                    char filename[256];
                    _snprintf(filename, sizeof(filename),
                              "d3dx9%s%s%u.dll", release ? "" : "d", version ? "_" : "", version);
                    hD3DXModule = LoadLibraryA(filename);
                    if (hD3DXModule)
                        goto found;
                }
            }
found:
            ;
        }

        if (hD3DXModule) {
            if (!pfnD3DXDisassembleShader) {
                pfnD3DXDisassembleShader = (PD3DXDISASSEMBLESHADER)GetProcAddress(hD3DXModule, "D3DXDisassembleShader");
            }
        }

        firsttime = FALSE;
    }

    LPD3DXBUFFER pDisassembly = NULL;
    HRESULT hr = E_FAIL;

    if (pfnD3DXDisassembleShader) {
        hr = pfnD3DXDisassembleShader(tokens, FALSE, NULL, &pDisassembly);
    }

    if (SUCCEEDED(hr)) {
        writer.beginRepr();
        writer.writeString((const char *)pDisassembly->GetBufferPointer(), pDisassembly->GetBufferSize());
    }

    writer.writeBlob(tokens, _shaderSize(tokens));

    if (pDisassembly) {
        pDisassembly->Release();
    }
    
    if (SUCCEEDED(hr)) {
        writer.endRepr();
    }
}