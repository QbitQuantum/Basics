void CMonsterSetBase::LoadSetBase(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int Token;
	int rcount;
	int copycount;
	BYTE Sdir;

	WzMemScript.SetBuffer(Buffer, iSize);

	this->m_Count = 0;

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
			break;

		if ( Token == 1 )
		{
			int Type = (int)WzMemScript.GetNumber();
			while ( true )
			{
				Token = WzMemScript.GetToken();
				if ( strcmp("end", WzMemScript.GetString()) == 0 )
					break;
				
				this->m_Mp[this->m_Count].m_Type = (WORD)WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();	this->m_Mp[this->m_Count].m_MapNumber = (BYTE)WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();	this->m_Mp[this->m_Count].m_Dis = (BYTE)WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();	this->m_Mp[this->m_Count].m_X = (BYTE)WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();	this->m_Mp[this->m_Count].m_Y = (BYTE)WzMemScript.GetNumber();

				this->m_Mp[this->m_Count].m_ArrangeType = Type;


				if ( Type == 1 || Type == 3 )
				{
					Token = WzMemScript.GetToken();	this->m_Mp[this->m_Count].m_W = (BYTE)WzMemScript.GetNumber();
					Token = WzMemScript.GetToken();	this->m_Mp[this->m_Count].m_H = (BYTE)WzMemScript.GetNumber();
				}
				else if ( Type == 2 )
				{
					this->m_Mp[this->m_Count].m_W = 0;
					this->m_Mp[this->m_Count].m_H = 0;

					 int w = this->m_Mp[this->m_Count].m_X - 3;
					 int h = this->m_Mp[this->m_Count].m_Y - 3;

					w += Random(0,6);
					h += Random(0,6);

					this->m_Mp[this->m_Count].m_X = w;
					this->m_Mp[this->m_Count].m_Y = h;
				}
				else if ( Type == 4 )
				{
					this->m_Mp[this->m_Count].m_W = 0;
					this->m_Mp[this->m_Count].m_H = 0;
				}
				else
				{
					this->m_Mp[this->m_Count].m_W = 0;
					this->m_Mp[this->m_Count].m_H = 0;
				}

				Token = WzMemScript.GetToken();	
				this->m_Mp[this->m_Count].m_Dir = (BYTE)WzMemScript.GetNumber();
				Sdir = this->m_Mp[this->m_Count].m_Dir;

				if ( this->m_Mp[this->m_Count].m_Dir == (BYTE)-1 )
				{
					this->m_Mp[this->m_Count].m_Dir = Random(0,7);
				}

				if ( Type == 1 || Type == 3 )
				{
					BYTE w = this->m_Mp[this->m_Count].m_X;
					BYTE h = this->m_Mp[this->m_Count].m_Y;
					Token = WzMemScript.GetToken();
					rcount = (int)WzMemScript.GetNumber();
					copycount = this->m_Count;

					if ( rcount > 1 )
					{
						for ( int k = 0; k<rcount-1 ; k++ )
						{
							if ( g_MapServerManager.CheckMapCanMove(this->m_Mp[copycount].m_MapNumber) == FALSE )
								break;
						
							this->m_Count++;
							if ( this->m_Count > OBJ_MAXMONSTER-1 )
							{
								MsgBox("Monster attribute max over %s %d", __FILE__, __LINE__);
								return;
							}

							this->m_Mp[this->m_Count].m_Dis = this->m_Mp[copycount].m_Dis;
							this->m_Mp[this->m_Count].m_Type = this->m_Mp[copycount].m_Type;
							this->m_Mp[this->m_Count].m_MapNumber = this->m_Mp[copycount].m_MapNumber;
							this->m_Mp[this->m_Count].m_W = this->m_Mp[copycount].m_W;
							this->m_Mp[this->m_Count].m_H = this->m_Mp[copycount].m_H;
							this->m_Mp[this->m_Count].m_X = this->m_Mp[copycount].m_X;
							this->m_Mp[this->m_Count].m_Y = this->m_Mp[copycount].m_Y;
							this->m_Mp[this->m_Count].m_ArrangeType = this->m_Mp[copycount].m_ArrangeType;

							if ( Sdir == (BYTE)-1 )
								this->m_Mp[this->m_Count].m_Dir = Random(0,7);
							else
								this->m_Mp[this->m_Count].m_Dir = this->m_Mp[copycount].m_Dir;
						}
					}
				}

				if ( g_MapServerManager.CheckMapCanMove(this->m_Mp[this->m_Count].m_MapNumber) == FALSE )
					continue;

				this->m_Count++;
				if ( this->m_Count > OBJ_MAXMONSTER-1 )
				{
					MsgBox("Monster attribute max over %d (%s %d)", this->m_Count, __FILE__, __LINE__);
					//fclose(SMDFile);
					return;
				}
			}
		}
	}

	//fclose(SMDFile);
}