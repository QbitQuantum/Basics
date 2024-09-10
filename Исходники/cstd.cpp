//! execute all constructors and other dynamic initializers
void _cdecl init_ctor() {

    _atexit_init();
    _initterm(__xc_a, __xc_z);
}