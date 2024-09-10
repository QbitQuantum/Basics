int esweep_imag(esweep_object *obj) { /* UNTESTED */
    Complex *cpx;
    Polar *polar;
    int i;

    ESWEEP_OBJ_NOTEMPTY(obj, ERR_EMPTY_OBJECT);

    switch (obj->type) {
    case COMPLEX:
        cpx=(Complex*) obj->data;
        for (i=0; i<obj->size; i++) cpx[i].real=0;
        break;
    case POLAR:
        polar=(Polar*) obj->data;
        cpx=(Complex*) polar;
        for (i=0; i<obj->size; i++) {
            cpx[i].imag=polar[i].abs*SIN(polar[i].arg);
            cpx[i].real=0;
        }
        obj->type=COMPLEX;
        break;
    default:
        ESWEEP_NOT_THIS_TYPE(obj->type, ERR_NOT_ON_THIS_TYPE);
    }
    ESWEEP_ASSERT(correctFpException(obj), ERR_FP);
    return ERR_OK;
}