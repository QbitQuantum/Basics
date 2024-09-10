void SetException(DWORD code, EXCEPTION_RECORD *pr)
{
	TCHAR *lpMsgBuf;
	lpMsgBuf = FormatError(code);
	if(lpMsgBuf) {
		PyErr_SetFromWindowsErr(code);
		LocalFree(lpMsgBuf);
	} else {
		switch (code) {
		case EXCEPTION_ACCESS_VIOLATION:
			/* The thread attempted to read from or write
			   to a virtual address for which it does not
			   have the appropriate access. */
			if (pr->ExceptionInformation[0] == 0)
				PyErr_Format(PyExc_WindowsError,
					     "exception: access violation reading %p",
					     pr->ExceptionInformation[1]);
			else
				PyErr_Format(PyExc_WindowsError,
					     "exception: access violation writing %p",
					     pr->ExceptionInformation[1]);
			break;
		case EXCEPTION_BREAKPOINT:
			/* A breakpoint was encountered. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: breakpoint encountered");
			break;
			
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			/* The thread attempted to read or write data that is
			   misaligned on hardware that does not provide
			   alignment. For example, 16-bit values must be
			   aligned on 2-byte boundaries, 32-bit values on
			   4-byte boundaries, and so on. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: datatype misalignment");
			break;

		case EXCEPTION_SINGLE_STEP:
			/* A trace trap or other single-instruction mechanism
			   signaled that one instruction has been executed. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: single step");
			break;

		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: 
			/* The thread attempted to access an array element
			   that is out of bounds, and the underlying hardware
			   supports bounds checking. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: array bounds exceeded");
			break;

		case EXCEPTION_FLT_DENORMAL_OPERAND:
			/* One of the operands in a floating-point operation
			   is denormal. A denormal value is one that is too
			   small to represent as a standard floating-point
			   value. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: floating-point operand denormal");
			break;

		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			/* The thread attempted to divide a floating-point
			   value by a floating-point divisor of zero. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: float divide by zero");
			break;

		case EXCEPTION_FLT_INEXACT_RESULT:
			/* The result of a floating-point operation cannot be
			   represented exactly as a decimal fraction. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: float inexact");
			break;

		case EXCEPTION_FLT_INVALID_OPERATION:
			/* This exception represents any floating-point
			   exception not included in this list. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: float invalid operation");
			break;

		case EXCEPTION_FLT_OVERFLOW:
			/* The exponent of a floating-point operation is
			   greater than the magnitude allowed by the
			   corresponding type. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: float overflow");
			break;

		case EXCEPTION_FLT_STACK_CHECK:
			/* The stack overflowed or underflowed as the result
			   of a floating-point operation. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: stack over/underflow");
			break;

		case EXCEPTION_STACK_OVERFLOW:
			/* The stack overflowed or underflowed as the result
			   of a floating-point operation. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: stack overflow");
			break;

		case EXCEPTION_FLT_UNDERFLOW:
			/* The exponent of a floating-point operation is less
			   than the magnitude allowed by the corresponding
			   type. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: float underflow");
			break;

		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			/* The thread attempted to divide an integer value by
			   an integer divisor of zero. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: integer divide by zero");
			break;

		case EXCEPTION_INT_OVERFLOW:
			/* The result of an integer operation caused a carry
			   out of the most significant bit of the result. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: integer overflow");
			break;

		case EXCEPTION_PRIV_INSTRUCTION:
			/* The thread attempted to execute an instruction
			   whose operation is not allowed in the current
			   machine mode. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: priviledged instruction");
			break;

		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			/* The thread attempted to continue execution after a
			   noncontinuable exception occurred. */
			PyErr_SetString(PyExc_WindowsError,
					"exception: nocontinuable");
			break;
		default:
			printf("error %d\n", code);
			PyErr_Format(PyExc_WindowsError,
				     "exception code 0x%08x",
				     code);
			break;
		}
	}
}