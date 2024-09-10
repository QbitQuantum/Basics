void apply_pi(vector<int> &vec) {
	int N = temp.size();
	for(int i = 0; i < N; i++) {
		temp[ Pi[i]-1 ] = vec[i];	
	}
	vec.swap(temp);
	return;
}