int main(int argc, char* argv[])
{
	LetsStart ();

	if (!FoolProof(argc,argv))
		return 0;

	char *fNameA=argv[1];
	char *DoIt=argv[2];
	char *fNameB=argv[3];
	char *fNameOut=argv[4];
	char *bin=argv[5];
	char *fNameM=argv[6];

	long size=0;
	LongInt a, b;

	char *ReadFlag=0;
	char *WriteFlag=0;
	if(strcmp(bin,"-b")==0)
	{
		ReadFlag = "rb";
		WriteFlag = "bw";
	}
	else
	{
		ReadFlag = "r";
		WriteFlag = "w";
	}
	
	if (!a.Read(ReadFlag, fNameA))
		return 0;
	if (!b.Read(ReadFlag, fNameB))
		return 0;;
	LongInt c;
	if (DoIt[0]=='-')
		c=a-b;
	if (DoIt[0]=='+')
		c=a+b;
	if (DoIt[0]=='*')
		c=a*b;
	if (DoIt[0]=='/')
		c=a/b;
	if (DoIt[0]=='%')
		c=a%b;
	if (DoIt[0]=='^')
	{
		LongInt mod;
		if(!mod.Read(ReadFlag, fNameM))
			return 0;
		c=c.Pow(a, b, mod);
	}
	//c.Print();	
	if (!c.WriteFile(WriteFlag, fNameOut))
		return 0;
	return 0;
}