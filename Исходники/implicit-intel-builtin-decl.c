void f() {
  (void)_mm_getcsr(); // expected-warning{{implicitly declaring library function '_mm_getcsr'}} \
  // expected-note{{include the header <xmmintrin.h> or explicitly provide a declaration for '_mm_getcsr'}}
  _mm_setcsr(1); // expected-warning{{implicitly declaring library function '_mm_setcsr'}} \
  // expected-note{{include the header <xmmintrin.h> or explicitly provide a declaration for '_mm_setcsr'}}
  _mm_sfence(); // expected-warning{{implicitly declaring library function '_mm_sfence'}} \
  // expected-note{{include the header <xmmintrin.h> or explicitly provide a declaration for '_mm_sfence'}}

  _mm_clflush((void*)0); // expected-warning{{implicitly declaring library function '_mm_clflush'}} \
  // expected-note{{include the header <emmintrin.h> or explicitly provide a declaration for '_mm_clflush'}}
  _mm_lfence(); // expected-warning{{implicitly declaring library function '_mm_lfence'}} \
  // expected-note{{include the header <emmintrin.h> or explicitly provide a declaration for '_mm_lfence'}}
  _mm_mfence(); // expected-warning{{implicitly declaring library function '_mm_mfence'}} \
  // expected-note{{include the header <emmintrin.h> or explicitly provide a declaration for '_mm_mfence'}}
  _mm_pause(); // expected-warning{{implicitly declaring library function '_mm_pause'}} \
  // expected-note{{include the header <emmintrin.h> or explicitly provide a declaration for '_mm_pause'}}
}