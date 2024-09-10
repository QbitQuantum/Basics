void FPUFlags::setCurrent (const FPUFlags& flags)
{
  unsigned int newControl = 0;
  unsigned int mask = 0;

  setControl (flags.getMaskNaNs(), newControl, mask,        _EM_INVALID);
  setControl (flags.getMaskDenormals(), newControl, mask,   _EM_DENORMAL);
  setControl (flags.getMaskZeroDivides(), newControl, mask, _EM_ZERODIVIDE);
  setControl (flags.getMaskOverflows(), newControl, mask,   _EM_OVERFLOW);
  setControl (flags.getMaskUnderflows(), newControl, mask,  _EM_UNDERFLOW);
//setControl (flags.getMaskInexacts(), newControl, mask,    _EM_INEXACT);
  setControl (flags.getFlushDenormals(), newControl, mask,  _DN_FLUSH);
  setControl (flags.getInfinitySigned(), newControl, mask,  _IC_AFFINE);

  if (flags.getRounding().is_set ())
  {
    Rounding rounding = flags.getRounding().value ();

    switch (rounding)
    {
    case roundChop: mask |= _MCW_RC; newControl |= _RC_CHOP; break;
    case roundUp:   mask |= _MCW_RC; newControl |= _RC_UP;   break;
    case roundDown: mask |= _MCW_RC; newControl |= _RC_DOWN; break;
    case roundNear: mask |= _MCW_RC; newControl |= _RC_NEAR; break;
    }
  }

  if (flags.getPrecision().is_set ())
  {
    switch (flags.getPrecision().value ())
    {
    case bits64: mask |= _MCW_PC; newControl |= _PC_64; break;
    case bits53: mask |= _MCW_PC; newControl |= _PC_53; break;
    case bits24: mask |= _MCW_PC; newControl |= _PC_24; break;
    }
  }

  unsigned int currentControl;

  errno_t result = _controlfp_s (&currentControl, newControl, mask);

  if (result != 0)
    Throw (std::runtime_error ("error in _controlfp_s"));
}