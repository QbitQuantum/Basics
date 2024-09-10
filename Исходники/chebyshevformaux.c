/*Wrapper to get directly the coeffs in the Chebyshev basis
  from a polynomial in the monomial basis given by a *node
  We return in n = deg(f)+1;
*/
void getChebCoeffsFromPolynomial(sollya_mpfi_t**coeffs, int *n, node *f, sollya_mpfi_t x, mp_prec_t prec){
  sollya_mpfi_t z1, z2, ui, vi;
  node **coefficients;
  int d,i;
  sollya_mpfi_t *p, *c;
  mpfr_t u,v;
  if (isPolynomial(f) ){
    getCoefficients(&d, &coefficients, f);

    *n=d+1;

    *coeffs= (sollya_mpfi_t *)safeMalloc((d+1)*sizeof(sollya_mpfi_t));

    p=safeMalloc((d+1)*sizeof(sollya_mpfi_t));
    c=safeMalloc((d+1)*sizeof(sollya_mpfi_t));
    for (i=0;i<d+1;i++){
      sollya_mpfi_init2((*coeffs)[i],prec);
      sollya_mpfi_init2(p[i],prec);
      sollya_mpfi_init2(c[i],prec);
      if (coefficients[i]!= NULL)  mpfi_set_node(p[i],coefficients[i], prec);
      else sollya_mpfi_set_ui(p[i],0);
    }

    for (i=0;i<d+1;i++) {
      if (coefficients[i] != NULL)
        free_memory(coefficients[i]);
    }
    safeFree(coefficients);

    /*Here we have the coeffs of the polynomial in p, over the interval x=[a,b]*/
    /*we need to compute the polynomial over [-1,1]*/
    /*we make the change of variable: x= y*(b-a)/2 + (b+a)/2, hence for y \in [-1,1] we have x\in [a,b]*/
    /* we compute P(x)=Q(y)*/
    sollya_mpfi_init2(ui, prec);
    sollya_mpfi_init2(vi, prec);


    mpfr_init2(u, prec);
    mpfr_init2(v, prec);

    sollya_mpfi_init2(z1, prec);
    sollya_mpfi_init2(z2, prec);

    sollya_mpfi_get_left(u,x);
    sollya_mpfi_get_right(v,x);

    sollya_mpfi_set_fr(ui,u);
    sollya_mpfi_set_fr(vi,v);

    sollya_mpfi_add(z2,ui,vi);
    sollya_mpfi_sub(z1,vi,ui);

    sollya_mpfi_div_ui(z1,z1,2);
    sollya_mpfi_div_ui(z2,z2,2);

    getTranslatedPolyCoeffs(c, p, d+1, z1,z2);

    getPolyCoeffsChebBasis(*coeffs, c, d+1);

    /*cleaning*/

    for (i=0;i<d+1;i++){
      sollya_mpfi_clear(p[i]);
      sollya_mpfi_clear(c[i]);
    }
    safeFree(p);
    safeFree(c);

    sollya_mpfi_clear(ui);
    sollya_mpfi_clear(vi);


    mpfr_clear(u);
    mpfr_clear(v);

    sollya_mpfi_clear(z1);
    sollya_mpfi_clear(z2);


  }
  else{
    printMessage(1,SOLLYA_MSG_ERROR_IN_CHEBYSHEVFORM_NOT_A_POLYNOMIAL,
		 "The given function is not a polynomial, no modification is made.\n");
  }
}