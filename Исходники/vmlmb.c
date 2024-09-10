/* Update L-BFGS approximation of the Hessian. */
static void
update(opk_vmlmb_t* opt,
       const opk_vector_t* x,
       const opk_vector_t* g)
{
  double sty, yty;
  opk_index_t k;

  k = SLOT(0);
  AXPBY(S(k), 1, x, -1, opt->x0);
  AXPBY(Y(k), 1, g, -1, opt->g0);
  if (opt->method != OPK_VMLMB) {
    /* Compute initial inverse Hessian approximation. */
    sty = DOT(S(k), Y(k));
    if (sty <= 0) {
      /* This pair will be skipped.  This may however indicate a problem, see
         Nocedal & Wright "Numerical Optimization", section 8.1, p. 201 (1999).
         FIXME: restart? */
      RHO(k) = 0;
    } else {
      /* Compute RHO(k) and GAMMA. */
      RHO(k) = 1/sty;
      yty = DOT(Y(k), Y(k));
      if (yty > 0) {
        opt->gamma = sty/yty;
      }
    }
  }
  ++opt->updates;
  if (opt->mp < opt->m) {
    ++opt->mp;
  }
}