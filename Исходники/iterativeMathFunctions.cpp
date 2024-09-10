long double IterativeMathFunctions::weightedSumHelper(InstanceIterator & itr, long double & totalWeight) {
	double value, weight;
	long double sum=0;
	totalWeight=0;
	for (itr.start();itr.getInstance(value,weight);itr.next()) {
		double weigthedValue=value*weight;
		sum+=weigthedValue;
		totalWeight+=weight;
	}
	return sum;
}