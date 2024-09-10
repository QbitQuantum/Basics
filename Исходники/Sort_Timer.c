//Main Function
int main (void){
	int i= 0, j = 0, temp;
	clock_t start, end , one_timer, two_timer;
	int maindata[Num];
	srand((unsigned int)(time(NULL)));
	go_first(maindata,Num);
	start = clock();
	for(i = 0; i<Num; i ++){
		for(j = Num ; j > i; j--){
			if(maindata[j] < maindata[j-1]){
				temp = maindata[j];
				maindata[j] = maindata[j-1];
				maindata[j-1] = temp;
			}
		}
	}
	end = clock();
	one_timer = end - start;
	go_first(maindata,Num);
	start = clock();
	qsort(maindata,Num,sizeof(int),int_compare);
	end = clock();
	two_timer = end - start;
	printf("Time1 takes %dclock and %d second!\n",one_timer, one_timer/CLOCKS_PER_SEC);
	printf("Time2 takes %dclock and %d second!\n",two_timer, two_timer/CLOCKS_PER_SEC);
	_sleep(10000);
}