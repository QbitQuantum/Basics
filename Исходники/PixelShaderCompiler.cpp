HRESULT CPixelShaderCompiler::InternalCompile(
    LPCSTR pSrcData,
    SIZE_T SrcDataSize,
    LPCSTR pSourceName,
    LPCSTR pEntrypoint,
    LPCSTR pProfile,
    DWORD Flags,
    IDirect3DPixelShader9** ppPixelShader,
    CString* pDisasm,
    CString* pErrMsg)
{
    if (!m_pD3DCompile) {
        return E_FAIL;
    }

    if (pDisasm && !m_pD3DDisassemble) {
        return E_FAIL;
    }

    if (ppPixelShader && !m_pD3DDev) {
        return E_FAIL;
    }

    LPCSTR pSelProfile = pProfile;
    if (!pSelProfile || *pSelProfile == '\0') {
        D3DCAPS9 caps;
        if (m_pD3DDev && m_pD3DDev->GetDeviceCaps(&caps) == D3D_OK) {
            switch (D3DSHADER_VERSION_MAJOR(caps.PixelShaderVersion)) {
                case 2:
                    if (caps.PS20Caps.NumInstructionSlots < 512) {
                        pSelProfile = "ps_2_0";
                    } else if (caps.PS20Caps.Caps > 0) {
                        pSelProfile = "ps_2_a";
                    } else {
                        pSelProfile = "ps_2_b";
                    }
                    break;
                case 3:
                    pSelProfile = "ps_3_0";
                    break;
            }
        } else {
            ASSERT(FALSE);
        }
    }

    if (!pSelProfile || *pSelProfile == '\0') {
        return E_FAIL;
    }

    LPCSTR defProfile = "MPC_HC_SHADER_PROFILE";
    LPCSTR defProfileVal;
    if (!strcmp(pSelProfile, "ps_2_0")) {
        defProfileVal = "0";
    } else if (!strcmp(pSelProfile, "ps_2_b")) {
        defProfileVal = "1";
    } else if (!strcmp(pSelProfile, "ps_2_a") || !strcmp(pSelProfile, "ps_2_sw")) {
        defProfileVal = "2";
    } else if (!strcmp(pSelProfile, "ps_3_0") || !strcmp(pSelProfile, "ps_3_sw")) {
        defProfileVal = "3";
    } else {
        defProfileVal = "-1";
    }

    if (ppPixelShader && SUCCEEDED(m_Cache.CreatePixelShader(defProfileVal, pSrcData, SrcDataSize, ppPixelShader))) {
        return S_OK;
    }

    D3D_SHADER_MACRO macros[] = { { defProfile, defProfileVal }, { 0 } };

    CComPtr<ID3DBlob> pShaderBlob, pErrorBlob;
    HRESULT hr = m_pD3DCompile(pSrcData, SrcDataSize, pSourceName, macros, nullptr, pEntrypoint,
                               pSelProfile, Flags, 0, &pShaderBlob, &pErrorBlob);

    if (pErrMsg) {
        CStringA msg;
        if (pErrorBlob) {
            auto len = pErrorBlob->GetBufferSize();
            VERIFY(memcpy_s(msg.GetBufferSetLength((int)len), len, pErrorBlob->GetBufferPointer(), len) == 0);
            msg.ReleaseBuffer((int)len);
        }
        *pErrMsg = msg;
    }

    if (FAILED(hr)) {
        return hr;
    }

    if (ppPixelShader) {
        hr = m_pD3DDev->CreatePixelShader((DWORD*)pShaderBlob->GetBufferPointer(), ppPixelShader);
        if (FAILED(hr)) {
            return hr;
        }

        m_Cache.SavePixelShader(defProfileVal, pSrcData, SrcDataSize,
                                (void*)pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize());
    }

    if (pDisasm) {
        CComPtr<ID3DBlob> pDisasmBlob;
        CStringA defs;
        for (auto pMacro = macros; pMacro && pMacro->Name && pMacro->Definition; pMacro++) {
            defs.Append("// #define ");
            defs.Append(pMacro->Name);
            defs.Append(" ");
            defs.Append(pMacro->Definition);
            defs.Append("\n");
        }
        hr = m_pD3DDisassemble(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(),
                               0, defs, &pDisasmBlob);
        if (SUCCEEDED(hr)) {
            CStringA disasm;
            auto len = pDisasmBlob->GetBufferSize();
            VERIFY(memcpy_s(disasm.GetBufferSetLength((int)len), len, pDisasmBlob->GetBufferPointer(), len) == 0);
            disasm.ReleaseBuffer((int)len);
            *pDisasm = disasm;
        }
    }

    return S_OK;
}