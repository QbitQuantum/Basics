int AddStuInfoFromFile()
{
	int tmpi;
	char student_number_char[13 + 1];
	char mobile_phone_number_char[11 + 1];	
	char qq_number_char[10 + 1];	
	FILE * pFile = NULL;
	
	pFile = fopen(STU_INFO_FILE, "r");
	if(!pFile)
	{
		printf("读取改进后的同学录系统失败!\n");
		return FAILURE;
	}
	else
		printf("欢迎进入改进后的同学录系统!\n");
		printf("程序员：戴嘉乐\n");
		printf("辅导老师：潘晔\n"); 
	
	memset(StudentNumber,0,8);
	memset(MobilePhoneNumber,0,8);
	memset(QQNumber,0,8);
	memset(Name,0,MAX_STU_COUNT * (10 + 1));
	memset(Email,0,MAX_STU_COUNT * (20 + 1));	
	
	while(!feof(pFile))
	{		
		fscanf(pFile,"%s",student_number_char);
		fscanf(pFile,"\t%s",Name[CurrentStudentCount]);
		fscanf(pFile,"\t%s",mobile_phone_number_char);
		fscanf(pFile,"\t%s",Email[CurrentStudentCount]);
		fscanf(pFile,"\t%s\n",qq_number_char);
		StudentNumber[CurrentStudentCount] = _atoi64(student_number_char);
		MobilePhoneNumber[CurrentStudentCount] = _atoi64(mobile_phone_number_char);		
		QQNumber[CurrentStudentCount] = _atoi64(qq_number_char);		
		CurrentStudentCount++;
	}
	
	fclose(pFile);
	return SUCCESS;
}