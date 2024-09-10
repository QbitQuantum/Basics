//---------------------------------------------------------------------------
void __fastcall TDMAvtoriz::DataModuleCreate(TObject *Sender)
{
	TIniFile *kkmp = new TIniFile(GetCurrentDir()+"\\config.ini");
	AnsiString host = kkmp->ReadString("connect_to_mysql","HostName","");
	AnsiString db = kkmp->ReadString("connect_to_mysql","Database","");
	AnsiString user = kkmp->ReadString("connect_to_mysql","UserName","");
	AnsiString pass = kkmp->ReadString("connect_to_mysql","Password","");
	AnsiString charset = kkmp->ReadString("connect_to_mysql","ServerCharSet","utf8");

	SQLConnectKKMP->Connected = false;
	SQLConnectKKMP->Params->Values["HostName"]= host;
	SQLConnectKKMP->Params->Values["DataBase"]= db;
	SQLConnectKKMP->Params->Values["UserName"]= user;
	SQLConnectKKMP->Params->Values["Password"]= pass;
	SQLConnectKKMP->Params->Values["ServerCharSet"]= charset;
	SQLConnectKKMP->Connected = true;

	kkmp->Free();
}