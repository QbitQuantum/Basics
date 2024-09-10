void ulsch_16qam_llr(LTE_DL_FRAME_PARMS *frame_parms,
		     int **rxdataF_comp,
		     short *ulsch_llr,
		     int **ul_ch_mag,
		     unsigned char symbol,
		     unsigned short nb_rb) {

  __m128i *rxF=(__m128i*)&rxdataF_comp[0][(symbol*frame_parms->N_RB_DL*12)];
  __m128i *ch_mag;
  int i;
  //  unsigned char symbol_mod;

  //  printf("ulsch_rx.c: ulsch_16qam_llr: symbol %d\n",symbol);

  if (symbol == 0)
    llr128U = (__m128i*)&ulsch_llr[0];

  //  symbol_mod = (symbol>=(7-frame_parms->Ncp)) ? symbol-(7-frame_parms->Ncp) : symbol;

  ch_mag =(__m128i*)&ul_ch_mag[0][(symbol*frame_parms->N_RB_DL*12)];


  for (i=0;i<(nb_rb*3);i++) {


    mmtmpU0 = _mm_abs_epi16(rxF[i]);
    //    print_shorts("tmp0",&tmp0);

    mmtmpU0 = _mm_subs_epi16(mmtmpU0,ch_mag[i]);


    llr128U[0] = _mm_unpacklo_epi16(rxF[i],mmtmpU0);
    llr128U[1] = _mm_unpackhi_epi16(rxF[i],mmtmpU0);
    llr128U+=2;

    //    print_bytes("rxF[i]",&rxF[i]);
    //    print_bytes("rxF[i+1]",&rxF[i+1]);
  }

  _mm_empty();
  _m_empty();

}