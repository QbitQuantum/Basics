CLongInt _CLongInt__loadstr(char * arg_0)
{
	char * local_00;
	int local_01;
	int local_02;
	int local_03;
	char local_04[100];
	CLongInt local_05;
	local_05.m_intarray[0]=0;
	local_05.m_int2=0;
	local_02=0;
	for ( ; !(*arg_0==0)&&(int)*arg_0==32; arg_0++) {
	}
	local_03=strlen(arg_0);
	if (local_03==0) {
		local_05.m_intarray[1]=0;
		local_05.m_int1=0;
		local_05.m_int2=0;
		return local_05;
	}
	if ((int)*arg_0==45) {
		local_05.m_int2=-1;
		local_02=local_02+1;
	}
	if ((int)*arg_0==43) {
		local_02=local_02+1;
	}
	strcpy(local_04,arg_0+local_02);
	local_00=local_04;
	local_00=strrev(local_00);
	local_03=local_03-local_02;
	for (local_01=0; local_01<local_03; local_01++) {
		if (isdigit((int)*(local_00+local_01))==0) break;
		*(local_00+local_01)-='0';
	}
	local_03=local_01;
	local_02=1;
	local_01=0;
	while (local_01<local_03) {
		local_05.m_intarray[local_02]=(int)*(local_00+local_01)+(int)*((local_00+1)+local_01)*10;
		local_02=local_02+1;
		local_01=local_01+2;
	}
	local_05.m_int1=local_02-1;
	return local_05;
}