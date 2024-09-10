static double awterms(double myaw, void *mydata) {
  int i, t;
  double val = 0;
  double law = log(myaw);
#ifdef A_DEBUG
  float save_a = ddC.SY->a;
  double like;
#endif
  S_remake(ddC.SY, myaw);
  for (t=0; t<ddN.T; t++) {
    uint32_t Tw_ = 0;
    for (i=0; i<ddN.W; i++) {
      Tw_ += ddS.Twt[i][t];
      if ( ddS.Nwt[i][t]>1 ) {
        val += S_S(ddC.SY,ddS.Nwt[i][t],ddS.Twt[i][t]);
      }
    }
    val += Tw_*law + lgamma(ddP.bwpar/myaw+Tw_) - lgamma(ddP.bwpar/myaw);
  }
  myarms_evals++;
#ifdef A_DEBUG
  yap_message("Eval awterms(%lf) = %lf (S had %f)", myaw, val, save_a);
  ddP.awpar = myaw;
  cache_update("aw");
  like = likelihood();
  if ( last_val != 0 ) {
    yap_message(", lp=%lf diffs=%lf vs %lf\n", like,
                val-last_val, like-last_like);
  }
  last_like = like;
  last_val = val;
#endif
  return val;
}