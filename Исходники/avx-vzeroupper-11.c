void
foo ()
{
  x = y;
  _mm256_zeroall ();
  _mm256_zeroupper ();
  _mm256_zeroupper ();
  _mm256_zeroupper ();
}