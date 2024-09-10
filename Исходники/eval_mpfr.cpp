 void bvisit(const ATan2 &x) {
     mpfr_class t(mpfr_get_prec(result_));
     apply(t.get_mpfr_t(), *(x.get_num()));
     apply(result_, *(x.get_den()));
     mpfr_atan2(result_, t.get_mpfr_t(), result_, rnd_);
 }