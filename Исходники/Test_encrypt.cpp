void Test_encrypt::matrixSize1()
{
	input=fopen("test.txt","w+");
	char string[50]="E";
	fwrite((void*)string,1,strlen(string),input);
	fclose(input);
	

	input=fopen("test.txt","w+");
	output=fopen("result.txt","w+");
	int vector[1]={0};
	encrypt(1,1,vector);
	fclose(output);
	fclose(input);

	output=fopen("result.txt","w+");
	fread((void*)string,1,100,output);
	CFIXCC_ASSERT_EQUALS(string,"E");
	fclose(output);
}