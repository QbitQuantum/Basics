void
foo ()
{
  _mm256_zeroupper ();
  x = y;
  _mm256_zeroupper ();
  _mm256_zeroupper ();
  _mm256_zeroupper ();
}