void formatEachField(My402SortElem *currentElem, My402Output *pOutput, long long *pBalance){

	//printf("\nPrint begins...");	
	int sign = 1;
	int i=0;
	int j=0;
	int count = 0;
	//store the balance that is printed
	char printDesc[25] = "\0"; //+1 for terminating char
	char printDate[16] = "\0"; //+1 for terminating char
	char temp[15] = {'\0'};
	char printAmount[15] = "\0"; //+1 for termiating char
	char printBalance[15] = "\0"; //+1 for terminating char	
	char *cTime = (char *)malloc(26*sizeof(char));
	memset(cTime, '\0', 26*sizeof(char));
	//FIXME: what if sizeof(unsigned int) = 2 bytes?	
	long long currentAmount = currentElem->transAmount; 
	//Porcess Amount
	if('-' == currentElem->transType){
		sign = -1;	
	}
	//Process Date
	cTime = ctime(&currentElem->transTime);
	while(cTime[i] != '\n'){
		
		if(! (i >= 10 && i<=18) ){
			printDate[j] = cTime[i];
			j++;
		}
		i++;
	}	
	printDate[15] = '\0';
	//printf("\n%s ", printDate);
	pOutput->printDate = printDate;
	//Porcess Description
	//printf("%s ", currentElem->transDesc);
	strncpy(printDesc, currentElem->transDesc,24);	
	//printf("\nstrlen-1 = %d",i);
	i=24;	
	while(printDesc[i] == '\0' && i>0){ //although not expecting i=0
		printDesc[i] = ' ';
		i--;	
	}	
	printDesc[24] = '\0';
	//printf("\nDesc%s.....",printDesc);	
	pOutput->printDesc = printDesc;	
	strncpy(printAmount,toCurrency((long long)currentElem->transAmount),14);
	i=0;
	count = 14-strlen(printAmount);
	while(i<count){ //although not expecting i=0
		temp[i] = ' ';
		i++;	
	}
	for(j=0;printAmount[j] != '\0'; j++,i++){
		//printf("\ninside amoun condition\n");	
		temp[i] = printAmount[j];
	}
	temp[14] = '\0';
	strncpy(printAmount,temp,14);
	printAmount[14] = '\0';
	if(sign == -1){
		strncpy(printAmount, representNegatives(printAmount),14);
	}
	printAmount[14] = '\0';
	pOutput->printAmount = printAmount;
	
	//Process Balance
	*pBalance = sign*currentAmount + *pBalance;
	strncpy(printBalance,toCurrency(*pBalance),14);
	//FIXME: add leading spaces	
	i=0;
	j=0;
	count = 14-strlen(printBalance);
	while(i<count){ //although not expecting i=0
		//printf("\ninside amoun condition\n");	
		temp[i] = ' ';
		i++;	
	}
	j=0;
	while(printBalance[j] != '\0'){
		temp[i++] = printBalance[j++];
	}
	temp[14] = '\0';	
	//printf("%s ", printBalance);
	strncpy(printBalance, temp, 14);
	printBalance[14] = '\0';	
	if(sign == -1){
		strncpy(printBalance, representNegatives(printBalance),14);
	}
	printBalance[14] = '\0';	
	pOutput->printBalance = printBalance;
	

}