static void process_sinc(rarch_resampler_t *resamp, float *out_buffer)
{
   __m128 sum_l = _mm_setzero_ps();
   __m128 sum_r = _mm_setzero_ps();

   const float *buffer_l = resamp->buffer_l + resamp->ptr;
   const float *buffer_r = resamp->buffer_r + resamp->ptr;

   unsigned phase = resamp->time >> PHASES_SHIFT;
   unsigned delta = (resamp->time >> SUBPHASES_SHIFT) & SUBPHASES_MASK;
   __m128 delta_f = _mm_set1_ps(delta);

   const float *phase_table = resamp->phase_table[phase][PHASE_INDEX];
   const float *delta_table = resamp->phase_table[phase][DELTA_INDEX];

   for (unsigned i = 0; i < TAPS; i += 4)
   {
      __m128 buf_l  = _mm_loadu_ps(buffer_l + i);
      __m128 buf_r  = _mm_loadu_ps(buffer_r + i);

      __m128 phases = _mm_load_ps(phase_table + i);
      __m128 deltas = _mm_load_ps(delta_table + i);

      __m128 sinc   = _mm_add_ps(phases, _mm_mul_ps(deltas, delta_f));

      sum_l         = _mm_add_ps(sum_l, _mm_mul_ps(buf_l, sinc));
      sum_r         = _mm_add_ps(sum_r, _mm_mul_ps(buf_r, sinc));
   }

   // Them annoying shuffles :V
   // sum_l = { l3, l2, l1, l0 }
   // sum_r = { r3, r2, r1, r0 }

   __m128 sum = _mm_add_ps(_mm_shuffle_ps(sum_l, sum_r, _MM_SHUFFLE(1, 0, 1, 0)),
         _mm_shuffle_ps(sum_l, sum_r, _MM_SHUFFLE(3, 2, 3, 2)));

   // sum   = { r1, r0, l1, l0 } + { r3, r2, l3, l2 }
   // sum   = { R1, R0, L1, L0 }

   sum = _mm_add_ps(_mm_shuffle_ps(sum, sum, _MM_SHUFFLE(3, 3, 1, 1)), sum);

   // sum   = {R1, R1, L1, L1 } + { R1, R0, L1, L0 }
   // sum   = { X,  R,  X,  L } 

   // Store L
   _mm_store_ss(out_buffer + 0, sum);

   // movehl { X, R, X, L } == { X, R, X, R }
   _mm_store_ss(out_buffer + 1, _mm_movehl_ps(sum, sum));
}