int main()
{
	enum	 {heitao,hongtao,meihua,fangkuai}s;
	int		i,j,l,k;
	int	 a[52] = {1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13};
	int		p0[18],p1[18],p2[18];
	int 	 str[2] = {53,54};
    int	 m = 0,n = 0,t = 0;

	srand(time(NULL));
	for (k = 0; k < 52; k++) {
		for(j = 0; j < 17; j++)	{
			p0[j] = a[rand() % 52];
			m++;
			p1[j] = a[rand() % 52];
			n++;
			p2[j] = a[rand() % 52];
			t++;
		}
		if(m == 18)	{
			 
			p1[17] = str[rand() % 2];
			p2[17] = str[rand() % 2];
		}
		else if(n == 18) {
			p0[17] = str[rand() % 2];
			p2[17] = str[rand() % 2];
		}
		else if(t == 18) {
			p0[17] = str[rand() % 2];
			p1[17] = str[rand() % 2];
			}
	}
	printf("p0:");
	for(j=0;j<18;j++) {
		switch ((rand() % 52) / 13)	{
			case 0:
				printf("heitao");
				break;
			case 1:
				printf("hongtao");
				break;
			case 2:
				printf("meihua");
				break;
			case 3:
				printf("fangkuai");
				break;
		}
		printf("%d   ",p0[j]);
	}
	printf("\n");


    printf("p1:");
	for(j=0;j<18;j++) {

		switch ((rand() % 52) / 13)	{
			case 0:
				printf("heitao");
				break;
			case 1:
				printf("hongtao");
				break;
			case 2:
				printf("meihua");
				break;
			case 3:
				printf("fangkuai");
				break;
		}
		printf("%d   ",p1[j]);
	}
	printf("\n");


	printf("p2:");
	for(j=0;j<18;j++) {
		switch ((rand() % 52) / 13)	{
			case 0:
				printf("heitao");
				break;
			case 1:
				printf("hongtao");
				break;
			case 2:
				printf("meihua");
				break;
			case 3:
				printf("fangkuai");
				break;
		}
		printf("%d   ",p2[j]);
	}
	printf("\n");
	return 0;
}