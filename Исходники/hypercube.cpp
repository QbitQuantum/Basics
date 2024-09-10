void setHyperColumn(const Vec<T>& v, const CubeSlice<T>& s, long pos, const T& val)
{
   long m = s.getProd(1);
   long n = s.getDim(0);
   long n1 = n;

   assert(pos >= 0 && pos < m);
   if (v.length() < n) n1 = v.length();

   const T* vp = &v[0];
   T* sp = &s[0];

   for (long i = 0; i < n1; i++)
      sp[pos + i*m] = vp[i];

   for (long i = n1; i < n; i++)
      sp[pos + i*m] = val;
}