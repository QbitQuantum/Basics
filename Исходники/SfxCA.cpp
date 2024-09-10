/// <summary>
/// Loads and invokes the managed portion of the proxy.
/// </summary>
/// <param name="hSession">Handle to the installer session,
/// used for logging errors and to be passed on to the custom action.</param>
/// <param name="pAppDomain">AppDomain which has its application
/// base set to the CA working directory.</param>
/// <param name="szEntryPoint">Name of the CA entrypoint to be invoked.
/// This must be either an explicit &quot;AssemblyName!Namespace.Class.Method&quot;
/// string, or a simple name that maps to a full entrypoint definition
/// in CustomAction.config.</param>
/// <param name="piResult">Return value of the invoked custom
/// action method.</param>
/// <returns>True if the managed proxy was invoked successfully,
/// false if there was some error. Note the custom action itself may
/// return an error via piResult while this method still returns true
/// since the invocation was successful.</returns>
bool InvokeManagedCustomAction(MSIHANDLE hSession, _AppDomain* pAppDomain,
        const wchar_t* szEntryPoint, int* piResult)
{
        VARIANT vResult;
        ::VariantInit(&vResult);

        const bool f64bit = (sizeof(void*) == sizeof(LONGLONG));
        const wchar_t* szMsiAssemblyName   = L"Microsoft.Deployment.WindowsInstaller";
        const wchar_t* szMsiCAProxyClass   = L"Microsoft.Deployment.WindowsInstaller.CustomActionProxy";
        const wchar_t* szMsiCAInvokeMethod = (f64bit ? L"InvokeCustomAction64" : L"InvokeCustomAction32");
        
        _MethodInfo* pCAInvokeMethod;
        if (!GetMethod(hSession, pAppDomain, szMsiAssemblyName,
                szMsiCAProxyClass, szMsiCAInvokeMethod, &pCAInvokeMethod))
        {
                return false;
        }

        HRESULT hr;
        VARIANT vNull;
        vNull.vt = VT_EMPTY;
        SAFEARRAY* saArgs = SafeArrayCreateVector(VT_VARIANT, 0, 3);
        VARIANT vSessionHandle;
        vSessionHandle.vt = VT_I4;
        vSessionHandle.intVal = hSession;
        LONG index = 0;
        hr = SafeArrayPutElement(saArgs, &index, &vSessionHandle);
        if (FAILED(hr)) goto LExit;
        VARIANT vEntryPoint;
        vEntryPoint.vt = VT_BSTR;
        vEntryPoint.bstrVal = SysAllocString(szEntryPoint);
        if (vEntryPoint.bstrVal == NULL)
        {
                hr = E_OUTOFMEMORY;
                goto LExit;
        }
        index = 1;
        hr = SafeArrayPutElement(saArgs, &index, &vEntryPoint);
        if (FAILED(hr)) goto LExit;
        VARIANT vRemotingFunctionPtr;
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
        if (f64bit)
#pragma warning(pop)
        {
                vRemotingFunctionPtr.vt =  VT_I8;
                vRemotingFunctionPtr.llVal = (LONGLONG) (g_fRunningOutOfProc ? MsiRemoteInvoke : NULL);
        }
        else
        {
                vRemotingFunctionPtr.vt =  VT_I4;
#pragma warning(push)
#pragma warning(disable:4302) // truncation
#pragma warning(disable:4311) // pointer truncation
                vRemotingFunctionPtr.lVal = (LONG) (g_fRunningOutOfProc ? MsiRemoteInvoke : NULL);
#pragma warning(pop)
        }
        index = 2;
        hr = SafeArrayPutElement(saArgs, &index, &vRemotingFunctionPtr);
        if (FAILED(hr)) goto LExit;
        
        hr = pCAInvokeMethod->Invoke_3(vNull, saArgs, &vResult);

LExit:
        SafeArrayDestroy(saArgs);
        pCAInvokeMethod->Release();
        
        if (FAILED(hr))
        {
                Log(hSession, L"Failed to invoke custom action method. Error code 0x%X", hr);
                return false;
        }

        *piResult = vResult.intVal;
        return true;
}