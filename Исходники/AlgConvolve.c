/*!
* \return	Error code.
* \ingroup	AlgConvolve
* \brief	Convolves double 1D kernel and data arrays, cnv = krn * data.
*		The return convolution array must not be aliased to
*		either the kernel or data arrays.
* \param	sizeArrayCnv		Length of return array must be
*					>= max(len(dat),len(krn)).
* \param	arrayCnv		Return convolution array.
* \param	sizeArrayKrn		Length of kernel array, must be
*					odd.
* \param	arrayKrn		Kernel array.
* \param	sizeArrayDat		Length of data array.
* \param	arrayDat		Data array.
* \param	pad			Type of padding.
* \param	padVal			Padding value, only used when
* 					pad == ALG_PAD_VALUE.
*/
AlgError	AlgConvolveD(int sizeArrayCnv, double *arrayCnv,
                         int sizeArrayKrn, double *arrayKrn,
                         int sizeArrayDat, double *arrayDat,
                         AlgPadType pad, double padVal)
{
    int		pCnt,
            kCnt0,
            kCnt1,
            halfArrayKrn;
    double	dat0,
            dat1;
    AlgError	errCode = ALG_ERR_NONE;

    ALG_DBG((ALG_DBG_LVL_FN|ALG_DBG_LVL_1),
            ("AlgConvolve FE %d 0x%lx %d 0x%lx %d 0x%lx %d\n",
             sizeArrayCnv, (unsigned long )arrayCnv,
             sizeArrayKrn, (unsigned long )arrayKrn,
             sizeArrayDat, (unsigned long )arrayDat,
             (int )pad));
    halfArrayKrn = sizeArrayKrn / 2;
    if((sizeArrayCnv <= 0) || (arrayCnv == NULL) ||
            (sizeArrayKrn <= 0) || ((sizeArrayKrn % 2) != 1) || (arrayKrn == NULL) ||
            (sizeArrayDat <= 0) || (arrayDat == NULL))
    {
        errCode = ALG_ERR_FUNC;
    }
    else
    {
        switch(pad)
        {
        case ALG_PAD_NONE:
            pad = ALG_PAD_ZERO;
            break;
        case ALG_PAD_ZERO:
            break;
        case ALG_PAD_END:
            dat0 = arrayDat[0];
            dat1 = arrayDat[sizeArrayDat - 1];
            break;
        case ALG_PAD_VALUE:
            dat0 = padVal;
            dat1 = padVal;
            break;
        default:
            errCode = ALG_ERR_FUNC;
            break;
        }
    }
    if(errCode == ALG_ERR_NONE)
    {
        /* Pad leading data with zeros or first data value and convolve with the
         * kernel until the whole of the kernel is within the data. */
        int		idp;

        for(idp = 0; idp < halfArrayKrn; ++idp)
        {
            int	idk;
            double	cnv = 0.0;

            pCnt = halfArrayKrn - idp;
            if((pad == ALG_PAD_END) || pad == (ALG_PAD_VALUE))
            {
                for(idk = 0; idk < pCnt; ++idk)
                {
                    cnv += arrayKrn[idk];
                }
                cnv *= dat0;
            }
            kCnt0 = sizeArrayKrn - pCnt;
            for(idk = 0; idk < kCnt0; ++idk)
            {
                cnv += arrayKrn[pCnt + idk] * arrayDat[idk];
            }
            arrayCnv[idp] = cnv;
        }
        /* Between leading and trailing padding regions just convolue the data
         * with the kernel. */
        pCnt = sizeArrayDat - sizeArrayKrn + 1;
#if defined ALG_FAST_CODE && defined __AVX2__
        {
            int	sizeArrayKrn4;

            sizeArrayKrn4 = sizeArrayKrn - (sizeArrayKrn % 4);
            for(idp = 0; idp < pCnt; ++idp)
            {
                int	idk;
                double	*dP;
                double	*cP;
                __m256d   c;

                c = _mm256_setzero_pd();
                dP = arrayDat + idp;
                for(idk = 0; idk < sizeArrayKrn4; idk += 4)
                {
                    __m256d d,
                            k;

                    d = _mm256_loadu_pd(dP + idk);
                    k = _mm256_loadu_pd(arrayKrn + idk);
                    c = _mm256_add_pd(c, _mm256_mul_pd(d, k));
                }
                cP = (double *)&c;
                cP[0] = cP[0] + cP[1] + cP[2] + cP[3];
                for(idk = sizeArrayKrn4; idk < sizeArrayKrn; ++idk)
                {
                    cP[0] += arrayKrn[idk] * dP[idk];
                }
                arrayCnv[halfArrayKrn + idp] = cP[0];
            }
        }
#else /* !ALG_FAST_CODE */
        for(idp = 0; idp < pCnt; ++idp)
        {
            int	idk;
            double	cnv = 0.0;

            for(idk = 0; idk < sizeArrayKrn; ++idk)
            {
                cnv += arrayKrn[idk] * arrayDat[idp + idk];
            }
            arrayCnv[halfArrayKrn + idp] = cnv;
        }
#endif /* ALG_FAST_CODE */
        /* Pad trailing data with zeros or last data value and convolve with the
         * kernel until the whole of the kernel is outside the data. */
        for(idp = 0; idp < halfArrayKrn; ++idp)
        {
            int	idk,
                idt;
            double	cnv = 0.0;

            kCnt0 = sizeArrayKrn - idp - 1;
            idt = idp + sizeArrayDat - sizeArrayKrn + 1;
            for(idk = 0; idk < kCnt0; ++idk)
            {
                cnv += arrayKrn[idk] * arrayDat[idt + idk];
            }
            if((pad == ALG_PAD_END) || pad == (ALG_PAD_VALUE))
            {
                double	cnv1 = 0.0;
                kCnt1 = sizeArrayKrn - kCnt0;
                for(idk = 0; idk < kCnt1; ++idk)
                {
                    cnv1 += arrayKrn[kCnt0 + idk];
                }
                cnv += cnv1 * dat1;
            }
            arrayCnv[sizeArrayDat - halfArrayKrn + idp] = cnv;
        }
    }
    ALG_DBG((ALG_DBG_LVL_FN|ALG_DBG_LVL_1),
            ("AlgConvolve FX %d\n",
             (int )errCode));
    return(errCode);
}