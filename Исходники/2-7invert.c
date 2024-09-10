void main()
{
	int num;
	scanf("%d", &num);
	num = BinToDec(num);
	DecToBin(num);
	printf("\n inverted bits = ");
	DecToBin(invert(num, 4, 3));
	printf("\n\n0^0 = %d\n", 0^0);
	printf("\n\n1^1 = %d\n", 1^1);
	printf("\n\n1^0 = %d\n", 1^0);
	printf("\n\n0^1 = %d\n", 0^1);
}