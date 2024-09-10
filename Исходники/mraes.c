void aes_ecb_encrypt(aes *a,MR_BYTE *buff)
{
    int i,j,k;
    MR_WORD p[4],q[4],*x,*y,*t;

#ifdef AES_NI_SUPPORT
	__m128i ky,m = _mm_loadu_si128((__m128i *) buff);
	ky = _mm_loadu_si128((__m128i *) &a->fkey[0]);
    m = _mm_xor_si128       (m, ky); 
	k=NB;
	for (i=1;i<a->Nr;i++)
	{
		ky=_mm_loadu_si128((__m128i *) &a->fkey[k]);
		m =_mm_aesenc_si128(m, ky); 
		k+=4;
	}
	ky=_mm_loadu_si128((__m128i *) &a->fkey[k]);
    m=_mm_aesenclast_si128(m, ky);

    _mm_storeu_si128((__m128i *)buff, m);
#else

    for (i=j=0;i<NB;i++,j+=4)
    {
        p[i]=pack((MR_BYTE *)&buff[j]);
        p[i]^=a->fkey[i];
    }

    k=NB;
    x=p; y=q;

/* State alternates between x and y */
    for (i=1;i<a->Nr;i++)
    { /* Nr is number of rounds. May be odd. */
#ifndef MR_SMALL_AES
        y[0]=a->fkey[k]^ftable[MR_TOBYTE(x[0])]^
             ftable1[MR_TOBYTE(x[1]>>8)]^
             ftable2[MR_TOBYTE(x[2]>>16)]^
             ftable3[x[3]>>24];
        y[1]=a->fkey[k+1]^ftable[MR_TOBYTE(x[1])]^
             ftable1[MR_TOBYTE(x[2]>>8)]^
             ftable2[MR_TOBYTE(x[3]>>16)]^
             ftable3[x[0]>>24];
        y[2]=a->fkey[k+2]^ftable[MR_TOBYTE(x[2])]^
             ftable1[MR_TOBYTE(x[3]>>8)]^
             ftable2[MR_TOBYTE(x[0]>>16)]^
             ftable3[x[1]>>24];
        y[3]=a->fkey[k+3]^ftable[MR_TOBYTE(x[3])]^
             ftable1[MR_TOBYTE(x[0]>>8)]^
             ftable2[MR_TOBYTE(x[1]>>16)]^
             ftable3[x[2]>>24];
#else
        y[0]=a->fkey[k]^ftable[MR_TOBYTE(x[0])]^
             ROTL8(ftable[MR_TOBYTE(x[1]>>8)])^
             ROTL16(ftable[MR_TOBYTE(x[2]>>16)])^
             ROTL24(ftable[x[3]>>24]);
        y[1]=a->fkey[k+1]^ftable[MR_TOBYTE(x[1])]^
             ROTL8(ftable[MR_TOBYTE(x[2]>>8)])^
             ROTL16(ftable[MR_TOBYTE(x[3]>>16)])^
             ROTL24(ftable[x[0]>>24]);
        y[2]=a->fkey[k+2]^ftable[MR_TOBYTE(x[2])]^
             ROTL8(ftable[MR_TOBYTE(x[3]>>8)])^
             ROTL16(ftable[MR_TOBYTE(x[0]>>16)])^
             ROTL24(ftable[x[1]>>24]);
        y[3]=a->fkey[k+3]^ftable[MR_TOBYTE(x[3])]^
             ROTL8(ftable[MR_TOBYTE(x[0]>>8)])^
             ROTL16(ftable[MR_TOBYTE(x[1]>>16)])^
             ROTL24(ftable[x[2]>>24]);
#endif
        k+=4;
        t=x; x=y; y=t;      /* swap pointers */
    }

/* Last Round */ 
    
    y[0]=a->fkey[k]^(MR_WORD)fbsub[MR_TOBYTE(x[0])]^
         ROTL8((MR_WORD)fbsub[MR_TOBYTE(x[1]>>8)])^
         ROTL16((MR_WORD)fbsub[MR_TOBYTE(x[2]>>16)])^
         ROTL24((MR_WORD)fbsub[x[3]>>24]);
    y[1]=a->fkey[k+1]^(MR_WORD)fbsub[MR_TOBYTE(x[1])]^
         ROTL8((MR_WORD)fbsub[MR_TOBYTE(x[2]>>8)])^
         ROTL16((MR_WORD)fbsub[MR_TOBYTE(x[3]>>16)])^
         ROTL24((MR_WORD)fbsub[x[0]>>24]);
    y[2]=a->fkey[k+2]^(MR_WORD)fbsub[MR_TOBYTE(x[2])]^
         ROTL8((MR_WORD)fbsub[MR_TOBYTE(x[3]>>8)])^
         ROTL16((MR_WORD)fbsub[MR_TOBYTE(x[0]>>16)])^
         ROTL24((MR_WORD)fbsub[x[1]>>24]);
    y[3]=a->fkey[k+3]^(MR_WORD)fbsub[MR_TOBYTE(x[3])]^
         ROTL8((MR_WORD)fbsub[MR_TOBYTE(x[0]>>8)])^
         ROTL16((MR_WORD)fbsub[MR_TOBYTE(x[1]>>16)])^
         ROTL24((MR_WORD)fbsub[x[2]>>24]);

    for (i=j=0;i<NB;i++,j+=4)
    {
        unpack(y[i],(MR_BYTE *)&buff[j]);
        x[i]=y[i]=0;   /* clean up stack */
    }
#endif
}