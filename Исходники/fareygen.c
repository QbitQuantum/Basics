static int32_t fareytable (FGDATA *ff, FUNC *ftp)
{
    /*
      This Gen routine calculates a Farey Sequence F_n of the integer n.
      A Farey Sequence F_n of order n is a list of fractions in their lowest
      terms between 0 and 1 and in ascending order. Their denominators do not
      exceed n.
      This means a fraction a/b belongs to F_n if 0 <= a <= b <= n.
      In F_n, the numerator and denominator of each fraction is always coprime.
      0 and 1 are included in F_n as the fractions 0/1 and 1/1.
      For example F_5 = {0/1, 1/5, 1/4, 1/3, 2/5, 1/2, 3/5, 2/3, 3/4, 4/5, 1/1}
      Some properties of the Farey Sequence:
      1. If a/b and c/d are two successive terms of F_n, then bc - ad = 1.
      2. If a/b, c/d, e/f are three successive terms of F_n, then:
      c/d = (a+e) / (b+f)
      c/d is called the mediant fraction between a/b and e/f.
      3. If n > 1, then no two successive terms of F_n have the same denominator.

      The length of any Farey Sequence F_n is determined by
      |F_n| = 1 + SUM (phi(m)) FOR m=1, m<=n, m++
      where phi(m) is Euler's totient function, which gives the number of
      integers <= m that are coprime to m.

      References:
      Hardy, G.M. and Wright, E.M. (1960), An Introduction to the Theory of
                               Numbers, Oxford, 4th Edition, Chapter 3, p.23
      http://mathworld.wolfram.com/FareySequence.html
      http://en.wikipedia.org/wiki/Totient

      Implementation Notes:

      The size of the array of fractions for any F_n is calculated
      with the help Euler's function phi(n), also called totient
      function. For its implementation we included an array of prime
      numbers and a function to determine the prime factor composition
      of a natural integer. The primes dividing the integer are stored
      locally in a small array of ints.

      Important: The length of the table declared by the user does not
      have to be equal to the length of the Farey Sequence. If the
      table is smaller, then only a part of the sequence is copied. If
      it is longer, then zeros are padded.
    */

    int32_t j, fareyseq, nvals, nargs, farey_length, mode;
    MYFLT   *fp = ftp->ftable, *pp, *pp2;
    CSOUND  *csound = ff->csound;
    RATIO *flist;

    nvals = ff->flen;
    nargs = ff->e.pcnt - 4;
    if (UNLIKELY(nargs < 2)) {
      return csound->ftError(ff, Str("insufficient arguments for fareytable"));
    }
    ff->e.p[4] *= -1;
    pp = &(ff->e.p[5]);
    fareyseq = (int32_t) *pp;
    pp2 = &(ff->e.p[6]);
    mode = (int32_t) *pp2;
    farey_length = FareyLength(fareyseq);
    flist = (RATIO*) csound->Calloc(csound, farey_length*sizeof(RATIO));

    GenerateFarey (fareyseq, flist, farey_length);

    switch (mode) {
    default:
    case 0: /* output float elements of F_n */
      for (j = 0;  j < nvals; j++) {
        if (j < farey_length)
          fp[j] = (MYFLT) flist[j].p / (MYFLT) flist[j].q;
      }
      break;
    case 1: /* output delta values of successive elements of F_n */
      {
        MYFLT last = FL(0.0);
        int32_t i = 1;
        for (j = 0; j < nvals; j++, i++) {
          if (i < farey_length) {
            MYFLT current = (MYFLT) flist[i].p / (MYFLT) flist[i].q;
            fp[j] = current - last;
            last = current;
          }
        }
        break;
      }
    case 2: /* output only the denominators of the integer ratios */
      for (j = 0; j < nvals; j++) {
        if (j < farey_length)
          fp[j] = (MYFLT) flist[j].q;
      }
      break;
    case 3: /* output the normalised denominators of the integer ratios */
      {
        MYFLT farey_scale = (MYFLT) 1 / (MYFLT) fareyseq;
        for (j = 0; j < nvals; j++) {
          if (j < farey_length)
            fp[j] = (MYFLT) flist[j].q * farey_scale;
        }
        break;
      }
    case 4: /* output float elements of F_n + 1 for tuning tables*/
      for (j = 0; j < nvals; j++) {
        if (j < farey_length)
          fp[j] = FL(1.0) + (MYFLT) flist[j].p / (MYFLT) flist[j].q;
      }
      break;
    }
    csound->Free(csound,flist);
    return OK;
}