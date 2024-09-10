    FdmZabrOp::FdmZabrOp(const boost::shared_ptr<FdmMesher>& mesher,
			const Real beta,
			const Real nu,
			const Real rho,
			const Real gamma)
    : forwardValues_(mesher->locations(0)),
      volatilityValues_(mesher->locations(1)),
	  dxyMap_(SecondOrderMixedDerivativeOp(0, 1, mesher).mult(nu*rho*Pow(Abs(volatilityValues_),gamma+1.0)*Pow(Abs(forwardValues_),beta))),
	  dxMap_(FdmZabrUnderlyingPart(mesher,beta,nu,rho,gamma)),
	  dyMap_(FdmZabrVolatilityPart(mesher,beta,nu,rho,gamma))
	{

    }