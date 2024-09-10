char* itoa(int v)
{
	char result[100];
	int idx = -1;
	while(true)
	{
		if(v==0)
			break;
		
		result[++idx]=(v%10)+'0';
		v/=10;
	}
	result[++idx]='\0'; 
	strrev(result);
	return result;
} 