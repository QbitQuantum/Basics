void conv(ZZ_pX& x, const ZZX& a)
{
   conv(x.rep, a.rep);
   x.normalize();
}