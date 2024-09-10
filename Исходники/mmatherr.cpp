extern "C" _MRTIMP void __cdecl __setusermatherr_m( _HANDLE_MATH_ERROR_M pf)
{
        pusermatherr = (_HANDLE_MATH_ERROR_M) EncodePointer(pf);
        if (pf != 0) {
            __setusermatherr(_matherr);
        }
        _matherr_flag = 0;
}