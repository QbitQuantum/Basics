wint_t _CRTIMP __cdecl _putwch (
        wchar_t ch
        )
{
        REG2 wint_t retval;

        _mlock(_CONIO_LOCK);
        __try {

        retval = _putwch_nolock(ch);

        }
        __finally {
                _munlock(_CONIO_LOCK);
        }

        return(retval);
}