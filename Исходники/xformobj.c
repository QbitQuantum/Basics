/*
 * A^-1 = adj(A) / det(AT)
 * A^-1 = 1/(a*d - b*c) * (a22,-a12,a21,-a11)
 */
ULONG
NTAPI
XFORMOBJ_iInverse(
    OUT XFORMOBJ *pxoDst,
    IN XFORMOBJ *pxoSrc)
{
    PMATRIX pmxDst, pmxSrc;
    FLOATOBJ foDet;
    XFORM xformSrc;

    pmxDst = XFORMOBJ_pmx(pxoDst);
    pmxSrc = XFORMOBJ_pmx(pxoSrc);

    XFORMOBJ_iGetXform(pxoSrc, (XFORML*)&xformSrc);

    /* det = M11 * M22 - M12 * M21 */
    MulSub(&foDet, &pmxSrc->efM11, &pmxSrc->efM22, &pmxSrc->efM12, &pmxSrc->efM21);

    if (FLOATOBJ_Equal0(&foDet))
    {
        /* Determinant is 0! */
        return DDI_ERROR;
    }

    /* Calculate adj(A) / det(A) */
    pmxDst->efM11 = pmxSrc->efM22;
    FLOATOBJ_Div(&pmxDst->efM11, &foDet);
    pmxDst->efM22 = pmxSrc->efM11;
    FLOATOBJ_Div(&pmxDst->efM22, &foDet);

    /* The other 2 are negative, negate foDet for that */
    FLOATOBJ_Neg(&foDet);
    pmxDst->efM12 = pmxSrc->efM12;
    FLOATOBJ_Div(&pmxDst->efM12, &foDet);
    pmxDst->efM21 = pmxSrc->efM21;
    FLOATOBJ_Div(&pmxDst->efM21, &foDet);

    /* Calculate the inverted x shift: Dx' = -Dx * M11' - Dy * M21' */
    pmxDst->efDx = pmxSrc->efDx;
    FLOATOBJ_Neg(&pmxDst->efDx);
    MulSub(&pmxDst->efDx, &pmxDst->efDx, &pmxDst->efM11, &pmxSrc->efDy, &pmxDst->efM21);

    /* Calculate the inverted y shift: Dy' = -Dy * M22' - Dx * M12' */
    pmxDst->efDy = pmxSrc->efDy;
    FLOATOBJ_Neg(&pmxDst->efDy);
    MulSub(&pmxDst->efDy, &pmxDst->efDy, &pmxDst->efM22, &pmxSrc->efDx, &pmxDst->efM12);

    /* Update accelerators and return complexity */
    return XFORMOBJ_UpdateAccel(pxoDst);
}