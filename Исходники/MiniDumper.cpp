/// #ref : http://serious-code.net/moin.cgi/MiniDump
tstring GetFaultReason(PEXCEPTION_POINTERS exPtrs)
{
    if (::IsBadReadPtr(exPtrs, sizeof(EXCEPTION_POINTERS))) 
        return _T("bad exception pointers");

    // 간단한 에러 코드라면 그냥 변환할 수 있다.
    switch (exPtrs->ExceptionRecord->ExceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION:         return _T("EXCEPTION_ACCESS_VIOLATION");
    case EXCEPTION_DATATYPE_MISALIGNMENT:    return _T("EXCEPTION_DATATYPE_MISALIGNMENT");
    case EXCEPTION_BREAKPOINT:               return _T("EXCEPTION_BREAKPOINT");
    case EXCEPTION_SINGLE_STEP:              return _T("EXCEPTION_SINGLE_STEP");
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return _T("EXCEPTION_ARRAY_BOUNDS_EXCEEDED");
    case EXCEPTION_FLT_DENORMAL_OPERAND:     return _T("EXCEPTION_FLT_DENORMAL_OPERAND");
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return _T("EXCEPTION_FLT_DIVIDE_BY_ZERO");
    case EXCEPTION_FLT_INEXACT_RESULT:       return _T("EXCEPTION_FLT_INEXACT_RESULT");
    case EXCEPTION_FLT_INVALID_OPERATION:    return _T("EXCEPTION_FLT_INVALID_OPERATION");
    case EXCEPTION_FLT_OVERFLOW:             return _T("EXCEPTION_FLT_OVERFLOW");
    case EXCEPTION_FLT_STACK_CHECK:          return _T("EXCEPTION_FLT_STACK_CHECK");
    case EXCEPTION_FLT_UNDERFLOW:            return _T("EXCEPTION_FLT_UNDERFLOW");
    case EXCEPTION_INT_DIVIDE_BY_ZERO:       return _T("EXCEPTION_INT_DIVIDE_BY_ZERO");
    case EXCEPTION_INT_OVERFLOW:             return _T("EXCEPTION_INT_OVERFLOW");
    case EXCEPTION_PRIV_INSTRUCTION:         return _T("EXCEPTION_PRIV_INSTRUCTION");
    case EXCEPTION_IN_PAGE_ERROR:            return _T("EXCEPTION_IN_PAGE_ERROR");
    case EXCEPTION_ILLEGAL_INSTRUCTION:      return _T("EXCEPTION_ILLEGAL_INSTRUCTION");
    case EXCEPTION_NONCONTINUABLE_EXCEPTION: return _T("EXCEPTION_NONCONTINUABLE_EXCEPTION");
    case EXCEPTION_STACK_OVERFLOW:           return _T("EXCEPTION_STACK_OVERFLOW");
    case EXCEPTION_INVALID_DISPOSITION:      return _T("EXCEPTION_INVALID_DISPOSITION");
    case EXCEPTION_GUARD_PAGE:               return _T("EXCEPTION_GUARD_PAGE");
    case EXCEPTION_INVALID_HANDLE:           return _T("EXCEPTION_INVALID_HANDLE");
        //case EXCEPTION_POSSIBLE_DEADLOCK:        return _T("EXCEPTION_POSSIBLE_DEADLOCK");
    case CONTROL_C_EXIT:                     return _T("CONTROL_C_EXIT");
    case 0xE06D7363:                         return _T("Microsoft C++ Exception");
    default:
        break;
    }

    // 뭔가 좀 더 복잡한 에러라면...
    static TCHAR szFaultReason[2048];
    SPrintf(szFaultReason, 2048, _T("Unknown")); 
    ::FormatMessage(
        FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
        ::GetModuleHandle(_T("ntdll.dll")),
        exPtrs->ExceptionRecord->ExceptionCode, 
        0,
        szFaultReason,
        0,
        NULL);

    return szFaultReason;
}