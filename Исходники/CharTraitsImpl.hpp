inline VOID CharTraits<WCHAR>::FormatV( WCHAR* Buffer, SIZE_T Count, CONST WCHAR* Format, va_list Args )
{
  va_list Args0;
  va_copy(Args0,Args);
  vswprintf( Buffer, Count, Format, Args0 );
  va_end(Args0);
}