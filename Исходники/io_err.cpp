/** @brief Sets extended RTL error.
    @param Format printf-like format string with following parameters.

    This function accept error string and set error value to ERROR_USER.
*/
void MYRTLEXP_PT SetError( CONSTSTR Format, ... )
  {  va_list a;
     char    _ErrBuff[ sizeof(ErrBuff) ];

    va_start( a, Format );
      VSNprintf( _ErrBuff,sizeof(_ErrBuff),Format,a );
    va_end( a );

    memcpy( ErrBuff, _ErrBuff, sizeof(ErrBuff) );
    _FIO_SETERRORN( ERROR_USER );
}