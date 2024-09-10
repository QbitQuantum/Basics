void CGate::Load(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int Token;
	int number;
	
	WzMemScript.SetBuffer(Buffer, iSize);
	this->Init();

	while ( true )
	{
		Token=WzMemScript.GetToken();
		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{

			number=WzMemScript.GetNumber();
			this->m_This[number]=number;

			Token=WzMemScript.GetToken();
			this->m_Flag[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_MapNumber[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_Sx[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_Sy[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_Ex[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_Ey[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_TargetGate[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_Dir[number]=WzMemScript.GetNumber();

			Token=WzMemScript.GetToken();
			this->m_Level[number]=WzMemScript.GetNumber();
		}
	}

	LogAdd("Gate information data load complete.");
}