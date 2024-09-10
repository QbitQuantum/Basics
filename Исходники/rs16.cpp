// Data and ECC addresses must be properly aligned for SSE.
bool RSCoder16::SSE_UpdateECC(uint DataNum, uint ECCNum, const byte *Data, byte *ECC, size_t BlockSize)
{
    // Check data alignment and SSSE3 support.
    if ((size_t(Data) & (SSE_ALIGNMENT-1))!=0 || (size_t(ECC) & (SSE_ALIGNMENT-1))!=0 ||
            _SSE_Version<SSE_SSSE3)
        return false;

    uint M=MX[ECCNum * ND + DataNum];

    // Prepare tables containing products of M and 4, 8, 12, 16 bit length
    // numbers, which have 4 high bits in 0..15 range and other bits set to 0.
    // Store high and low bytes of resulting 16 bit product in separate tables.
    __m128i T0L,T1L,T2L,T3L; // Low byte tables.
    __m128i T0H,T1H,T2H,T3H; // High byte tables.

    for (uint I=0; I<16; I++)
    {
        ((byte *)&T0L)[I]=gfMul(I,M);
        ((byte *)&T0H)[I]=gfMul(I,M)>>8;
        ((byte *)&T1L)[I]=gfMul(I<<4,M);
        ((byte *)&T1H)[I]=gfMul(I<<4,M)>>8;
        ((byte *)&T2L)[I]=gfMul(I<<8,M);
        ((byte *)&T2H)[I]=gfMul(I<<8,M)>>8;
        ((byte *)&T3L)[I]=gfMul(I<<12,M);
        ((byte *)&T3H)[I]=gfMul(I<<12,M)>>8;
    }

    size_t Pos=0;

    __m128i LowByteMask=_mm_set1_epi16(0xff);     // 00ff00ff...00ff
    __m128i Low4Mask=_mm_set1_epi8(0xf);          // 0f0f0f0f...0f0f
    __m128i High4Mask=_mm_slli_epi16(Low4Mask,4); // f0f0f0f0...f0f0

    for (; Pos+2*sizeof(__m128i)<=BlockSize; Pos+=2*sizeof(__m128i))
    {
        // We process two 128 bit chunks of source data at once.
        __m128i *D=(__m128i *)(Data+Pos);

        // Place high bytes of both chunks to one variable and low bytes to
        // another, so we can use the table lookup multiplication for 16 values
        // 4 bit length each at once.
        __m128i HighBytes0=_mm_srli_epi16(D[0],8);
        __m128i LowBytes0=_mm_and_si128(D[0],LowByteMask);
        __m128i HighBytes1=_mm_srli_epi16(D[1],8);
        __m128i LowBytes1=_mm_and_si128(D[1],LowByteMask);
        __m128i HighBytes=_mm_packus_epi16(HighBytes0,HighBytes1);
        __m128i LowBytes=_mm_packus_epi16(LowBytes0,LowBytes1);

        // Multiply bits 0..3 of low bytes. Store low and high product bytes
        // separately in cumulative sum variables.
        __m128i LowBytesLow4=_mm_and_si128(LowBytes,Low4Mask);
        __m128i LowBytesMultSum=_mm_shuffle_epi8(T0L,LowBytesLow4);
        __m128i HighBytesMultSum=_mm_shuffle_epi8(T0H,LowBytesLow4);

        // Multiply bits 4..7 of low bytes. Store low and high product bytes separately.
        __m128i LowBytesHigh4=_mm_and_si128(LowBytes,High4Mask);
        LowBytesHigh4=_mm_srli_epi16(LowBytesHigh4,4);
        __m128i LowBytesHigh4MultLow=_mm_shuffle_epi8(T1L,LowBytesHigh4);
        __m128i LowBytesHigh4MultHigh=_mm_shuffle_epi8(T1H,LowBytesHigh4);

        // Add new product to existing sum, low and high bytes separately.
        LowBytesMultSum=_mm_xor_si128(LowBytesMultSum,LowBytesHigh4MultLow);
        HighBytesMultSum=_mm_xor_si128(HighBytesMultSum,LowBytesHigh4MultHigh);

        // Multiply bits 0..3 of high bytes. Store low and high product bytes separately.
        __m128i HighBytesLow4=_mm_and_si128(HighBytes,Low4Mask);
        __m128i HighBytesLow4MultLow=_mm_shuffle_epi8(T2L,HighBytesLow4);
        __m128i HighBytesLow4MultHigh=_mm_shuffle_epi8(T2H,HighBytesLow4);

        // Add new product to existing sum, low and high bytes separately.
        LowBytesMultSum=_mm_xor_si128(LowBytesMultSum,HighBytesLow4MultLow);
        HighBytesMultSum=_mm_xor_si128(HighBytesMultSum,HighBytesLow4MultHigh);

        // Multiply bits 4..7 of high bytes. Store low and high product bytes separately.
        __m128i HighBytesHigh4=_mm_and_si128(HighBytes,High4Mask);
        HighBytesHigh4=_mm_srli_epi16(HighBytesHigh4,4);
        __m128i HighBytesHigh4MultLow=_mm_shuffle_epi8(T3L,HighBytesHigh4);
        __m128i HighBytesHigh4MultHigh=_mm_shuffle_epi8(T3H,HighBytesHigh4);

        // Add new product to existing sum, low and high bytes separately.
        LowBytesMultSum=_mm_xor_si128(LowBytesMultSum,HighBytesHigh4MultLow);
        HighBytesMultSum=_mm_xor_si128(HighBytesMultSum,HighBytesHigh4MultHigh);

        // Combine separate low and high cumulative sum bytes to 16-bit words.
        __m128i HighBytesHigh4Mult0=_mm_unpacklo_epi8(LowBytesMultSum,HighBytesMultSum);
        __m128i HighBytesHigh4Mult1=_mm_unpackhi_epi8(LowBytesMultSum,HighBytesMultSum);

        // Add result to ECC.
        __m128i *StoreECC=(__m128i *)(ECC+Pos);

        StoreECC[0]=_mm_xor_si128(StoreECC[0],HighBytesHigh4Mult0);
        StoreECC[1]=_mm_xor_si128(StoreECC[1],HighBytesHigh4Mult1);
    }

    // If we have non 128 bit aligned data in the end of block, process them
    // in a usual way. We cannot do the same in the beginning of block,
    // because Data and ECC can have different alignment offsets.
    for (; Pos<BlockSize; Pos+=2)
        *(ushort*)(ECC+Pos) ^= gfMul( M, *(ushort*)(Data+Pos) );

    return true;
}