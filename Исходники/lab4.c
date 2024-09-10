int main(void) {
	//Problem 1
	printf("Problem 1\n");

	int array[20];

	fillInteger(array, 20, -20, 20);
	int n = 10;
	int i;
	for(i = 0; i < 20; i++) {
		printf("%d	", array[i]);
		if((i+1)%n==0) {
			printf("\n");
		}
	}

	findConsecutive(array, 20);

	//Problem 2
	printf("\nProblem 2\n");

	char charArr[50];

	fillCharacter(charArr, 50, 'a', 'z');
	int a;
	for(a = 0; a < 50; a++) {
		printf("%c ", charArr[a]);
	}

	findTriples(charArr, 50);

	//Problem 3
	printf("\n\nProblem 3\n");

	float floatArr[10];

	fillFloat(floatArr, 10, 1.0, 50.0);
	int b;
	for(b = 0; b < 10; b++) {
		printf("%lf  ", floatArr[b]);
	}
	
	float mean = floatMean(floatArr, 10);
	printf("\nMean of the array is %lf\n", mean);

	float min = floatMin(floatArr, 10);
	printf("Min of the array is %lf\n", min);

	float max = floatMax(floatArr, 10);
	printf("Max of the array is %lf\n", max);

}