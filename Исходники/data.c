int GetMedoid(int cluster) {
	int clustMin = dataAct.clustIndexes[cluster];
	int clustMax;
	int i, j, minDistIndex;
	double sumDist = 0, minDist;

	if (cluster == dataAct.k - 1)
		clustMax = dataAct.centroidsIndex - 1;
	else
		clustMax = dataAct.clustIndexes[cluster + 1] - 1;

	double* avgDist = malloc(sizeof(double) * (clustMax - clustMin + 1));
	minDist = 99999999999;
	minDistIndex = 0;
	for (i = clustMin; i < clustMax + 1; ++i) {
		for (j = clustMin; j < clustMax + 1; ++j) {
			if (i == j) continue;
			sumDist += data.distance(&dataAct.data[i], &dataAct.data[j]);
			if(sumDist > minDist)
				continue;
		}
		if(sumDist > minDist){
			sumDist = 0;
			continue;
		}
		value centroid;
		GetIthCentroid( cluster, &centroid);
		minDist = sumDist;
		minDistIndex = i;
		sumDist = 0;
	}

	
	

	free(avgDist);
	return minDistIndex;
}