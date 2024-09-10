int main(void)
{
	double value;
	char *pstr;
	int dec, sign;

	value=3.1415926535;
	pstr=fcvt(value,6,&dec,&sign);
	printf("문자열 : %s, 소수점 위치 : %d, 부호는 %d,",pstr,dec,sign);
	
	value=-3.1415926535;
	pstr=fcvt(value,8,&dec,&sign);
	printf("문자열 : %s, 소수점 위치 : %d, 부호는 %d,",pstr,dec,sign);

	return 0;
}