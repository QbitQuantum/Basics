void dumpprint(ProxyStream& os, __int64 x, int Scale, const char*xText)
{
	char Text[100];

	_ltoa_s(int(x),Text + 1,99,10);

	int Dot = 1;
	for(Dot=1; Text[Dot]; Dot++);
	Dot -= Scale;
	Dot--;
	for(int i=0; i < Dot; i++)
		Text[i] = Text[i+1];
	if(Scale > 0) Text[Dot] = '.';	
	else Text[Dot] = 0;
	dumpprint(os,Text);
	dumpprint(os,xText);
};