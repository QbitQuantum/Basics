/*********************************************************************
 *		_CxxThrowException (MSVCRT.@)
 */
void WINAPI _CxxThrowException( exception *object, const cxx_exception_type *type )
{
    ULONG_PTR args[3];

    args[0] = CXX_FRAME_MAGIC_VC6;
    args[1] = (ULONG_PTR)object;
    args[2] = (ULONG_PTR)type;
    RaiseException( CXX_EXCEPTION, EH_NONCONTINUABLE, 3, args );
}