void RealFFTf4x(fft_type *buffer,HFFT h)
{

   __m128 *localBuffer=(__m128 *)buffer;

   __m128 *A,*B;
   fft_type *sptr;
   __m128 *endptr1,*endptr2;
   int br1Index, br2Index;
   int br1Value, br2Value;
   __m128 HRplus,HRminus,HIplus,HIminus;
   __m128 v1,v2,sin,cos;
   fft_type iToRad=2*M_PI/(2*h->Points); 

   int ButterfliesPerGroup=h->Points/2;

   /*
   *  Butterfly:
   *     Ain-----Aout
   *         \ /
   *         / \
   *     Bin-----Bout
   */

   endptr1=&localBuffer[h->Points*2];

   while(ButterfliesPerGroup>0)
   {
      A=localBuffer;
      B=&localBuffer[ButterfliesPerGroup*2];
      sptr=h->SinTable;
      int iSinCosIndex=0;
      int iSinCosCalIndex=0;
      while(A<endptr1)
      {
         v4sfu sin4_2, cos4_2;
         if(useSinCosTable) {
            sin=_mm_set1_ps(*(sptr++));
            cos=_mm_set1_ps(*(sptr++));
         } else {
            if(!iSinCosCalIndex)
            {
               v4sfu vx;
               for(int i=0;i<4;i++)
                  vx.m128_f32[i]=((fft_type )SmallReverseBits(iSinCosIndex+i,h->pow2Bits-1))*iToRad;
               sincos_ps(&vx, &sin4_2, &cos4_2);
               sin=_mm_set1_ps(-sin4_2.m128_f32[0]);
               cos=_mm_set1_ps(-cos4_2.m128_f32[0]);
               iSinCosCalIndex++;
            } else {
               sin=_mm_set1_ps(-sin4_2.m128_f32[iSinCosCalIndex]);
               cos=_mm_set1_ps(-cos4_2.m128_f32[iSinCosCalIndex]);
               if(iSinCosCalIndex==3)
                  iSinCosCalIndex=0;
               else
                  iSinCosCalIndex++;
            }
            iSinCosIndex++;
         }
         endptr2=B;
         while(A<endptr2)
         {
            v1 = _mm_add_ps( _mm_mul_ps(*B, cos), _mm_mul_ps(*(B+1), sin));
            v2 = _mm_sub_ps( _mm_mul_ps(*B, sin), _mm_mul_ps(*(B+1), cos));
            *B=_mm_add_ps( *A, v1);
            __m128 temp128 = _mm_set1_ps( 2.0); 
            *(A++)=_mm_sub_ps(*(B++), _mm_mul_ps(temp128, v1));
            *B=_mm_sub_ps(*A,v2);
            *(A++)=_mm_add_ps(*(B++), _mm_mul_ps(temp128, v2));
         }
         A=B;
         B=&B[ButterfliesPerGroup*2];
      }
      ButterfliesPerGroup >>= 1;
   }
   /* Massage output to get the output for a real input sequence. */

   br1Index=1; // h->BitReversed+1;
   br2Index=h->Points-1;   //h->BitReversed+h->Points-1;

   int iSinCosCalIndex=0;
   while(br1Index<br2Index)
   {
      v4sfu sin4_2, cos4_2;
      if(useBitReverseTable) {
         br1Value=h->BitReversed[br1Index];
         br2Value=h->BitReversed[br2Index];
      } else {
         br1Value=SmallReverseBits(br1Index,h->pow2Bits);
         br2Value=SmallReverseBits(br2Index,h->pow2Bits);
      }
      if(useSinCosTable) {
         sin=_mm_set1_ps(h->SinTable[br1Value]);
         cos=_mm_set1_ps(h->SinTable[br1Value+1]);
      } else {
         if(!iSinCosCalIndex)
         {
            v4sfu vx;
            for(int i=0;i<4;i++)
               vx.m128_f32[i]=((float)(br1Index+i))*iToRad;
            sincos_ps(&vx, &sin4_2, &cos4_2);
            sin=_mm_set1_ps(-sin4_2.m128_f32[0]);
            cos=_mm_set1_ps(-cos4_2.m128_f32[0]);
            iSinCosCalIndex++;
         } else {
            sin=_mm_set1_ps(-sin4_2.m128_f32[iSinCosCalIndex]);
            cos=_mm_set1_ps(-cos4_2.m128_f32[iSinCosCalIndex]);
            if(iSinCosCalIndex==3)
               iSinCosCalIndex=0;
            else
               iSinCosCalIndex++;
         }
      }

      A=&localBuffer[br1Value];
      B=&localBuffer[br2Value];
      __m128 temp128 = _mm_set1_ps( 2.0);
      HRplus = _mm_add_ps(HRminus = _mm_sub_ps( *A, *B ), _mm_mul_ps(*B, temp128));
      HIplus = _mm_add_ps(HIminus = _mm_sub_ps(*(A+1), *(B+1) ), _mm_mul_ps(*(B+1), temp128));
      v1 = _mm_sub_ps(_mm_mul_ps(sin, HRminus), _mm_mul_ps(cos, HIplus));
      v2 = _mm_add_ps(_mm_mul_ps(cos, HRminus), _mm_mul_ps(sin, HIplus));
      temp128 = _mm_set1_ps( 0.5);
      *A = _mm_mul_ps(_mm_add_ps(HRplus, v1), temp128);
      *B = _mm_sub_ps(*A, v1);
      *(A+1) = _mm_mul_ps(_mm_add_ps(HIminus, v2), temp128);
      *(B+1) = _mm_sub_ps(*(A+1), HIminus);

      br1Index++;
      br2Index--;
   }
   /* Handle the center bin (just need a conjugate) */
   if(useBitReverseTable) 
      A=&localBuffer[h->BitReversed[br1Index]+1];
   else
      A=&localBuffer[SmallReverseBits(br1Index,h->pow2Bits)+1];
   // negate sse style
   *A=_mm_xor_ps(*A, _mm_set1_ps(-0.f));
   /* Handle DC and Fs/2 bins separately */
   /* Put the Fs/2 value into the imaginary part of the DC bin */
   v1=_mm_sub_ps(localBuffer[0], localBuffer[1]);
   localBuffer[0]=_mm_add_ps(localBuffer[0], localBuffer[1]);
   localBuffer[1]=v1;
}