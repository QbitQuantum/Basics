void shuffle(vector<T> &v){
	vector<T> temp;
	 T locations[v.size()];
	for (int i = 0; i < v.size(); i++){
		do{
			locations[i] = rand() % v.size();
		} while (i != 0 || include(locations, i, locations[i]));
		temp.push_back(v.at(locations[i]));
	}
	v.swap(temp);
}