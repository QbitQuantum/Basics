ATerm SSL_modr(ATerm x, ATerm y)
{ 
  assert_is_real(x);
  assert_is_real(y);
  return((ATerm) ATmakeReal(fmod(_get_real(x), _get_real(y))));
}