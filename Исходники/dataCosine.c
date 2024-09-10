void RateItemsCosine(value* lvalue, value** nn, int size, List Rresult){
	int i,j,k,pos;
	double R;
	int *x = lvalue->content;
	hashTable rated;
	int hashSize = co.users[*x].NoOfItems*size;
	int** array = malloc(co.users[*x].NoOfItems*sizeof(int*));
	Rating rating;

	InitHashTable(&rated,hashSize,sizeof(int),NULL,
			distanceCos,IntHashFuncCos,NULL);
	//InitList(Rresult,sizeof(int),NULL,distance,NULL);

	for(i=0; i<co.users[*x].NoOfItems; ++i){
		InsertHashTable(rated, &co.users[*x].myitems[i].id,NULL);
	}
	double z = 0.0;
	for ( i = 0; i < size; ++i)
	{
		//z+=abs((-data.distance(lvalue,nn[i])-1));
		double tmp = (-data.distance(lvalue,nn[i])-1);
		z+= ( tmp <0 ? -tmp : tmp);
	}
	z = 1/z;
	double Ru = 0.0;
	for (k = 0; k < co.users[*x].NoOfItems; ++k)
	{
		Ru+=co.users[*x].myitems[k].score;
	}
	Ru/=co.users[*x].NoOfItems;
	for(i=0; i<size; ++i){
		int* curr = nn[i]->content;

		for(j=0; j<co.users[*curr].NoOfItems; ++j ){
			if(SearchHashTable(rated, &co.users[*curr].myitems[j].id)!=NULL){
				continue;
			}
			InsertHashTable(rated, &co.users[*curr].myitems[j].id,NULL);
			double sum = 0.0;
			int avg = 0;
			for (k = 0; k < co.users[*curr].NoOfItems; ++k)
			{
				avg+=co.users[*curr].myitems[k].score;
			}
			avg/=co.users[*curr].NoOfItems;
			for(k=0; k<size; ++k){
				int l;
				int *index = nn[k]->content;
				// for(l=0; l<co.users[*index].NoOfItems; l++){
				// 	printf("%d ",co.users[*index].myitems[l].id );
				// }
				// printf("\n");
				
				pos=BinarySearchCosine(co.users[*index].myitems,co.users[*index].NoOfItems,co.users[*curr].myitems[j].id);
				//printf("%d %d\n", co.users[*curr].myitems[j].id,pos);
				if(pos == -1)
					continue;
				sum+= (-data.distance(lvalue,nn[k])+1)*(co.users[k].myitems[pos].score-avg);
				//printf("dist %f score %d \n", (-data.distance(lvalue,nn[k])+1),co.users[k].myitems[pos].score);
			}
			R = Ru+z*sum;
			rating.rate = R;
			rating.id = co.users[*curr].myitems[j].id;
			InsertValueList(Rresult, &rating);
			//printf("%f , %d\n",R, co.users[*curr].myitems[j].id);
		}

	}
}