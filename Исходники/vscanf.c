	int vscanf (

/*  SYNOPSIS */
	const char * format,
	va_list      args)

/*  FUNCTION
	Scan the standard input and convert it into the arguments as
	specified by format.

    INPUTS
	format - A scanf() format string.
	args - A list of arguments for the results

    RESULT
	The number of converted parameters.

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

******************************************************************************/
{
    struct PosixCBase *PosixCBase = __aros_getbase_PosixCBase();

    return vfscanf (PosixCBase->_stdin, format, args);
} /* vscanf */