/* multiply the accumulators
 * by the inverse diagonal
 * hessian (hess) 
 */
void 
Hess_acc(weight *nptr)
{
  int i, iend;
  weight *w;

  if (nptr==NULL) {
    w=weightbase;
    iend=weightnombre;
  } else {
    w=nptr;
    iend=1; 
  }
  for ( i=0; i<iend; i++, w++ ) {
    w->Wacc=Fdiv( w->Wacc, Fadd( mu, Fabs(w->Whess)));
  }
}