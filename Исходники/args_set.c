/*
 * strargerr
 *
 * returns string containing detailed error message of
 * error occured in last call of _set_args()
 *
 */
STRPTR strargerr(void)
{
    STRPTR str = "unknown error";

    switch (arg_error_num)
    {

    case ASE_NO_MEM:
        str = "out of memory";
        break;

    case ASE_OCCURED_TWICE:
        str = "argument occured twice";
        break;

    case ASE_UNKNOWN_KEYWORD:
        str = "unknown keyword";
        break;

    case ASE_INVALID_NUM:
        str = "invalid numeric argument";
        break;

    case ASE_INVALID_ENUM:
        str = "invalid enumerator value";
        break;

    case ASE_REQUIRED_MISS:
        str = "required argument missing";
        break;

    case ASE_EMPTY_TEMPLATE:
        str = "empty template";
        break;

    case ASE_OUT_OF_RANGE:
        str = "numeric argument out of range";
        break;
    case ASE_NO_VAL_AFTER_KW:
        str = "value after keyword missing";
        break;

    case ASE_HANDLE_FUNC:       /* error in handle function */
        str = arg_error_hfs;
        break;

    }                           /* switch */

    strcpy(argerrstr, str);
    if (arg_error_arg)
    {

        strncat(argerrstr, ": ", SIZE_ARGERRSTR - strlen(str) - 1);
        strncat(argerrstr, arg_error_arg, SIZE_ARGERRSTR - strlen(str) - 3);

    }

    if (arg_error_num)
        return argerrstr;
    else
        return NULL;
}