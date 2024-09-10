static void LFO_Init(running_machine &machine)
{
    int i,s;
    for(i=0;i<256;++i)
    {
		int a,p;
//      float TL;
		//Saw
		a=255-i;
		if(i<128)
			p=i;
		else
			p=i-256;
		ALFO_SAW[i]=a;
		PLFO_SAW[i]=p;

		//Square
		if(i<128)
		{
			a=255;
			p=127;
		}
		else
		{
			a=0;
			p=-128;
		}
		ALFO_SQR[i]=a;
		PLFO_SQR[i]=p;

		//Tri
		if(i<128)
			a=255-(i*2);
		else
			a=(i*2)-256;
		if(i<64)
			p=i*2;
		else if(i<128)
			p=255-i*2;
		else if(i<192)
			p=256-i*2;
		else
			p=i*2-511;
		ALFO_TRI[i]=a;
		PLFO_TRI[i]=p;

		//noise
		//a=lfo_noise[i];
		a=machine.rand()&0xff;
		p=128-a;
		ALFO_NOI[i]=a;
		PLFO_NOI[i]=p;
    }

	for(s=0;s<8;++s)
	{
		float limit=PSCALE[s];
		for(i=-128;i<128;++i)
		{
			PSCALES[s][i+128]=CENTS(((limit*(float) i)/128.0));
		}
		limit=-ASCALE[s];
		for(i=0;i<256;++i)
		{
			ASCALES[s][i]=DB(((limit*(float) i)/256.0));
		}
	}
}