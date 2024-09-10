int CMoveCommand::Load(char* Buffer, int iSize)
{
	this->Init();
	CWzMemScript WzMemScript;
	int Token;
	int counter;
	
	WzMemScript.SetBuffer(Buffer, iSize);

	counter=0;

	while ( true )
	{
		Token=WzMemScript.GetToken();

		if ( Token == 2)
		{
			break;
		}
		
		
		if ( Token == 1)
		{
			this->m_MoveCommandData[counter].Index = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			strcpy(this->m_MoveCommandData[counter].Name, WzMemScript.GetString());

			Token = WzMemScript.GetToken();
			strcpy(this->m_MoveCommandData[counter].EngName, WzMemScript.GetString());

			Token = WzMemScript.GetToken();
			this->m_MoveCommandData[counter].NeedZen = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			this->m_MoveCommandData[counter].NeedLevel = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			this->m_MoveCommandData[counter].GateNumber = WzMemScript.GetNumber();

			counter++;
		}
		else
		{
			this->Init();
			MsgBox("MoveCommand script load fail");
			return FALSE;
		}
	}
	return TRUE;
}