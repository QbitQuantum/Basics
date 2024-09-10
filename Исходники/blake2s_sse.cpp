static void blake2s_init_sse()
{
  // We cannot initialize these 128 bit variables in place when declaring
  // them globally, because global scope initialization is performed before
  // our SSE check and it would make code incompatible with older non-SSE2
  // CPUs. Also we cannot initialize them as static inside of function
  // using these variables, because SSE static initialization is not thread
  // safe: first thread starts initialization and sets "init done" flag even
  // if it is not done yet, second thread can attempt to access half-init
  // SSE data. So we moved init code here.

  blake2s_IV_0_3 = _mm_setr_epi32( 0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A );
  blake2s_IV_4_7 = _mm_setr_epi32( 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19 );

#ifdef _WIN_64
  crotr8 = _mm_set_epi8( 12, 15, 14, 13, 8, 11, 10, 9, 4, 7, 6, 5, 0, 3, 2, 1 );
  crotr16 = _mm_set_epi8( 13, 12, 15, 14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2 );
#endif
}