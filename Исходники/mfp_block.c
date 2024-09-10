int
mfp_block_trunc(mfp_block * in, mfp_block * out) 
{
    if (mfp_block_use_sse && mfp_block_compiled_with_sse) { 
#ifdef MFP_USE_SSE
        int loc = 0;
        int end = in->blocksize;
        __v4sf ftmp;
        __v4si itmp;
        for(; loc < end; loc+=4) {
            ftmp = __builtin_ia32_loadups(in->data+loc);
            itmp = __builtin_ia32_cvttps2dq(ftmp);
            ftmp = __builtin_ia32_cvtdq2ps(itmp);
            __builtin_ia32_storeups(out->data + loc, ftmp); 
         }
#endif
    }
    else {
        mfp_sample * inptr = in->data, * optr = out->data;
        mfp_sample * iend = in->data + in->blocksize;
        for (; inptr < iend; inptr++) {
            *optr = truncf(*inptr);
            optr++;
        }
    }
    return 1;
}