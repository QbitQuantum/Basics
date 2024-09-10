extern "C" HRESULT __stdcall CallApplicationMain(PCALL_APPLICATION_MAIN_DATA data)
{
    auto trace_writer = dnx::trace_writer{ IsTracingEnabled() };

    SetEnvironmentVariable(L"DNX_FRAMEWORK", L"dnxcore50");

    Win32KDisable(trace_writer);

    auto runtime_directory = data->runtimeDirectory ? data->runtimeDirectory : GetModuleDirectory(nullptr);

    auto coreclr_module = LoadCoreClr(runtime_directory, trace_writer);
    if (!coreclr_module)
    {
        trace_writer.write(L"Failed to locate or load coreclr.dll", false);
        return E_FAIL;
    }

    ICLRRuntimeHost2* pCLRRuntimeHost = nullptr;

    HRESULT hr = GetClrRuntimeHost(coreclr_module, &pCLRRuntimeHost, trace_writer);
    if (FAILED(hr))
    {
        trace_writer.write(L"Failed to get IID_ICLRRuntimeHost2", false);
        return hr;
    }

    hr = StartClrHost(pCLRRuntimeHost, trace_writer);
    if (FAILED(hr))
    {
        trace_writer.write(L"Failed to start CLR host", false);
        return hr;
    }

    hr = ExecuteMain(pCLRRuntimeHost, data, runtime_directory, GetModuleDirectory(coreclr_module), trace_writer);
    if (FAILED(hr))
    {
        trace_writer.write(L"Failed to start CLR host", false);
        return hr;
    }

    hr = StopClrHost(pCLRRuntimeHost);
    if (FAILED(hr))
    {
        trace_writer.write(L"Failed to stop CLR host", false);
        return hr;
    }

    return S_OK;
}