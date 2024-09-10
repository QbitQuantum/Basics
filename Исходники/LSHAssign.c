void BFAssign(int index){
	int i;
	double dist = 9999999999;
	double dist2 = 9999999999;
	int kVal = 0;
	int kVal2 = 0;
	value v1,v2;
	GetIthData(index, &v2);
	for(i = 0 ; i< GetNoOfCluster(); i++){
		GetIthCentroid(i, &v1);
		double tempDist = data.distance(&v1, &v2);

		if (tempDist < dist2) {
			if (tempDist < dist) {
				kVal2 = kVal;
				dist2 = dist;
				kVal = i;
				dist = tempDist;
			} else {
				kVal2 = i;
				dist2 = tempDist;
			}
		}
	}
	AssignClustExtra(index,kVal,dist,kVal2,dist2);
}