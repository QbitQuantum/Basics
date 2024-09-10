//compute average channel_level on each (TX,RX) antenna pair
int dl_channel_level(s16 *dl_ch,
		     LTE_DL_FRAME_PARMS *frame_parms) {

  s16 rb;
  __m128i *dl_ch128;
  int avg;

      //clear average level
  avg128F = _mm_xor_si128(avg128F,avg128F);
  dl_ch128=(__m128i *)dl_ch;

  for (rb=0;rb<frame_parms->N_RB_DL;rb++) {
    
    avg128F = _mm_add_epi32(avg128F,_mm_madd_epi16(dl_ch128[0],dl_ch128[0]));
    avg128F = _mm_add_epi32(avg128F,_mm_madd_epi16(dl_ch128[1],dl_ch128[1]));
    avg128F = _mm_add_epi32(avg128F,_mm_madd_epi16(dl_ch128[2],dl_ch128[2]));
    
    dl_ch128+=3;	
    
  }

  avg = (((int*)&avg128F)[0] + 
	 ((int*)&avg128F)[1] + 
	 ((int*)&avg128F)[2] + 
	 ((int*)&avg128F)[3])/(frame_parms->N_RB_DL*12);
  


  _mm_empty();
  _m_empty();
  
  return(avg);
}