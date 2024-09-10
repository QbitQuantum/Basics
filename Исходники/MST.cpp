double dist(int i, int j){
	return sqrt( (double)pow((double)coord[i][0]-coord[j][0], 2) + (double)pow((double)coord[i][1]-coord[j][1], 2) );
}