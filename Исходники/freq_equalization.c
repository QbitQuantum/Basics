void freq_equalization(LTE_DL_FRAME_PARMS *frame_parms,
		       int32_t **rxdataF_comp,
		       int32_t **ul_ch_mag,
		       int32_t **ul_ch_magb,
		       uint8_t symbol,
		       uint16_t Msc_RS,
		       uint8_t Qm) {
  uint16_t re;
  int16_t amp;
  __m128i *ul_ch_mag128,*ul_ch_magb128,*rxdataF_comp128;

  rxdataF_comp128   = (__m128i *)&rxdataF_comp[0][symbol*frame_parms->N_RB_DL*12];  
  ul_ch_mag128      = (__m128i *)&ul_ch_mag[0][symbol*frame_parms->N_RB_DL*12];  
  ul_ch_magb128      = (__m128i *)&ul_ch_magb[0][symbol*frame_parms->N_RB_DL*12];  

  for (re=0;re<(Msc_RS>>2);re++) {
      
    amp=(*((int16_t*)&ul_ch_mag128[re]));
    if (amp>255)
      amp=255;

    //     printf("freq_eq: symbol %d re %d => %d,%d,%d, (%d) (%d,%d) => ",symbol,re,*((int16_t*)(&ul_ch_mag128[re])),amp,inv_ch[8*amp],*((int16_t*)(&ul_ch_mag128[re]))*inv_ch[8*amp],*(int16_t*)&(rxdataF_comp128[re]),*(1+(int16_t*)&(rxdataF_comp128[re])));
    rxdataF_comp128[re] = _mm_mullo_epi16(rxdataF_comp128[re],*((__m128i *)&inv_ch[8*amp])); 
    if (Qm==4)
      ul_ch_mag128[re] = _mm_set1_epi16(324);  // this is 512*2/sqrt(10)
    else {
      ul_ch_mag128[re]   = _mm_set1_epi16(316);  // this is 512*4/sqrt(42)
      ul_ch_magb128[re] = _mm_set1_epi16(158);  // this is 512*2/sqrt(42)
    }
    //            printf("(%d,%d)\n",*(int16_t*)&(rxdataF_comp128[re]),*(1+(int16_t*)&(rxdataF_comp128[re])));

  }
}