void __chk8087( void )
/********************/
{
    // TODO: We really need to call Linux and determine if the machine
    //       has a real FPU or not, so we can properly work with an FPU
    //       emulator.
    _RWD_real87 = __x87id();
    _RWD_8087 = _RWD_real87;
    _fpreset();
}