HRESULT WINAPI
OutOfProcessExceptionEventSignatureCallback (
  /* __in    */ PVOID pContext,
  /* __in    */ const PWER_RUNTIME_EXCEPTION_INFORMATION pExceptionInformation,
  /* __in    */ DWORD dwIndex,
  /* __out   */ PWSTR pwszName,
  /* __inout */ PDWORD pchName,
  /* __out   */ PWSTR pwszValue,
  /* __inout */ PDWORD pchValue
)

/*++

Routine Description:

    WER can call this function multiple times to get the report parameters that uniquely describe the
    problem.

    The PFN_WER_RUNTIME_EXCEPTION_EVENT_SIGNATURE type defines a pointer to this callback function.

    This function will be exported out of this DLL, as specified by HandlerDll.def.

Arguments:

    pContext - An arbitrary pointer-sized value that was passed in to WerRegisterRuntimeExceptionModule.

    pExceptionInformation - A WER_RUNTIME_EXCEPTION_INFORMATION structure that contains the exception
        information.

    dwIndex - The index of the report parameter. Valid values are 0 to 9.

    pwszName - A caller-allocated buffer that you use to specify the parameter name.

    pchName - A pointer to a DWORD specifying the size, in characters, of the pwszName buffer. The size includes
        the null-terminating character.

    pwszValue - A caller-allocated buffer that you use to specify the parameter value.

    pchValue - A pointer to a DWORD specifying the size, in characters, of the pwszValue buffer. The size includes
        the null-terminating character.

Return Value:

    HRESULT.

--*/

{
    UNREFERENCED_PARAMETER (pContext);


    //
    // Some sanity checks. Our handler only specifies 2 signature pairs.
    //
    if (dwIndex >= 2
        || (0xABCD1234 != pExceptionInformation->exceptionRecord.ExceptionCode)) {

        return E_UNEXPECTED;
    }

    //
    // Make sure the given buffers are large enough to hold our signature name/value pairs.
    // We will need 4 characters (3 characters + 1 null-terminator) for our fixed strings.
    //
    if (*pchName < 4) {
        *pchName = 4;
        return HRESULT_FROM_WIN32 (ERROR_INSUFFICIENT_BUFFER);
    }

    if (*pchValue < 4) {
        *pchValue = 4;
        return HRESULT_FROM_WIN32 (ERROR_INSUFFICIENT_BUFFER);
    }

    //
    // At this point, we should fill in the problem signature with the data from the crashing process.
    //
    // For example, the signature can uniquely identify where the crash happened. If our application runs
    // custom-compiled code, we can let the signature identify what module/class/line/etc the crash
    // happened at. This can be done by exposing an easily-accessible data structure in the process, and
    // reading the structure using ReadProcessMemory.
    //
    // In here, we will simply set the signature to some fixed strings.
    //
    switch (dwIndex) {
      case 0:
        wcscpy_s (pwszName, *pchName, L"one");
        wcscpy_s (pwszValue, *pchValue, L"111");
        break;

      case 1:
        wcscpy_s (pwszName, *pchName, L"two");
        wcscpy_s (pwszValue, *pchValue, L"222");
        break;

      default:
        UNREACHABLE_CODE ();
    }

    return S_OK;
}