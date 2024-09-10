 Beta(Teuchos::ParameterList &parlist) {
   shape1_ = parlist.sublist("SOL").sublist("Distribution").sublist("Beta").get("Shape 1",2.);
   shape2_ = parlist.sublist("SOL").sublist("Distribution").sublist("Beta").get("Shape 2",2.);
   shape1_ = (shape1_ > 0.) ? shape1_ : 2.;
   shape2_ = (shape2_ > 0.) ? shape2_ : 2.;
   coeff_ = tgamma(shape1_+shape2_)/(tgamma(shape1_)*tgamma(shape2_));
   initializeQuadrature();
 }