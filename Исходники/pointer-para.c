int main(void)
{
	double pi = 3.1415;
	int int_part;
	double frac_part;
	int num;
	int *p = 0x8048000;

	printf("*p = %d\n", *p);
	printf("input a number:\n");
	scanf("%d", 0x8048000);
	printf("*p = %d\n", *p);
	return 0;

	printf("&int_part = %p\n", &int_part);

	decompose(pi, &int_part, &frac_part);

	printf("int_part = %d\n", int_part);
	printf("frac_part = %f\n", frac_part);

	printf("&int_part = %p\n", &int_part);

	return 0;
}