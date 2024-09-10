	//find W(word) in S(sentence)
	//return the index of the first appearance
	//implementing KMP algorithm
	int CharString::indexOf(CharString W, int start) const{
		if(W.length() == 0)
			return NOT_FOUND;
		if(W.length() == 1)
			return indexOf(W[0], start);

		//first, make the table
		int* T = new int[W.length()];
		int pos=2, cnd=0;
		T[0] = -1;
		T[1] = 0;

		while(pos < W.length()){
			if(W[pos-1] == W[cnd]){
				cnd = cnd + 1;
				T[pos] = cnd;
				pos = pos + 1;
			}else if(cnd > 0){
				cnd = T[cnd];
			}else{
				T[pos] = 0;
				pos = pos + 1;
			}
		}


		//now let's do KMP 
		int m=start, i=0;
		while((m + i) < length()){
			if(W[i] == operator[](m+i)){
				if(i == W.length() - 1)
					return m;
				i = i + 1;
			}else{
				if(T[i] > -1){
					m = m + i - T[i];
					i = T[i];
				}else{
					i = 0;
					m = m + 1;
				}
			}
		}
		return NOT_FOUND;
	}