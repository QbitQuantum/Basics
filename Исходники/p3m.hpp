/** Calculate real space contribution of coulomb pair forces.
    If NPT is compiled in, it returns the energy, which is needed for NPT. */
inline double p3m_add_pair_force(double chgfac, double *d,double dist2,double dist,double force[3])
{
  int j;
  double fac1,fac2, adist, erfc_part_ri;
  if(dist < p3m.params.r_cut) {
    if (dist > 0.0){		//Vincent
      adist = p3m.params.alpha * dist;
#if USE_ERFC_APPROXIMATION
      erfc_part_ri = AS_erfc_part(adist) / dist;
      fac1 = coulomb.prefactor * chgfac  * exp(-adist*adist);
      fac2 = fac1 * (erfc_part_ri + 2.0*p3m.params.alpha*wupii) / dist2;
#else
      erfc_part_ri = erfc(adist) / dist;
      fac1 = coulomb.prefactor * chgfac;
      fac2 = fac1 * (erfc_part_ri + 2.0*p3m.params.alpha*wupii*exp(-adist*adist)) / dist2;
#endif
      for(j=0;j<3;j++)
	force[j] += fac2 * d[j];
      ESR_TRACE(fprintf(stderr,"%d: RSE: Pair dist=%.3f: force (%.3e,%.3e,%.3e)\n",this_node,
			dist,fac2*d[0],fac2*d[1],fac2*d[2]));
#ifdef NPT
      return fac1 * erfc_part_ri;
#endif
    }
  }
  return 0.0;
}