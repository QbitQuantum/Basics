//---------------------------------------------------------
bool CPolygon_Intersection::On_Execute(void)
{
	CSG_String	sName;

	m_pShapes_A		= Parameters("SHAPES_A")	->asShapes();
	m_pShapes_B		= Parameters("SHAPES_B")	->asShapes();
	m_pShapes_AB	= Parameters("SHAPES_AB")	->asShapes();
	m_bSplitParts	= Parameters("SPLITPARTS")	->asBool();
	m_iField_A		= Parameters("FIELD_A")		->asInt();	if( m_iField_A >= m_pShapes_A->Get_Field_Count() )	{	m_iField_A	= -1;	}
	m_iField_B		= Parameters("FIELD_B")		->asInt();	if( m_iField_B >= m_pShapes_B->Get_Field_Count() )	{	m_iField_B	= -1;	}

	if(	m_pShapes_A->Get_Type() == SHAPE_TYPE_Polygon && m_pShapes_A->is_Valid()
	&&	m_pShapes_B->Get_Type() == SHAPE_TYPE_Polygon && m_pShapes_B->is_Valid() )
	{
		m_pShapes_AB->Create(SHAPE_TYPE_Polygon);
		m_pShapes_AB->Add_Field("ID"	, SG_DATATYPE_Int);
		m_pShapes_AB->Add_Field("ID_A"	, SG_DATATYPE_Int);
		m_pShapes_AB->Add_Field("ID_B"	, SG_DATATYPE_Int);
		m_pShapes_AB->Add_Field("ID_AB"	, SG_DATATYPE_Int);

		if( m_iField_A >= 0 )
		{
			m_pShapes_AB->Add_Field(m_pShapes_A->Get_Field_Name(m_iField_A), m_pShapes_A->Get_Field_Type(m_iField_A));
		}

		if( m_iField_B >= 0 )
		{
			m_pShapes_AB->Add_Field(m_pShapes_B->Get_Field_Name(m_iField_B), m_pShapes_B->Get_Field_Type(m_iField_B));
		}

		//-------------------------------------------------
		switch( Parameters("METHOD")->asInt() )
		{
		//-------------------------------------------------
		case 0:	// Complete Intersection...
			sName.Printf(SG_T("%s [%s]-[%s]"), _TL("Intersection"), m_pShapes_A->Get_Name(), m_pShapes_B->Get_Name());

			Get_Intersection(m_pShapes_A, m_pShapes_B, MODE_FIRST);
			Get_Difference	(m_pShapes_A, m_pShapes_B, MODE_FIRST);
			Get_Difference	(m_pShapes_B, m_pShapes_A, MODE_SECOND);

			break;

		//-------------------------------------------------
		case 1:	// Intersection...
			sName.Printf(SG_T("%s [%s]-[%s]"), _TL("Intersection"), m_pShapes_A->Get_Name(), m_pShapes_B->Get_Name());

			Get_Intersection(m_pShapes_A, m_pShapes_B, MODE_FIRST);

			break;

		//-------------------------------------------------
		case 2:						// Difference A - B...
			sName.Printf(SG_T("%s [%s]-[%s]"), _TL("Difference"), m_pShapes_A->Get_Name(), m_pShapes_B->Get_Name());

			Get_Difference	(m_pShapes_A, m_pShapes_B, MODE_FIRST);

			break;

		//-------------------------------------------------
		case 3:						// Difference B - A...
			sName.Printf(SG_T("%s [%s]-[%s]"), _TL("Difference"), m_pShapes_B->Get_Name(), m_pShapes_A->Get_Name());

			Get_Difference	(m_pShapes_B, m_pShapes_A, MODE_SECOND);

			break;
		}

		//-------------------------------------------------
		m_pShapes_AB->Set_Name(sName);

		return( m_pShapes_AB->Get_Count() > 0 );
	}

	return( false );
}/**/