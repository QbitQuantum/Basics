//---------------------------------------------------------
bool CPointcloud_To_Text_File::On_Execute(void)
{
	CSG_PointCloud			*pPoints;
	CSG_String				fileName;
	CSG_File				*pTabStream = NULL;
	bool					bWriteHeader;
	CSG_String				fieldSep;

	CSG_Parameters			P;
	CSG_Parameter			*pNode;
	CSG_String				s;
	std::vector<int>		vCol, vPrecision;


	//-----------------------------------------------------
	pPoints			= Parameters("POINTS")		->asPointCloud();
	fileName		= Parameters("FILE")		->asString();
	bWriteHeader	= Parameters("WRITE_HEADER")->asBool();


	switch (Parameters("FIELDSEP")->asInt())
    {
	default:
    case 0:		fieldSep = "\t";	break;
    case 1:		fieldSep = " ";		break;
    case 2:		fieldSep = ",";		break;
    }


	if( fileName.Length() == 0 )
	{
		SG_UI_Msg_Add_Error(_TL("Please provide an output file name!"));
		return( false );
	}


	if (SG_UI_Get_Window_Main())
	{
		P.Set_Name(_TL("Check the fields to export"));

		for(int iField=0; iField<pPoints->Get_Field_Count(); iField++)
		{
			s.Printf(SG_T("NODE_%03d") , iField + 1);
			pNode	= P.Add_Node(NULL, s, CSG_String::Format(_TL("%d. %s"), iField + 1, _TL("Field")), _TL(""));

			s.Printf(SG_T("FIELD_%03d"), iField);
			P.Add_Value(pNode, s, CSG_String::Format(SG_T("%s"), pPoints->Get_Field_Name(iField)), _TL(""), PARAMETER_TYPE_Bool, false);

			s.Printf(SG_T("PRECISION_%03d"), iField);
			P.Add_Value(pNode, s, _TL("Decimal Precision"), _TL(""), PARAMETER_TYPE_Int, 2.0, 0.0, true);
		}


		//-----------------------------------------------------
		if( Dlg_Parameters(&P, _TL("Field Properties")) )
		{
			vCol.clear();
			vPrecision.clear();

			for(int iField=0; iField<pPoints->Get_Field_Count(); iField++)
			{
				if( P(CSG_String::Format(SG_T("FIELD_%03d" ), iField).c_str())->asBool() )
				{
					vCol.push_back(iField);
					vPrecision.push_back(P(CSG_String::Format(SG_T("PRECISION_%03d" ), iField).c_str())->asInt());
				}
			}
		}
		else
			return( false );
	}
	else // CMD
	{
		CSG_String		sFields, sPrecision;
		CSG_String		token;
		int				iValue;


		sFields		= Parameters("FIELDS")->asString();
		sPrecision	= Parameters("PRECISIONS")->asString();

		CSG_String_Tokenizer   tkz_fields(sFields, ";", SG_TOKEN_STRTOK);

		while( tkz_fields.Has_More_Tokens() )
		{
			token	= tkz_fields.Get_Next_Token();

			if( token.Length() == 0 )
				break;

			if( !token.asInt(iValue) )
			{
				SG_UI_Msg_Add_Error(_TL("Error parsing attribute fields: can't convert to number"));
				return( false );
			}

			iValue	-= 1;

			if( iValue < 0 || iValue > pPoints->Get_Field_Count() - 1 )
			{
				SG_UI_Msg_Add_Error(_TL("Error parsing attribute fields: field index out of range"));
				return( false );
			}
			else
				vCol.push_back(iValue);
		}

		CSG_String_Tokenizer   tkz_precisons(sPrecision.c_str(), ";", SG_TOKEN_STRTOK);

		while( tkz_precisons.Has_More_Tokens() )
		{
			token	= tkz_precisons.Get_Next_Token();

			if( token.Length() == 0 )
				break;

			if( !token.asInt(iValue) )
			{
				SG_UI_Msg_Add_Error(_TL("Error parsing attribute fields: can't convert to number"));
				return( false );
			}

			vPrecision.push_back(iValue);
		}
	}


	if( vCol.size() == 0 )
	{
		SG_UI_Msg_Add_Error(_TL("Please provide at least one column to export!"));
		return( false );
	}

	if( vCol.size() != vPrecision.size() )
	{
		SG_UI_Msg_Add_Error(_TL("Number of fields and precisions must be equal!"));
		return( false );
	}

	//-----------------------------------------------------
	pTabStream = new CSG_File();

	if( !pTabStream->Open(fileName, SG_FILE_W, false) )
	{
		SG_UI_Msg_Add_Error(CSG_String::Format(_TL("Unable to open output file %s!"), fileName.c_str()));
		delete (pTabStream);
		return (false);
	}


	if( bWriteHeader )
	{
	    CSG_String  sHeader;

		for(size_t i=0; i<vCol.size(); i++)
		{
		    sHeader += CSG_String::Format(SG_T("%s"), pPoints->Get_Field_Name(vCol.at(i)));

		    if( i < vCol.size()-1 )
                sHeader += fieldSep.c_str();
		}

		sHeader += SG_T("\n");

		pTabStream->Write(sHeader);
	}


	for(int iPoint=0; iPoint<pPoints->Get_Count() && Set_Progress(iPoint, pPoints->Get_Count()); iPoint++)
	{
		CSG_String	sLine;

		for(size_t i=0; i<vCol.size(); i++)
		{
			switch (pPoints->Get_Field_Type(vCol.at(i)))
			{
			case SG_DATATYPE_Double:
			case SG_DATATYPE_Float:
				sLine += SG_Get_String(pPoints->Get_Value(iPoint, vCol.at(i)), vPrecision.at(i), false);
				break;
			default:
				sLine += CSG_String::Format(SG_T("%d"), (int)pPoints->Get_Value(iPoint, vCol.at(i)));
				break;
			}

            if( i < vCol.size()-1 )
                sLine += fieldSep.c_str();
		}

		sLine += SG_T("\n");

		pTabStream->Write(sLine);
	}


	pTabStream->Close();
	delete (pTabStream);

	return( true );
}