	FlexibleTimeMeasurement::FlexibleTimeMeasurement(
		    double expectedValue, double minValue, double maxValue) :
		     TimeMeasurement(expectedValue) {

		computedValue = NaN();
		minFeasibleValue = NaN();
		maxFeasibleValue = NaN();
		setBoundaryValues(minValue, maxValue);
	}