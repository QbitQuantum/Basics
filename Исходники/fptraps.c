void    __MaskDefaultFPE( void ) {
//==========================
#if defined( _M_IX86 )
    // By default we don't report the following exceptions;
    // the user has to make his own call to _control87.  This has to
    // be done in the "fpc" model as well in case there is an 80x87
    // present.
    _control87( ~0, EM_UNDERFLOW | EM_DENORMAL | EM_PRECISION );
#endif
}