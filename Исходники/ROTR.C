unsigned long __cdecl _lrotr (
        unsigned long val,
        int shift
        )
{
        return( (unsigned long) _rotr((unsigned) val, shift) );
}