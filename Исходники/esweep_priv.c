__EXTERN_FUNC__ int inline correctFpException(esweep_object* obj) {
  int i;

  Wave *wave;
  Polar *polar;
  Complex *cpx;
  Surface *surf;

  if (fetestexcept(FE_INVALID)) {
    fprintf(stderr, "Invalid floating point operation occured.\n");
    feclearexcept(FE_INVALID);
    return 0;
  }

  if (fetestexcept(FE_OVERFLOW | FE_DIVBYZERO)) {
    // find the errors and correct them by rounding to neares representable
    switch (obj->type) {
      case WAVE:
        wave=(Wave*) obj->data;
        for (i=0; i < obj->size; i++) {
          if (isinf(wave[i])) {
            if (signbit(wave[i])) {
              wave[i]=-MAXREAL;
            } else {
              wave[i]=MAXREAL;
            }
          }
        }
        break;
      case POLAR:
        polar=(Polar*) obj->data;
        for (i=0; i < obj->size; i++) {
          if (isinf(polar[i].abs)) {
            if (signbit(polar[i].abs)) {
              polar[i].abs=-MAXREAL;
            } else {
              polar[i].abs=MAXREAL;
            }
          }
          if (isinf(polar[i].arg)) {
            if (signbit(polar[i].arg)) {
              polar[i].arg=-MAXREAL;
            } else {
              polar[i].arg=MAXREAL;
            }
          }
        }
        break;
      case COMPLEX:
        cpx=(Complex*) obj->data;
        for (i=0; i < obj->size; i++) {
          if (isinf(cpx[i].real)) {
            if (signbit(cpx[i].real)) {
              cpx[i].real=-MAXREAL;
            } else {
              cpx[i].real=MAXREAL;
            }
          }
          if (isinf(cpx[i].imag)) {
            if (signbit(cpx[i].imag)) {
              cpx[i].imag=-MAXREAL;
            } else {
              cpx[i].imag=MAXREAL;
            }
          }
        }
        break;
      case SURFACE:
      default:
        break;
    }
    feclearexcept(FE_OVERFLOW | FE_DIVBYZERO);
  }
  return 1;
}