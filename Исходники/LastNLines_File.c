int main(){
	FILE *fp;
	fp = NULL;
	int count = 0, i;
	char line[100];
	int n;
	char lines[100][150];
	fp = fopen("Readme.txt", "r");
	if (fp != NULL){
		printf("Enter no. of line to be printed\n");
		scanf("%d", &n);
		while (fgets(line, 150, fp) != NULL){
			strCpy(lines[count],&line);
			count++;
		}
		fclose(fp);
		for (i = count - n ; i < count; i++){
			printf("%s", lines[i]);
		}
	}

	getchar();
}