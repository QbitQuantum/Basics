    Fdm2dBlackScholesOp::Fdm2dBlackScholesOp(
            const boost::shared_ptr<FdmMesher>& mesher,
            const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
            const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
            Real correlation,
            Time maturity,
            bool localVol,
            Real illegalLocalVolOverwrite)
    : mesher_(mesher),
      p1_(p1),
      p2_(p2),
      
      localVol1_((localVol) ? p1->localVolatility().currentLink()
                            : boost::shared_ptr<LocalVolTermStructure>()),
      localVol2_((localVol) ? p2->localVolatility().currentLink()
                            : boost::shared_ptr<LocalVolTermStructure>()),
                            
      x_((localVol) ? Array(Exp(mesher->locations(0))) : Array()),
      y_((localVol) ? Array(Exp(mesher->locations(1))) : Array()),

      opX_(mesher, p1, p1->x0(), localVol, illegalLocalVolOverwrite, 0),
      opY_(mesher, p2, p2->x0(), localVol, illegalLocalVolOverwrite, 1),
      
      corrMapT_(0, 1, mesher),
      corrMapTemplate_(SecondOrderMixedDerivativeOp(0, 1, mesher)
                      .mult(Array(mesher->layout()->size(), correlation))),
                      
      illegalLocalVolOverwrite_(illegalLocalVolOverwrite) { 
    }