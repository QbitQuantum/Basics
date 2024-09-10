	void Load(char* f)
	{
		vector<standardRecord> emptyVector;

		//Load file in memory
		int size=0;
		char *ptr=0;
		char* cursor=0;
		size=load_file_to_memory(f,&ptr);
		cursor=ptr;

		if(size>0&&ptr!=0)
		{
			cursor=ptr+24+(*(int*)(ptr+4));
			while(cursor<(ptr+size))
				cursor=LoopGRUP(cursor,0,0);
		}

		ParseLoadedData();

		delete ptr;

		//Trick to clear used ram by the vector
		recordPointers.swap(emptyVector);
		recordPointers.clear();
	}