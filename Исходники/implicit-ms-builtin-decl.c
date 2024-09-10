void f() {
  (void)_byteswap_ushort(42); // expected-warning{{implicitly declaring library function '_byteswap_ushort}} \
  // expected-note{{include the header <stdlib.h> or explicitly provide a declaration for '_byteswap_ushort'}}
  (void)_byteswap_uint64(42LL); // expected-warning{{implicitly declaring library function '_byteswap_uint64}} \
  // expected-note{{include the header <stdlib.h> or explicitly provide a declaration for '_byteswap_uint64'}}
}