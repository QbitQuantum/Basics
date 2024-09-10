//---------------------------------------------------------
bool CShapes2Grid::On_Execute(void)
{
	//-----------------------------------------------------
	m_pShapes			= Parameters("INPUT"    )->asShapes();

	m_Method_Lines		= Parameters("LINE_TYPE")->asInt();
	m_Method_Polygon	= Parameters("POLY_TYPE")->asInt();
	m_Method_Multi		= Parameters("MULTIPLE" )->asInt();

	if( m_pShapes->Get_Type() == SHAPE_TYPE_Polygon && m_Method_Polygon == 1 )	// all cells intersected have to be marked
	{
		m_Method_Lines	= 1;	// thick, each cell crossed by polygon boundary will be marked additionally
	}

	//-----------------------------------------------------
	int		iField;

	switch( Parameters("OUTPUT")->asInt() )
	{
	case 0:	iField	= -1;	break;
	case 1:	iField	= -2;	break;
	case 2:
		if( (iField = Parameters("FIELD")->asInt()) < 0 || !SG_Data_Type_is_Numeric(m_pShapes->Get_Field_Type(iField)) )
		{
			iField		= -2;

			Message_Add(_TL("WARNING: selected attribute is not numeric; generating unique identifiers instead."));
		}
		break;
	}

	//-----------------------------------------------------
	m_Grid_Target.Cmd_Update(m_pShapes);	// if called from saga_cmd

	if( (m_pGrid = m_Grid_Target.Get_Grid("GRID", Get_Grid_Type(Parameters("GRID_TYPE")->asInt()))) == NULL )
	{
		return( false );
	}

	if( iField < 0 )
	{
		m_pGrid->Set_NoData_Value(0.0);
	}

	m_pGrid->Set_Name(CSG_String::Format("%s [%s]", m_pShapes->Get_Name(), iField < 0 ? _TL("ID") : m_pShapes->Get_Field_Name(iField)));
	m_pGrid->Assign_NoData();

	//-------------------------------------------------
	m_pCount	= m_Grid_Target.Get_Grid("COUNT", m_pShapes->Get_Count() < 256 ? SG_DATATYPE_Byte : SG_DATATYPE_Word);

	if( m_pCount == NULL )
	{
		m_Count.Create(m_pGrid->Get_System(), SG_DATATYPE_Word);

		m_pCount	= &m_Count;
	}

	m_pCount->Set_Name(CSG_String::Format("%s [%s]", m_pShapes->Get_Name(), _TL("Count")));
	m_pCount->Set_NoData_Value(0.0);
	m_pCount->Assign(0.0);

	//-----------------------------------------------------
	for(int iShape=0; iShape<m_pShapes->Get_Count() && Set_Progress(iShape, m_pShapes->Get_Count()); iShape++)
	{
		CSG_Shape	*pShape	= m_pShapes->Get_Shape(iShape);

		if( m_pShapes->Get_Selection_Count() <= 0 || pShape->is_Selected() )
		{
			if( iField < 0 || !pShape->is_NoData(iField) )
			{
				m_Value	= iField >= 0 ? pShape->asDouble(iField) : iField == -2 ? iShape + 1 : 1;

				if( pShape->Intersects(m_pGrid->Get_Extent()) )
				{
					switch( m_pShapes->Get_Type() )
					{
					case SHAPE_TYPE_Point:	case SHAPE_TYPE_Points:
						Set_Points	(pShape);
						break;

					case SHAPE_TYPE_Line:
						Set_Line	(pShape);
						break;

					case SHAPE_TYPE_Polygon:
						Set_Polygon	(pShape);

						if( m_Method_Polygon == 1 )	// all cells intersected have to be marked
						{
							Set_Line(pShape);	// thick, each cell crossed by polygon boundary will be marked additionally
						}
						break;
					}
				}
			}
		}
	}

	//-----------------------------------------------------
	if( m_Method_Multi == 4 )	// mean
	{
		for(int y=0; y<m_pGrid->Get_NY() && Set_Progress(y, m_pGrid->Get_NY()); y++)
		{
			for(int x=0; x<m_pGrid->Get_NX(); x++)
			{
				if( m_pCount->asInt(x, y) > 1 )
				{
					m_pGrid->Mul_Value(x, y, 1.0 / m_pCount->asDouble(x, y));
				}
			}
		}
	}

	//-----------------------------------------------------
	m_Count.Destroy();

	return( true );
}