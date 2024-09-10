int main()
{
	int num,i=7;
	char arr[9];
	printf("Enter a number: ");
	scanf_s("%d", &num);
	arr[8] = '\0';
	while (num != 0){
		arr[i] = num % 10+'0';
		i--;
		num = num / 10;
	}
	permutations(arr, i+1, 7);
	_getch();
	return 0;
}