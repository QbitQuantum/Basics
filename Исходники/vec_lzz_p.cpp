// NOTE: the signature for this is in lzz_p.h
void conv(vec_zz_p& x, const Vec<long>& a)
{
   long i, n;

   n = a.length();
   x.SetLength(n);

   VectorConv(n, x.elts(), a.elts());
}