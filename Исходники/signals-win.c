static LONG WINAPI _exception_handler(struct _EXCEPTION_POINTERS *ExceptionInfo, int in_ctx)
{
    jl_ptls_t ptls = jl_get_ptls_states();
    if (ExceptionInfo->ExceptionRecord->ExceptionFlags == 0) {
        switch (ExceptionInfo->ExceptionRecord->ExceptionCode) {
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
                fpreset();
                jl_throw_in_ctx(jl_diverror_exception,
                    ExceptionInfo->ContextRecord,in_ctx);
                return EXCEPTION_CONTINUE_EXECUTION;
            case EXCEPTION_STACK_OVERFLOW:
                jl_throw_in_ctx(jl_stackovf_exception,
                    ExceptionInfo->ContextRecord,in_ctx&&pSetThreadStackGuarantee);
                return EXCEPTION_CONTINUE_EXECUTION;
            case EXCEPTION_ACCESS_VIOLATION:
                if (jl_addr_is_safepoint(ExceptionInfo->ExceptionRecord->ExceptionInformation[1])) {
#ifdef JULIA_ENABLE_THREADING
                    jl_set_gc_and_wait();
                    // Do not raise sigint on worker thread
                    if (ptls->tid != 0)
                        return EXCEPTION_CONTINUE_EXECUTION;
#endif
                    if (ptls->defer_signal) {
                        jl_safepoint_defer_sigint();
                    }
                    else if (jl_safepoint_consume_sigint()) {
                        jl_clear_force_sigint();
                        jl_throw_in_ctx(jl_interrupt_exception,
                                        ExceptionInfo->ContextRecord, in_ctx);
                    }
                    return EXCEPTION_CONTINUE_EXECUTION;
                }
                if (ExceptionInfo->ExceptionRecord->ExceptionInformation[0] == 1) { // writing to read-only memory (e.g. mmap)
                    jl_throw_in_ctx(jl_readonlymemory_exception,
                        ExceptionInfo->ContextRecord,in_ctx);
                    return EXCEPTION_CONTINUE_EXECUTION;
                }
        }
        jl_safe_printf("\nPlease submit a bug report with steps to reproduce this fault, and any error messages that follow (in their entirety). Thanks.\nException: ");
        switch (ExceptionInfo->ExceptionRecord->ExceptionCode) {
            case EXCEPTION_ACCESS_VIOLATION:
                jl_safe_printf("EXCEPTION_ACCESS_VIOLATION"); break;
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
                jl_safe_printf("EXCEPTION_ARRAY_BOUNDS_EXCEEDED"); break;
            case EXCEPTION_BREAKPOINT:
                jl_safe_printf("EXCEPTION_BREAKPOINT"); break;
            case EXCEPTION_DATATYPE_MISALIGNMENT:
                jl_safe_printf("EXCEPTION_DATATYPE_MISALIGNMENT"); break;
            case EXCEPTION_FLT_DENORMAL_OPERAND:
                jl_safe_printf("EXCEPTION_FLT_DENORMAL_OPERAND"); break;
            case EXCEPTION_FLT_DIVIDE_BY_ZERO:
                jl_safe_printf("EXCEPTION_FLT_DIVIDE_BY_ZERO"); break;
            case EXCEPTION_FLT_INEXACT_RESULT:
                jl_safe_printf("EXCEPTION_FLT_INEXACT_RESULT"); break;
            case EXCEPTION_FLT_INVALID_OPERATION:
                jl_safe_printf("EXCEPTION_FLT_INVALID_OPERATION"); break;
            case EXCEPTION_FLT_OVERFLOW:
                jl_safe_printf("EXCEPTION_FLT_OVERFLOW"); break;
            case EXCEPTION_FLT_STACK_CHECK:
                jl_safe_printf("EXCEPTION_FLT_STACK_CHECK"); break;
            case EXCEPTION_FLT_UNDERFLOW:
                jl_safe_printf("EXCEPTION_FLT_UNDERFLOW"); break;
            case EXCEPTION_ILLEGAL_INSTRUCTION:
                jl_safe_printf("EXCEPTION_ILLEGAL_INSTRUCTION"); break;
            case EXCEPTION_IN_PAGE_ERROR:
                jl_safe_printf("EXCEPTION_IN_PAGE_ERROR"); break;
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
                jl_safe_printf("EXCEPTION_INT_DIVIDE_BY_ZERO"); break;
            case EXCEPTION_INT_OVERFLOW:
                jl_safe_printf("EXCEPTION_INT_OVERFLOW"); break;
            case EXCEPTION_INVALID_DISPOSITION:
                jl_safe_printf("EXCEPTION_INVALID_DISPOSITION"); break;
            case EXCEPTION_NONCONTINUABLE_EXCEPTION:
                jl_safe_printf("EXCEPTION_NONCONTINUABLE_EXCEPTION"); break;
            case EXCEPTION_PRIV_INSTRUCTION:
                jl_safe_printf("EXCEPTION_PRIV_INSTRUCTION"); break;
            case EXCEPTION_SINGLE_STEP:
                jl_safe_printf("EXCEPTION_SINGLE_STEP"); break;
            case EXCEPTION_STACK_OVERFLOW:
                jl_safe_printf("EXCEPTION_STACK_OVERFLOW"); break;
            default:
                jl_safe_printf("UNKNOWN"); break;
        }
        jl_safe_printf(" at 0x%Ix -- ", (size_t)ExceptionInfo->ExceptionRecord->ExceptionAddress);
        jl_gdblookup((uintptr_t)ExceptionInfo->ExceptionRecord->ExceptionAddress);

        jl_critical_error(0, ExceptionInfo->ContextRecord,
                          ptls->bt_data, &ptls->bt_size);
        static int recursion = 0;
        if (recursion++)
            exit(1);
        else
            jl_exit(1);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}