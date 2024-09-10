vector<float> CircularBuffer::creatHistogram(int partitionN){
	vector<float> histogram(8 * partitionN);
	float angle;
	float mod;

	int frameN = maxSize/partitionN;

	for(int j = 0; j < partitionN; ++j){
		for(int i = j * frameN; i < (j + 1) * frameN; ++i){
			int pos = startPoint + i;
			if(pos >= maxSize)
				pos = pos - maxSize;

			if(!zero(v[pos])){
				mod = getMod(v[pos]);

				if(v[pos].first == 0 && v[pos].second > 0){//positive y direction
					histogram[2 + 8 * j] += mod;
					continue;
				}else if(v[pos].first == 0 && v[pos].second < 0){//negative y direction
					histogram[6 + 8 * j] += mod;
					continue;
				}else if(v[pos].second == 0 && v[pos].first > 0){//positive x direction
					histogram[0 + 8 * j] += mod;
					continue;
				}else{//negative x direction
					histogram[4 + 8 * j] += mod;
					continue;
				}

				angle = atan((v[pos].second*1.0)/v[pos].first);

				if(v[pos].first > 0 && v[pos].second > 0){//positive x and positive y region
					if(angle <= 3.1415926/4){
						histogram[0 + 8 * j] += mod;
						continue;
					}
					if(angle > 3.1415926/4 && angle < 3.1415926/2){
						histogram[1 + 8 * j] += mod;
						continue;
					}
				}else if(v[pos].first > 0 && v[pos].second < 0){//positive x and negative y region
					if(angle > 3.1415926/4){
						histogram[7 + 8 * j] += mod;
						continue;
					}
					if(angle > -3.1415926/2 && angle < -3.1415926/4){
						histogram[6 + 8 * j] += mod;
						continue;
					}
				}else if(v[pos].first < 0 && v[pos].second > 0){//negative x and positive y region
					if(angle > -3.1415926/4){
						histogram[3 + 8 * j] += mod;
						continue;
					}
					if(angle > -3.1415926/2 && angle < -3.1415926/4){
						histogram[2 + 8 * j] += mod;
						continue;
					}
				}else if(v[pos].first < 0 && v[pos].second < 0){//negative x and negative y region
					if(angle <= 3.1415926/4){
						histogram[4 + 8 * j] += mod;
						continue;
					}
					if(angle > 3.1415926/4 && angle < 3.1415926/2){
						histogram[5 + 8 * j] += mod;
						continue;
					}
				}
			}//end of if
		}//end of for
	}

	for(int i = 0; i < 8 * partitionN; ++i){
		histogram[i] /= frameN * 1.0;
	}

	return histogram;
}