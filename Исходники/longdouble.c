bool initFPU()
{
#ifdef _WIN64
//    int old_cw = ld_initfpu(_RC_NEAR);
    int old_cw = ld_initfpu(0x300 /*_PC_64  | _RC_NEAR*/, // #defines NOT identical to CPU FPU control word!
                            0xF00 /*_MCW_PC | _MCW_RC*/);
#else
    int old_cw = _control87(_MCW_EM | _PC_64  | _RC_NEAR,
                            _MCW_EM | _MCW_PC | _MCW_RC);
#endif
    _set_output_format(_TWO_DIGIT_EXPONENT);
    return true;
}