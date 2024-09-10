int main(){
	char dayOfWeek[7][10] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int yearst[8010], yr, y, m, d, dw, n;
	yearst[0] = 0;
	for(yr=1; yr<8010; yr++){
		yearst[yr] = yearst[yr-1] + 365 + isLeap(yr+1999);
	}

	scanf("%d", &n);
	while(n >= 0){
		dw = n%7;
		y = bSearch(yearst, 8010, n);
		n -= yearst[y];
		y += 2000;
		for(m=0; ; m++){
			if(m == 1 && n < month[m]+isLeap(y))
				break;
			if(n < month[m])
				break;
			if(m == 1)
				n -= month[m] + isLeap(y);
			else
				n -= month[m];
		}
		d = n+1;
		printf("%d-%02d-%02d %s\n", y, m+1, d, dayOfWeek[dw]);

		scanf("%d", &n);
	}
	return 0;
}