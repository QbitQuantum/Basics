/* Update L-BFGS approximation of the Hessian. */
static void
update(opk_vmlmn_t* opt,
       const opk_vector_t* x,
       const opk_vector_t* g)
{
  double sty, yty;
  opk_index_t k;

  k = slot(opt, 0);
  AXPBY(S(k), 1, x, -1, opt->x0);
  AXPBY(Y(k), 1, g, -1, opt->g0);
  if (opt->method != OPK_VMLMN) {
    /* Compute initial inverse Hessian approximation. */
    sty = DOT(Y(k), S(k));
    if (sty <= 0) {
      RHO(k) = 0;
    } else {
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