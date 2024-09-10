//void xfft(int gatepow[NGATEAUTO][NFAUTO],char *obuf, char *ibuf, __m128i norm[NCHAN/2][FFTLEN/8],short int idelay[4],int nthread,double time0, double period)
void xfft(char *obuf, char *ibuf, __m128i norm[NCHAN/2][FFTLEN/8],short int idelay[4],int nthread,char walshsign[NCHAN][NWALSH2])
{
  int nbuf,k;
  __declspec(align(128)) static short int fftbuf[4][NCHAN][FFTLEN]; // cache align this

  nbuf=NT/FFTLEN/NCHAN/2;  // the last factor of two because half the data is sent off to quad cores
  omp_set_num_threads(nthread);
#pragma omp parallel for default(none) shared(obuf,ibuf,norm,nbuf,fftbuf,idelay,walshsign)  schedule(dynamic,64)
  for (k=0;k<nbuf-1;k++){
    int i,j,r32,i32,io,imp;
    short int i16,r16,igate,*ibuf16;
    register __m128i r0,r1,r2,r3,r4,r5,r6,r7;
    __m128i *fftbuf_sse;


#ifdef _OPENMP
    imp=omp_get_thread_num();
#else
    imp=0;
#endif
    
    /* we want fftbuf to stay in cache */
    for (j=0;j<NCHAN;j++) {
      for(i=0;i<FFTLEN;i++) {
	char ctmp,ctmp1;
	ctmp=ibuf[(k*FFTLEN+(i+idelay[j]))*NCHAN+j];
//	ctmp1=(ctmp & 0b10111111) | (ctmp >> 1 & 0b0100000); // clip
	fftbuf[imp][j][i]=ctmp*walshsign[j][k/NTCHUNK];
      }
      fft1dippirc16(fftbuf[imp][j],fftbuf[imp][j],1);
      fftbuf_sse=fftbuf[imp][j];
      for(i=0;i<FFTLEN/8;i++) fftbuf_sse[i]=_mm_mulhi_epi16(fftbuf_sse[i],norm[j][i]);
      r7=_mm_set1_epi8(0xf0);
      for (i=0;i<FFTLEN/2;i+=FFTBLOCK){
#if 0
	for (io=0;io<FFTBLOCK;io++){ // we process 2 numbers at once.
	  r32=fftbuf[imp][j][2*(i+io)];
//	  r32=r32*norm[j][i+io];
	  i32=fftbuf[imp][j][2*(i+io)+1];
//	  i32*=norm[j][i+io];
          obuf[io+j*FFTBLOCK+k*FFTBLOCK*NCHAN+i*(NT/(FFTLEN)/2)]=(r32 >> 16)&0x0f | (i32 >> 12)&0xf0;
	}
#else
	for (io=0;io<FFTBLOCK;io+=2*8){ // we process 32 numbers at once.
	/* bits 5-8  are extracted(?) */
	  r0=_mm_load_si128(&fftbuf[imp][j][2*(i+io)]);
	  r1=_mm_load_si128(&fftbuf[imp][j][2*(i+io)+8]);
	  r2=_mm_load_si128(&fftbuf[imp][j][2*(i+io)+16]);
	  r3=_mm_load_si128(&fftbuf[imp][j][2*(i+io)+24]);  // squeeze four 16-bit ints into 4-bit ints
#define MMSHUF _MM_SHUFFLE(3,1,2,0)   // little endian, swap i1 r1 i0 r0 -> i1 i0 r1 r0
	  r5=_mm_shufflehi_epi16(r0,MMSHUF);  
	  r6=_mm_shufflelo_epi16(r5,MMSHUF);
	  r0=_mm_shuffle_epi32(r6,MMSHUF);  // i3 i2 r3 r2 i1 i0 r1 r0 -> i3210 r3210
	  r5=_mm_shufflehi_epi16(r1,MMSHUF);
	  r6=_mm_shufflelo_epi16(r5,MMSHUF);
	  r1=_mm_shuffle_epi32(r6,MMSHUF);
	  r5=_mm_unpacklo_epi64(r0,r1);   // r0=i3210r3210, r1=i7654r7654 -> r5=r76543210
	  r6=_mm_unpackhi_epi64(r0,r1);    // r6=i76543210
	  r0=r5;
	  r1=r6;
	  
	  // now for the second set
	  r5=_mm_shufflehi_epi16(r2,MMSHUF);
	  r6=_mm_shufflelo_epi16(r5,MMSHUF);
	  r2=_mm_shuffle_epi32(r6,MMSHUF);
	  r5=_mm_shufflehi_epi16(r3,MMSHUF);
	  r6=_mm_shufflelo_epi16(r5,MMSHUF);
	  r3=_mm_shuffle_epi32(r6,MMSHUF);
	  r5=_mm_unpacklo_epi64(r2,r3);
	  r6=_mm_unpackhi_epi64(r2,r3);
	  r2=r5;  // r5 is the real part
	  r3=r6;
	  /* this part reduces the number of bits to LSB with saturate */
	  
	  r5=_mm_packs_epi16(r0,r2);  // r5=rFEDCBA9876543210, saturate
	  r0=_mm_srli_epi16(r5,4);    // in little-endian, real into LSB
	  // modified next few lines to just store MSB's.
	  r0=_mm_andnot_si128(r7,r0);//zero 4 MSB
	  r6=_mm_packs_epi16(r1,r3);  // imaginary
	  r1=_mm_and_si128(r6,r7);
	  r2=_mm_or_si128(r0,r1);
	/* write without polluting caches */
	  _mm_stream_si128(&obuf[io+j*FFTBLOCK+k*FFTBLOCK*NCHAN+i*(NT/FFTLEN/2)],r2);
	  /* the outgoing structure is obuf[FFTREST][TIME][CHAN][FFTBLOCK].
	     The BLOCK is cache friendly, the FFTREST is the MPI transpose order,
	     and we need all channels locally for the correlation.
	  */
	}
#endif
	// prefetch obuf non-persistent
      }
    }
  }
}