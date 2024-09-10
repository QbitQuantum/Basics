void recursiveEval(const CubeSlice<zz_p>& s,
                   const Vec< Vec<zz_p> >& multiEvalPoints,
                   long d,
                   zz_pX& tmp1,
                   Vec<zz_p>& tmp2)
{
   long numDims = s.getNumDims();
   assert(numDims > 0);

   if (numDims > 1) {
      long dim0 = s.getDim(0);
      for (long i = 0; i < dim0; i++)
         recursiveEval(CubeSlice<zz_p>(s, i), multiEvalPoints, d+1, tmp1, tmp2);
   }

   long posBnd = s.getProd(1);
   for (long pos = 0; pos < posBnd; pos++) {
      getHyperColumn(tmp1.rep, s, pos);
      tmp1.normalize();
      eval(tmp2, tmp1, multiEvalPoints[d]);
      setHyperColumn(tmp2, s, pos);
   }

}