void judge3() {
	int num;
	printf("请输入年份：\n");
	scanf_s("%d", &num);
	if (0 == num % 4 && 0 != num%100) {
		printf("%d是闰年\n", num);
	}
	else if (0 == num % 400){
		printf("%d是闰年\n", num);
	}
	else
	{
		printf("%d不是闰年\n", num);
	}
	finish();
}