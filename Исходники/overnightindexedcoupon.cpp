	Real ArithmeticAveragedOvernightIndexedCouponPricer::convAdj1(Time ts, Time te) const {
		Real vol = vol_->value();
		Real k = meanReversion_->value();
		return vol * vol / ( 4.0 * pow(k, 3.0) ) * ( 1.0 - exp(-2.0*k*ts)) * pow(( 1.0 - exp(-k*(te-ts)) ), 2.0);
	}