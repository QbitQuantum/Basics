FLOAT_TYPE p3m_k_space_error_ik_i ( system_t *s, parameters_t *p ) {
  int  nx, ny, nz;
  FLOAT_TYPE he_q = 0.0;
  FLOAT_TYPE alias1, alias2, alias3, alias4, n2;
  int mesh = p->mesh;

  he_q = p3m_find_error(p->alpha*s->length, mesh, p->cao, 1);

  if(he_q < 0) {
    he_q = 0.0;
    for ( nx=-mesh/2; nx<mesh/2; nx++ ) {
      for ( ny=-mesh/2; ny<mesh/2; ny++ ) {
	for ( nz=-mesh/2; nz<mesh/2; nz++ ) {
	  if ( ( nx!=0 ) || ( ny!=0 ) || ( nz!=0 ) ) {
	    n2 = SQR ( nx ) + SQR ( ny ) + SQR ( nz );

	    p3m_tune_aliasing_sums_ik_i ( nx,ny,nz, s, p, &alias1,&alias2,&alias3, &alias4 );
	    he_q +=  alias1  -  SQR ( alias2 ) / (0.5*n2*(SQR(alias3)+SQR(alias4)) );
	  }
	}
      }
    }
    he_q = FLOAT_ABS(he_q);
  }
  return 2.0*s->q2*SQRT ( he_q/ ( FLOAT_TYPE ) s->nparticles ) / ( SQR ( s->length ) );
}