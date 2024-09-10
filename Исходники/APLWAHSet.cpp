void APLWAHSet::intersection(const vector<APLWAHSet>& sets, vector<int>& ret){
	ret.clear();
	ret.reserve(sets[0].length/sets.size());

	WordItr* baseItr = new WordItr[sets.size()];
	for(unsigned int i=0;i<sets.size();i++){
		baseItr[i] = sets[i].bitmap.begin();
	}
	
	APLWAHDecoder* Decoders = new APLWAHDecoder[sets.size()];

	int* ChunkItr = new int[sets.size()];
	memset(ChunkItr,0,sizeof(int)*sets.size());
	
	//int lastLit = 0;

	while((!Decoders[0].isEmpty) || (baseItr[0] != sets[0].bitmap.end())){
		Word lit = 0;
		
		//grab a Literal from sets[0]
		if(Decoders[0].isEmpty){
			Word w = *baseItr[0];
			baseItr[0]++;

			if(_bittestandreset((long*)&w,31)){
				lit = w;
				ChunkItr[0]++;
			}
			else{
				Decoders[0].extractHalf(w);
				if(Decoders->len1 != 0){
					Decoders->extractL1();
					lit = Decoders->lit1;
					ChunkItr[0]++;
				}
				else if(Decoders->len2 != 0){
					ChunkItr[0] += Decoders[0].counter + 1;
					Decoders->extractL2();
					lit = Decoders->lit2;
					Decoders->clear();
				}
				else{
					ChunkItr[0] += Decoders[0].counter;
					Decoders->clear();
				}
			}
		} else{
			ChunkItr[0] += Decoders[0].counter;
			if(Decoders[0].len2 != 0){
				Decoders->extractL2();
				lit = Decoders->lit2;
				ChunkItr[0]++;
			}
			Decoders->clear();
		}

		if(lit == 0) continue;

		// a Literal has been grabbed
		for(unsigned int i=1;i<sets.size();i++){
			if(ChunkItr[i] >= ChunkItr[0]) {
				lit = 0;
				break;
			} 

			while(true){
				//上一轮有残余的LFL
				if(!Decoders[i].isEmpty){ 
					int step = Decoders[i].counter + (Decoders[i].len2  != 0);
					if(ChunkItr[i] + step > ChunkItr[0]){
						ChunkItr[i] += Decoders[i].counter;
						Decoders[i].counter = 0;
						lit = 0;
						if(Decoders[i].len2 == 0) Decoders[i].clear();
						break;
					}
					else if(ChunkItr[i] + step == ChunkItr[0]){
						ChunkItr[i]+= step;
						if(Decoders[i].len2 == 0) {
							lit = 0;
						}
						else{
							Decoders[i].extractL2();
							lit &= Decoders[i].lit2;
						}
						Decoders[i].clear();
						break;
					}
					else{
						ChunkItr[i]+=step;
						Decoders[i].clear();
					}
				}
				else if(baseItr[i] == sets[i].bitmap.end()){
					lit = 0;
					break;
				}
				else{ 
					Word sw = *(baseItr[i]);
					baseItr[i]++;
					int step = 0;
					if(_bittest((long*)&sw,31)){
						step = 1;
					}
					else{
						step = Decoders[i].extractHalf(sw);
					}

					if(ChunkItr[i] + step > ChunkItr[0]){
						if(step == 1){
							printf("Terrible Error!!\n\n\n");
						}

						//进入此分支，说明第一个Literal是与base 对齐的
						else if(Decoders[i].len1 != 0 && ((ChunkItr[i] + 1) == ChunkItr[0])){
							Decoders[i].extractL1();
							lit &= Decoders[i].lit1;
							ChunkItr[i]++;
						}

						else if(Decoders[i].len2 != 0){
							ChunkItr[i] += Decoders[i].counter + (Decoders[i].len1 != 0);
							Decoders[i].counter = 0;
							lit = 0;
						}
						else{
							ChunkItr[i] += step;
							Decoders[i].clear();
							lit = 0;
						}
						break;
					}
					else if(ChunkItr[i] + step == ChunkItr[0]){
						ChunkItr[i] += step;
						if(_bittest((long*)&sw,31)){
							lit &= sw;
						}
						else if(Decoders[i].len2 != 0){
							Decoders[i].extractL2();
							lit &= Decoders[i].lit2;
							Decoders[i].clear();
						}
						else{
							Decoders[i].clear();
							lit = 0;
						}
						break;
					}
					else{
						ChunkItr[i] += step;
						Decoders[i].clear();
					}
				}
			}
		
			if(lit == 0 || lit == 0x80000000) break;
		}
		//for 循环结束
		if(lit != 0 && lit != 0x80000000){
			int baseNum = ChunkItr[0]*31 - 31;
			_bittestandreset((long*)&lit,31);
			while(lit != 0){
				int zc = _tzcnt_u32(lit);
				_bittestandreset((long*)&lit,zc);
				ret.push_back(zc + baseNum);
			}
		}
		
	}

	return;
}