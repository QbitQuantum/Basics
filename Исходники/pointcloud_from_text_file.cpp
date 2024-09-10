//---------------------------------------------------------
bool CPointCloud_From_Text_File::On_Execute(void)
{
	//-----------------------------------------------------
	CSG_File	Stream;

	if( !Stream.Open(Parameters("FILE")->asString(), SG_FILE_R, false) )
	{
		Error_Set(_TL("Unable to open input file!"));

		return( false );
	}

	//-----------------------------------------------------
	int	xField	= Parameters("XFIELD")->asInt() - 1;
	int	yField	= Parameters("YFIELD")->asInt() - 1;
	int	zField	= Parameters("ZFIELD")->asInt() - 1;

	char	Separator;

	switch( Parameters("SEPARATOR")->asInt() )
    {
	default:	Separator	= '\t';	break;
    case  1:	Separator	=  ' ';	break;
    case  2:	Separator	=  ',';	break;
    }

    //-----------------------------------------------------
	CSG_String	sLine;
	CSG_Strings	Values;

	if( !Stream.Read_Line(sLine) )
	{
		Error_Set(_TL("Empty file!"));

		return( false );
	}

	if( Parameters("SKIP_HEADER")->asBool() )	// header contains field names
	{
		CSG_String_Tokenizer	tokValues(sLine, Separator);	// read each field name for later use

		while( tokValues.Has_More_Tokens() )
		{
			Values	+= tokValues.Get_Next_Token();
		}
	}
	else
    {
		Stream.Seek_Start();
    }

    //-----------------------------------------------------
    CSG_PointCloud	*pPoints	= SG_Create_PointCloud();
    pPoints->Set_Name(SG_File_Get_Name(Parameters("FILE")->asString(), false));
    Parameters("POINTS")->Set_Value(pPoints);

	CSG_Array_Int	Fields;

    //-----------------------------------------------------
    if( SG_UI_Get_Window_Main() )
    {
		CSG_Parameters	&Fields	= *Parameters("FIELDSPECS")->asParameters();

		int	nFields	= Fields.Get_Count() / 2;

		CSG_String	Names, Types;

		for(int iField=0; iField<nFields; iField++)
		{
			Names	+= CSG_String::Format("%s;", Fields(CSG_String::Format("NAME%03d", iField))->asString());
			Types	+= CSG_String::Format("%d;", Fields(CSG_String::Format("TYPE%03d", iField))->asInt   ());
		}

		Parameters("FIELDNAMES")->Set_Value(Names);
		Parameters("FIELDTYPES")->Set_Value(Types);
	}

	{
		TSG_Data_Type	Type	= SG_DATATYPE_Float;	// default

		CSG_String_Tokenizer	tokFields(Parameters("FIELDS"    )->asString(), ";");
		CSG_String_Tokenizer	tokTypes (Parameters("FIELDTYPES")->asString(), ";");
		CSG_String_Tokenizer	tokNames (Parameters("FIELDNAMES")->asString(), ";");

		while( tokFields.Has_More_Tokens() )
		{
			int	iField;

			if( !tokFields.Get_Next_Token().asInt(iField) || iField < 1 )
			{
				Error_Set(_TL("Error parsing attribute field index"));

				return( false );
			}

			Fields	+= iField - 1;

			CSG_String	Name;

			if( tokNames.Has_More_Tokens() )
			{
				Name	= tokNames.Get_Next_Token(); Name.Trim(true); Name.Trim(false);
			}

			if( Name.is_Empty() )
			{
				if( iField - 1 < Values.Get_Count() )
				{
					Name	= Values[iField - 1];
				}
				else
				{
					Name.Printf("FIELD%02d", iField);
				}
			}

			if( tokTypes.Has_More_Tokens() )
			{
				Get_Data_Type(Type, tokTypes.Get_Next_Token());
			}

			pPoints->Add_Field(Name, Type);
		}
	}

    //-----------------------------------------------------
	Process_Set_Text(_TL("Importing data ..."));

	int		nLines	= 0;
	sLong	Length	= Stream.Length();

	while( Stream.Read_Line(sLine) )
    {
		nLines++;

		if( pPoints->Get_Count() % 10000 == 0 && !Set_Progress((double)Stream.Tell(), (double)Length) )
		{
			return( true );	// user break
		}

	    //-------------------------------------------------
		CSG_String_Tokenizer	tokValues(sLine, Separator);

		Values.Clear();

		while( tokValues.Has_More_Tokens() )	// read every column in this line and fill vector
        {
			Values	+= tokValues.Get_Next_Token();
        }

	    //-------------------------------------------------
		double	x, y, z;

		if( xField >= Values.Get_Count() || !Values[xField].asDouble(x)
		||  yField >= Values.Get_Count() || !Values[yField].asDouble(y)
		||  zField >= Values.Get_Count() || !Values[zField].asDouble(z) )
		{
			Message_Fmt("\n%s: %s [%d]", _TL("Warning"), _TL("Skipping misformatted line"), nLines);

			continue;
		}

        pPoints->Add_Point(x, y, z);

	    //-------------------------------------------------
		for(int iAttribute=0; iAttribute<pPoints->Get_Attribute_Count(); iAttribute++)
		{
			if( Fields[iAttribute] >= Values.Get_Count() )
			{
				pPoints->Set_NoData(3 + iAttribute);
			}
			else switch( pPoints->Get_Attribute_Type(iAttribute) )
			{
			case SG_DATATYPE_String:
				pPoints->Set_Attribute(iAttribute, Values[Fields[iAttribute]]);
				break;

			default:
				{
					double	Value;

					if( Values[Fields[iAttribute]].asDouble(Value) )
					{
						pPoints->Set_Attribute(iAttribute, Value);
					}
					else
					{
						pPoints->Set_NoData(3 + iAttribute);
					}
				}
				break;
			}
		}
    }

    //-----------------------------------------------------
	DataObject_Set_Parameter(pPoints, "DISPLAY_VALUE_AGGREGATE", 3);	// highest z
	DataObject_Set_Parameter(pPoints, "COLORS_TYPE"            , 3);	// graduated colors
	DataObject_Set_Parameter(pPoints, "METRIC_ATTRIB"          , 2);	// z attrib
	DataObject_Set_Parameter(pPoints, "METRIC_ZRANGE", pPoints->Get_Minimum(2), pPoints->Get_Maximum(2));

	DataObject_Update(pPoints);

    //-----------------------------------------------------
	if( nLines > pPoints->Get_Count() )
	{
		Message_Add(" ", true);
		Message_Fmt("%s: %d %s", _TL("Warning"), nLines - pPoints->Get_Count(), _TL("invalid points have been skipped"));
	}

	Message_Add(" ", true);
	Message_Fmt("%d %s", pPoints->Get_Count(), _TL("points have been imported with success"));

	return( true );
}