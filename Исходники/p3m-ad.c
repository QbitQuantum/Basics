FLOAT_TYPE Error_ad( system_t *s, parameters_t *p ) {
  FLOAT_TYPE real = Realspace_error( s, p);
  FLOAT_TYPE recp = p3m_k_space_error_ad( s, p );
  //  printf("p3m ad error for mesh %d rcut %lf cao %d alpha %lf : real %e recp %e\n", p->mesh, p->rcut, p->cao, p->alpha, real, recp);
  //  printf("system size %d box %lf\n", s->nparticles, s->length);
  return SQRT( SQR ( real ) + SQR ( recp ) );
}