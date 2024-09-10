//---------------------------------------------------------------------------
__TROPICALL BTP_Tempo::BTP_Tempo(char *tnome,bool ativarmanual) throw(BTP_Excecao*):BTP_Objeto(tnome)
{
	   BTP_Tempo::numtempo++;

	   char a[50];
	   itoa(BTP_Tempo::numtempo,a,10);
	   strcat(tnome,a);
	   manual=ativarmanual;
	   htimer = CreateWaitableTimerA(NULL, ativarmanual,tnome);
	   ativo=false;
	   intervalo=0;
	   //MessageBoxA(0,tnome,"nome timer",0);
	
}