GLbitfield GLAPIENTRY _mesa_QueryMatrixxOES(GLfixed mantissa[16], GLint exponent[16])
{
    GLfloat matrix[16];
    GLint tmp;
    GLenum currentMode = GL_FALSE;
    GLenum desiredMatrix = GL_FALSE;
    /* The bitfield returns 1 for each component that is invalid (i.e.
     * NaN or Inf).  In case of error, everything is invalid.
     */
    GLbitfield rv;
    register unsigned int i;
    unsigned int bit;

    /* This data structure defines the mapping between the current matrix
     * mode and the desired matrix identifier.
     */
    static struct {
        GLenum currentMode;
        GLenum desiredMatrix;
    } modes[] = {
        {GL_MODELVIEW, GL_MODELVIEW_MATRIX},
        {GL_PROJECTION, GL_PROJECTION_MATRIX},
        {GL_TEXTURE, GL_TEXTURE_MATRIX},
    };

    /* Call Mesa to get the current matrix in floating-point form.  First,
     * we have to figure out what the current matrix mode is.
     */
    _mesa_GetIntegerv(GL_MATRIX_MODE, &tmp);
    currentMode = (GLenum) tmp;

    /* The mode is either GL_FALSE, if for some reason we failed to query
     * the mode, or a given mode from the above table.  Search for the
     * returned mode to get the desired matrix; if we don't find it,
     * we can return immediately, as _mesa_GetInteger() will have
     * logged the necessary error already.
     */
    for (i = 0; i < sizeof(modes)/sizeof(modes[0]); i++) {
        if (modes[i].currentMode == currentMode) {
            desiredMatrix = modes[i].desiredMatrix;
            break;
        }
    }
    if (desiredMatrix == GL_FALSE) {
        /* Early error means all values are invalid. */
        return 0xffff;
    }

    /* Now pull the matrix itself. */
    _mesa_GetFloatv(desiredMatrix, matrix);

    rv = 0;
    for (i = 0, bit = 1; i < 16; i++, bit<<=1) {
        float normalizedFraction;
        int exp;

        switch (fpclassify(matrix[i])) {
            /* A "subnormal" or denormalized number is too small to be
             * represented in normal format; but despite that it's a
             * valid floating point number.  FP_ZERO and FP_NORMAL
             * are both valid as well.  We should be fine treating
             * these three cases as legitimate floating-point numbers.
             */
            case FP_SUBNORMAL:
            case FP_NORMAL:
            case FP_ZERO:
                normalizedFraction = (GLfloat)frexp(matrix[i], &exp);
                mantissa[i] = FLOAT_TO_FIXED(normalizedFraction);
                exponent[i] = (GLint) exp;
                break;

            /* If the entry is not-a-number or an infinity, then the
             * matrix component is invalid.  The invalid flag for
             * the component is already set; might as well set the
             * other return values to known values.  We'll set
             * distinct values so that a savvy end user could determine
             * whether the matrix component was a NaN or an infinity,
             * but this is more useful for debugging than anything else
             * since the standard doesn't specify any such magic
             * values to return.
             */
            case FP_NAN:
                mantissa[i] = INT_TO_FIXED(0);
                exponent[i] = (GLint) 0;
                rv |= bit;
                break;

            case FP_INFINITE:
                /* Return +/- 1 based on whether it's a positive or
                 * negative infinity.
                 */
                if (matrix[i] > 0) {
                    mantissa[i] = INT_TO_FIXED(1);
                }
                else {
                    mantissa[i] = -INT_TO_FIXED(1);
                }
                exponent[i] = (GLint) 0;
                rv |= bit;
                break;

            /* We should never get here; but here's a catching case
             * in case fpclassify() is returnings something unexpected.
             */
            default:
                mantissa[i] = INT_TO_FIXED(2);
                exponent[i] = (GLint) 0;
                rv |= bit;
                break;
        }

    } /* for each component */

    /* All done */
    return rv;
}