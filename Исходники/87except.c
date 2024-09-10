void _87except(int opcode, struct _exception *exc, unsigned short *pcw16)
{
    int fixed;
    unsigned int flags;
    unsigned int cw, *pcw;

    //
    // convert fp control word into an unsigned int
    //

    cw = *pcw16;
    pcw = &cw;

    switch (exc->type) {
    case _DOMAIN:
    case _TLOSS:
	flags = FP_I;
	break;
    case _OVERFLOW:
	flags = FP_O | FP_P;
	break;
    case _UNDERFLOW:
	flags = FP_U | FP_P;
	break;
    case _SING:
	flags = FP_Z;
	break;
    case _INEXACT:
	flags = FP_P;
	break;
    case _DOMAIN_QNAN:
	exc->type = _DOMAIN;
	// no break
    default:
	flags = 0;
    }



    if (flags && _handle_exc(flags, &exc->retval, *pcw) == 0) {

	//
	// trap should be taken
	//

	_FPIEEE_RECORD rec;

	//
	// fill in operand2 info. The rest of rec will be
	// filled in by _raise_exc
	//

	switch (opcode) {
	case OP_POW:
	case OP_FMOD:
	case OP_ATAN2:
	    rec.Operand2.OperandValid = 1;
	    rec.Operand2.Format = _FpFormatFp64;
	    rec.Operand2.Value.Fp64Value = exc->arg2;
	    break;
	default:
	    rec.Operand2.OperandValid = 0;
	}

	_raise_exc(&rec,
		   pcw,
		   flags,
		   opcode,
		   &exc->arg1,
		   &exc->retval);
    }


    /* restore cw  */
    _rstorfp(*pcw);

    fixed = 0;

    if (exc->type != _INEXACT &&
	! _matherr_flag) {
	fixed = _matherr(exc);
    }
    if (!fixed) {
	_set_errno(exc->type);
    }

}