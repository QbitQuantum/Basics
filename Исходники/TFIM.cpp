//get 166 genes information in database
void TFIM::getGeneInformation(FILE *fp)
{
	ifstream data("TFIM");
	//ofstream text("Sequence");
	if(!data)
	{
		getError=1;
	}
	else
		getError=0;
	char ch;
	int i;
	for(i=1;i<aM;i++)
	{
		if(!data.get(ch))
		{
			i=aM;
		}
		while(ch=='#')//filter RegulonDB line
		{
			string noUse;
			getline(data,noUse);
			data.get(ch);
		}
		string line;
		char GN[10];
		getline(data,line);
		for(int h=0;h<10;h++)
			GN[h]=geneName[h];
		char cLine[60];
		for(int H=0;H<60;H++)
			cLine[H]=line[H];
		strlwr(cLine);
		strlwr(GN);
		int haveFound=easyFind(cLine,GN);
		if(haveFound==1)
		{
			char fullLine[10000];
			int h=0;
			while(line[h]!='\0')
			{
				fullLine[h]=line[h];
				h++;
			}
			fullLine[h]='\0';
			const char *delims="	";
			char *p;
			p=strtok(fullLine,delims);
			iD=p;
			p=strtok(NULL,delims);
			p=strtok(NULL,delims);
			leftPosition=p;
			p=strtok(NULL,delims);
			rightPosition=p;
			p=strtok(NULL,delims);
			p=strtok(NULL,delims);
			if(*p!='-')RNA=1;
			else RNA=0;
			p=strtok(NULL,delims);
			p=strtok(NULL,delims);
			p=strtok(NULL,delims);
			p=strtok(NULL,delims);
			geneSequence=p;
			i=aM+1;
			//text.seekp(text.end);
			//text<<geneNumber<<"	"<<geneSequence<<endl;
			fprintf(fp,"%d	%s\n",geneNumber,geneSequence);
		}
		//cout<<i<<endl;
	}
	if(i==aM)
		cout<<"can't find gene sequence"<<endl;
}