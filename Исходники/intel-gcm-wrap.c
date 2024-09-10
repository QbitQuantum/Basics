intel_AES_GCMContext *intel_AES_GCM_CreateContext(void *context, 
               freeblCipherFunc cipher,
               const unsigned char *params, 
               unsigned int blocksize)
{
    intel_AES_GCMContext *gcm = NULL;
    AESContext *aes = (AESContext*)context;
    const CK_GCM_PARAMS *gcmParams = (const CK_GCM_PARAMS *)params;
    unsigned char buff[AES_BLOCK_SIZE]; /* aux buffer */
    
    int IV_whole_len = gcmParams->ulIvLen&(~0xf);
    int IV_remainder_len = gcmParams->ulIvLen&0xf;
    int AAD_whole_len = gcmParams->ulAADLen&(~0xf);
    int AAD_remainder_len = gcmParams->ulAADLen&0xf;
    
    __m128i BSWAP_MASK = _mm_setr_epi8(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
    __m128i ONE = _mm_set_epi32(0,0,0,1);
    unsigned int j;
    SECStatus rv;

    if (blocksize != AES_BLOCK_SIZE) {
      PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
      return NULL;
    }
    gcm = PORT_ZNew(intel_AES_GCMContext);
    
    if (gcm == NULL) {
        return NULL;
    }
    /* initialize context fields */
    gcm->aes_context = aes;
    gcm->tagBits = gcmParams->ulTagBits;
    gcm->Alen = 0;
    gcm->Mlen = 0;
    /* first prepare H and its derivatives for ghash */
    intel_aes_gcmINIT(gcm->Htbl, (unsigned char*)aes->expandedKey, aes->Nr);
    /* Initial TAG value is zero*/
    _mm_storeu_si128((__m128i*)gcm->T, _mm_setzero_si128());
    _mm_storeu_si128((__m128i*)gcm->X0, _mm_setzero_si128());
    /* Init the counter */
    if(gcmParams->ulIvLen == 12) {
        _mm_storeu_si128((__m128i*)gcm->CTR, _mm_setr_epi32(((unsigned int*)gcmParams->pIv)[0], ((unsigned int*)gcmParams->pIv)[1], ((unsigned int*)gcmParams->pIv)[2], 0x01000000));
    } else {
        /* If IV size is not 96 bits, then the initial counter value is GHASH of the IV */
        intel_aes_gcmAAD(gcm->Htbl, gcmParams->pIv, IV_whole_len, gcm->T);
        /* Partial block */
        if(IV_remainder_len) {
            PORT_Memset(buff, 0, AES_BLOCK_SIZE);
            PORT_Memcpy(buff, gcmParams->pIv + IV_whole_len, IV_remainder_len);
            intel_aes_gcmAAD(gcm->Htbl, buff, AES_BLOCK_SIZE, gcm->T);
         }
         
         intel_aes_gcmTAG
         (
            gcm->Htbl,
            gcm->T,
            gcmParams->ulIvLen,
            0,
            gcm->X0,
            gcm->CTR
         );
        /* TAG should be zero again */
        _mm_storeu_si128((__m128i*)gcm->T, _mm_setzero_si128());
    }
    /* Encrypt the initial counter, will be used to encrypt the GHASH value, in the end */
    rv = (*cipher)(context, gcm->X0, &j, AES_BLOCK_SIZE, gcm->CTR, AES_BLOCK_SIZE, AES_BLOCK_SIZE);
    if (rv != SECSuccess) {
        goto loser;
    }
    /* Promote the counter by 1 */
    _mm_storeu_si128((__m128i*)gcm->CTR, _mm_shuffle_epi8(_mm_add_epi32(ONE, _mm_shuffle_epi8(_mm_loadu_si128((__m128i*)gcm->CTR), BSWAP_MASK)), BSWAP_MASK));

/*     Now hash AAD - it would actually make sense to seperate the context creation from the AAD, 
 *     because that would allow to reuse the H, which only changes when the AES key changes, 
 *     and not every package, like the IV and AAD */
    intel_aes_gcmAAD(gcm->Htbl, gcmParams->pAAD, AAD_whole_len, gcm->T);
    if(AAD_remainder_len) {
        PORT_Memset(buff, 0, AES_BLOCK_SIZE);
        PORT_Memcpy(buff, gcmParams->pAAD + AAD_whole_len, AAD_remainder_len);
        intel_aes_gcmAAD(gcm->Htbl, buff, AES_BLOCK_SIZE, gcm->T);
    }
    gcm->Alen += gcmParams->ulAADLen;
    return gcm;
    
    loser:
    if (gcm) {
        PORT_Free(gcm);
    }
    return NULL;
}