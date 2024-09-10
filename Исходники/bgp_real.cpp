		void check(u_s ID){
			LeftTimesVector[ID] --;
			if(!LeftTimesVector[ID]){
				delete MOldPathDB[ID];
				MOldPathDB[ID] = NULL;
				OInMemoList.remove(ID);
				PathInMemo --;
				fprintf(stderr,"			delete %d from memo\n", ID);
			}
		}