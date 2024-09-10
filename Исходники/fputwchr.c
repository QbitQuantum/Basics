wint_t __cdecl _fputwchar (
        REG1 wchar_t ch
        )
{
        return(putwc(ch, stdout));
}