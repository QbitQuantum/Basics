//compute average channel_level on each (TX,RX) antenna pair
int dl_channel_level(int16_t *dl_ch,
                     LTE_DL_FRAME_PARMS *frame_parms)
{

    int16_t rb;
#if defined(__x86_64__) || defined(__i386__)
    __m128i *dl_ch128;
#elif defined(__arm__)
    int16x4_t *dl_ch128;
#endif
    int avg;

    //clear average level
#if defined(__x86_64__) || defined(__i386__)
    avg128F = _mm_setzero_si128();
    dl_ch128=(__m128i *)dl_ch;

    for (rb=0; rb<frame_parms->N_RB_DL; rb++) {

        avg128F = _mm_add_epi32(avg128F,_mm_madd_epi16(dl_ch128[0],dl_ch128[0]));
        avg128F = _mm_add_epi32(avg128F,_mm_madd_epi16(dl_ch128[1],dl_ch128[1]));
        avg128F = _mm_add_epi32(avg128F,_mm_madd_epi16(dl_ch128[2],dl_ch128[2]));

        dl_ch128+=3;

    }
#elif defined(__arm__)
    avg128F = vdupq_n_s32(0);
    dl_ch128=(int16x4_t *)dl_ch;

    for (rb=0; rb<frame_parms->N_RB_DL; rb++) {

        avg128F = vqaddq_s32(avg128F,vmull_s16(dl_ch128[0],dl_ch128[0]));
        avg128F = vqaddq_s32(avg128F,vmull_s16(dl_ch128[1],dl_ch128[1]));
        avg128F = vqaddq_s32(avg128F,vmull_s16(dl_ch128[2],dl_ch128[2]));
        avg128F = vqaddq_s32(avg128F,vmull_s16(dl_ch128[3],dl_ch128[3]));
        avg128F = vqaddq_s32(avg128F,vmull_s16(dl_ch128[4],dl_ch128[4]));
        avg128F = vqaddq_s32(avg128F,vmull_s16(dl_ch128[5],dl_ch128[5]));
        dl_ch128+=6;


    }


#endif
    DevAssert( frame_parms->N_RB_DL );
    avg = (((int*)&avg128F)[0] +
           ((int*)&avg128F)[1] +
           ((int*)&avg128F)[2] +
           ((int*)&avg128F)[3])/(frame_parms->N_RB_DL*12);


#if defined(__x86_64__) || defined(__i386__)
    _mm_empty();
    _m_empty();
#endif
    return(avg);
}