int main(void){
	/* ソートする配列 */
	FILE *fp ;
	float x[100] ;
	int i = 0;
	fp = fopen("inputint.txt", "r") ;
	while(fscanf(fp, "%f", &x[i]) != EOF) {
		i++ ;
	}
    int n = i ;
	int k ;

    QSort(x, 0, n - 1);
	printf("homework 3-2 no.1\r\n");
	ShowData(x, n);
	printf("\r\n homework 3-2 no.2\r\n");
	printf("%d", n);
	printf("input: k= ");
	scanf("%d", &k);
	if(0 < k && k <= n){
		ShowData(x, k);
	}
	else{
		printf("error");
	}
	return 0;
}