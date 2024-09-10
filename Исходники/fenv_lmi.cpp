void fenv_rounding(e_ieee754_rounding rounding_mode)
{
#if defined LMI_IEC_559
    int z =
          (fe_tonearest  == rounding_mode) ? FE_TONEAREST
        : (fe_downward   == rounding_mode) ? FE_DOWNWARD
        : (fe_upward     == rounding_mode) ? FE_UPWARD
        : (fe_towardzero == rounding_mode) ? FE_TOWARDZERO
        : throw std::runtime_error("Failed to set rounding mode.")
        ;
    fesetround(z);
#elif defined __BORLANDC__
    unsigned short int z =
          (fe_tonearest  == rounding_mode) ? (unsigned short int)(RC_NEAR)
        : (fe_downward   == rounding_mode) ? (unsigned short int)(RC_DOWN)
        : (fe_upward     == rounding_mode) ? (unsigned short int)(RC_UP)
        : (fe_towardzero == rounding_mode) ? (unsigned short int)(RC_CHOP)
        : throw std::runtime_error("Failed to set rounding mode.")
        ;
    _control87(z, MCW_RC);
#elif defined LMI_X86
    intel_control_word control_word(x87_control_word());
    control_word.rc(rounding_mode);
    x87_control_word(control_word.cw());
#else  // Unknown compiler or platform.
#   error Unknown compiler or platform.
#endif // Unknown compiler or platform.
}