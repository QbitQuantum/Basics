bool Cihacres_elev::_CreateDialog2()
{
	int		i;

	//std::ofstream f("_out_elev.txt");

	CSG_Parameters	P;  // used to add Parameters in the second dialog
	CSG_Parameter	*pNode, *pNode1;
	CSG_String		s;
	CSG_String		tmpNode, tmpName;

	P.Set_Name(_TL("IHACRES Elevation Bands (Dialog 2)"));
	// Input file ----------------------------------------------
	pNode = P.Add_Table(
		NULL	, "TABLE"	, _TL("IHACRES Input Table"),
		_TL(""),
		PARAMETER_INPUT
	);

	P.Add_Table_Field(
		pNode	, "DATE_Field"	, _TL("Date Column"),
		SG_T("Select the column containing the Date")
	);

	P.Add_Table_Field(
		pNode	, "DISCHARGE_Field"	, _TL("Streamflow (obs.) Column"),
		SG_T("Select the column containing the observed streamflow time series)")
	);
	
	for (i = 0; i < m_nElevBands; i++)
	{
		tmpNode = convert_sl::Int2String(i+1).c_str();
		//s.Printf(tmpNode.c_str(), i);
		//pNode1 = P.Add_Node(NULL,s,SG_T("Elevation Band Input",_TL(""));

		tmpName = SG_T("PCP Column: Elevation Band: ");
		tmpName+=tmpNode;
		P.Add_Table_Field(
			pNode	, tmpName.c_str(), tmpName.c_str(),
			SG_T("Select Precipitation Column")
		);

		tmpName = SG_T("TMP Column: Elevation Band: ");
		tmpName+=tmpNode;
		P.Add_Table_Field(
			pNode	, tmpName.c_str()	, tmpName.c_str(),
			SG_T("Select Temperature Column")
		);
	}
	// Input file ----------------------------------------------

	for (i = 0; i < m_nElevBands; i++)
	{
		tmpNode = SG_T("Node");
		tmpNode+=convert_sl::Int2String(i+100).c_str();
		tmpName = SG_T("Elevation Band ");
		tmpName+=convert_sl::Int2String(i+1).c_str();

		s.Printf(tmpNode.c_str(), i+100);
		pNode = P.Add_Node(NULL,s,tmpName.c_str(),_TL(""));
		
		tmpName = SG_T("Area [km2] Elev(");
		tmpName += tmpNode;
		tmpName += SG_T(")");
		P.Add_Value(
			pNode,	tmpName, _TL("Area [km2]"),
			_TL(""),
			PARAMETER_TYPE_Double
		);

		tmpName = SG_T("Mean Elevation [m.a.s.l] Elev(");
		tmpName += tmpNode;
		tmpName += _TL(")");
		P.Add_Value(
			pNode,	tmpName, _TL("Mean Elevation [m.a.s.l]"),
			_TL(""),
			PARAMETER_TYPE_Double
		);
	//}

		// Parameters of non-linear module -------------------------
		tmpNode = SG_T("Node");
		tmpNode+=convert_sl::Int2String(i+150).c_str();
		s.Printf(tmpNode.c_str(), i+150);
		pNode1 = P.Add_Node(pNode,s,SG_T("Non-Linear Module"),_TL(""));

		tmpName = SG_T("TwFAC(");
		tmpName += tmpNode;
		tmpName += _TL(")");
		P.Add_Value(
			pNode1,	tmpName,	_TL("Wetness decline time constant (Tw)"),
			_TW("Tw is approximately the time constant, or inversely, "
			"the rate at which the catchment wetness declines in the absence of rainfall"),
			PARAMETER_TYPE_Double,
			1.0, 0.01, true, 150.0, true
		);

		tmpName = SG_T("TFAC(");
		tmpName += tmpNode;
		tmpName += _TL(")");
		P.Add_Value(
			pNode1, tmpName, SG_T("Temperature Modulation Factor (f)"),
			_TL("Temperature Modulation Factor f"),
			PARAMETER_TYPE_Double,
			1.0, 0.0001, true, 10.0, true
		);

		tmpName = SG_T("CFAC(");
		tmpName += tmpNode;
		tmpName += _TL(")");
		P.Add_Value(
			pNode1,tmpName,	_TL("Parameter (c)"),
			_TL("Parameter (c) to fit streamflow volume"),
			PARAMETER_TYPE_Double,
			0.001, 0.0, true, 1.0, true
		);

		switch(m_IHAC_version)
		{
		case 0: // Jakeman & Hornberger (1993)
			break;
		case 1: // Croke et al. (2005)
			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+200).c_str();
			s.Printf(tmpNode.c_str(), i+200);
			pNode1 = P.Add_Node(pNode,s,SG_T("Soil Moisture Power Eq."),_TL(""));

			tmpName = SG_T("LFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,	tmpName,	_TL("Parameter (l)"),
				_TL("Soil moisture index threshold"),
				PARAMETER_TYPE_Double,
				0.0, 0.0, true, 5.0, true
			);

			tmpName = SG_T("PFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,	tmpName,	_TL("Parameter (p)"),
				_TL("non-linear response term"),
				PARAMETER_TYPE_Double,
				0.0, 0.0, true, 5.0, true
			);
				break;
		}
		// Parameters of non-linear module -------------------------

		// Parameters of linear module -----------------------------
		switch(m_StorConf)
		{
		case 0: // single storage
			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+250).c_str();
			s.Printf(tmpNode.c_str(), i+250);
			pNode1 = P.Add_Node(pNode,s,SG_T("Linear Module"),_TL(""));

			tmpName = SG_T("AFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,	tmpName,	_TL("(a)"),
				_TL(""),
				PARAMETER_TYPE_Double,
				-0.8, -0.99, true, -0.01, true
			);

			tmpName = SG_T("BFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,	tmpName,	_TL("(b)"),
				_TL(""),
				PARAMETER_TYPE_Double,
				0.2, 0.001, true, 1.0, true
			);
			break;

		case 1: // two parallel storages
			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+250).c_str();
			s.Printf(tmpNode.c_str(), i+250);
			pNode1 = P.Add_Node(pNode,s,SG_T("Linear Module"),_TL(""));

			// Parameter a
			tmpName = SG_T("AQ(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,tmpName,	_TL("a(q)"),
				_TL(""),
				PARAMETER_TYPE_Double,
				-0.7, -0.99, true, -0.01, true
			);

			tmpName = SG_T("AS(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,	tmpName,	_TL("a(s)"),
				_TL(""),
				PARAMETER_TYPE_Double,
				-0.9, -0.99, true, -0.01, true
			);

			// Parameter b
			tmpName = SG_T("BQ(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,	tmpName,	_TL("b(q)"),
				_TL(""),
				PARAMETER_TYPE_Double,
				0.0, 0.0, true, 1.0, true
			);
			break;

		case 2: // two storages in series
			break;
		} // end switch (storconf)
		// Parameters of linear module -----------------------------

		tmpNode = SG_T("Node");
		tmpNode+=convert_sl::Int2String(i+300).c_str();
		s.Printf(tmpNode.c_str(), i+300);
		pNode1 = P.Add_Node(pNode,s,SG_T("Time Delay after Start of Rainfall (INTEGER)"),_TL(""));
						
		tmpName = SG_T("DELAY(");
			tmpName += tmpNode;
			tmpName += _TL(")");
		P.Add_Value(
			pNode1,tmpName,	SG_T("Time Delay (Rain-Runoff)"),
			SG_T("The delay after the start of rainfall, before the discharge starts to rise."),
			PARAMETER_TYPE_Int,
			0, 1, true, 100, true
		);

		// snow module parameters ----------------------------------
		if (m_bSnowModule)
		{
			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+350).c_str();
			s.Printf(tmpNode.c_str(), i+350);
			pNode1 = P.Add_Node(pNode,s,SG_T("Snow Module Parameters"),_TL(""));
			
			tmpName = SG_T("T_RAIN(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,tmpName,	SG_T("Temperature Threshold for Rainfall)"),
				SG_T("Below this threshold precipitation will fall as snow"),
				PARAMETER_TYPE_Double,
				-1.0, -10.0, true, 10.0, true
			);

			tmpName = SG_T("T_MELT(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,tmpName,	SG_T("Temperature Threshold for Melting"),
				SG_T("Above this threshold snow will start to melt"),
				PARAMETER_TYPE_Double,
				1.0, -5.0, true, 10.0, true
			);

			tmpName = SG_T("DD_FAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			P.Add_Value(
				pNode1,tmpName,	SG_T("Day-Degree Factor"),
				SG_T("Day-Degree Factor depends on catchment characteristics"),
				PARAMETER_TYPE_Double,
				0.7, 0.7, true, 9.2, true
			);
		}
		// snow module parameters ----------------------------------
	}
	
	
	if( SG_UI_Dlg_Parameters(&P, _TL("IHACRES Distributed Input Dialog 2")) )
	{
		// input table
		m_p_InputTable		= P("TABLE")				->asTable();
		// field numbers
		m_dateField			= P("DATE_Field")			->asInt();
		m_streamflowField	= P("DISCHARGE_Field")		->asInt();
		for (int i = 0; i < m_nElevBands; i++)
		{
			tmpNode = convert_sl::Int2String(i+1).c_str();
			
			// get precipitation column of Elevation Band[i]
			tmpName = SG_T("PCP Column: Elevation Band: ");
			tmpName+=tmpNode;
			m_p_pcpField[i]			= P(tmpName)		->asInt();

			// get temperature column of Elevation Band[i]
			tmpName = SG_T("TMP Column: Elevation Band: ");
			tmpName+=tmpNode;
			m_p_tmpField[i]			= P(tmpName)		->asInt();

			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+100).c_str();

			// get area[km2] of Elevation Band[i]
			tmpName = SG_T("Area [km2] Elev(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			m_p_elevbands[i].m_area	= P(tmpName)		->asDouble();

			// get mean elevation of Elevation Band[i]
			tmpName = SG_T("Mean Elevation [m.a.s.l] Elev(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			m_p_elevbands[i].m_mean_elev =P(tmpName)	->asDouble();
		

			// non-linear module parameters
			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+150).c_str();
			// get Tw
			tmpName = SG_T("TwFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			m_p_nonlinparms->mp_tw[i]	= P(tmpName)		->asDouble();

			// get f
			tmpName = SG_T("TFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			m_p_nonlinparms->mp_f[i]	= P(tmpName)		->asDouble();

			// get c
			tmpName = SG_T("CFAC(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			m_p_nonlinparms->mp_c[i]	= P(tmpName)		->asDouble();

			switch(m_IHAC_version)
			{
			case 0: // Jakeman & Hornberger (1993)
				break;
			case 1: // Croke et al. (2005)
				// get l
				tmpName = SG_T("LFAC(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_nonlinparms->mp_l[i]= P(tmpName)		->asDouble();

				// get p
				tmpName = SG_T("PFAC(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_nonlinparms->mp_p[i]= P(tmpName)		->asDouble();
			}

			// linear module parameters
			switch(m_nStorages)
			{
			case 1: // single storage
				tmpNode = SG_T("Node");
				tmpNode+=convert_sl::Int2String(i+250).c_str();
				// get a
				tmpName = SG_T("AFAC(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_linparms->a[i]		= P(tmpName)		->asDouble();

				// get b
				tmpName = SG_T("BFAC(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_linparms->b[i]		= P(tmpName)		->asDouble();
				break;
			case 2: // two storages
				tmpNode = SG_T("Node");
				tmpNode+=convert_sl::Int2String(i+250).c_str();
				// get aq
				tmpName = SG_T("AQ(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_linparms->aq[i]		= P(tmpName)		->asDouble();

				// get bq
				tmpName = SG_T("BQ(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_linparms->bq[i]		= P(tmpName)		->asDouble();

				// get as
				tmpName = SG_T("AS(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_p_linparms->as[i]		= P(tmpName)		->asDouble();

				// get bs
				m_p_linparms->bs[i] = ihacres.Calc_Parm_BS(m_p_linparms->aq[i],m_p_linparms->as[i],m_p_linparms->bq[i]);
				break;
			}

			// get delay
			tmpNode = SG_T("Node");
			tmpNode+=convert_sl::Int2String(i+300).c_str();

			tmpName = SG_T("DELAY(");
			tmpName += tmpNode;
			tmpName += _TL(")");
			m_delay						= P(tmpName)		->asInt();	

			if (m_bSnowModule)
			{
				tmpNode = SG_T("Node");
				tmpNode+=convert_sl::Int2String(i+350).c_str();

				// get T_RAIN
				tmpName = SG_T("T_RAIN(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_pSnowparms[i].T_Rain		= P(tmpName)		->asDouble();

				// get T_MELT
				tmpName = SG_T("T_MELT(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_pSnowparms[i].T_Melt		= P(tmpName)		->asDouble();

				// get DD_FAC
				tmpName = SG_T("DD_FAC(");
				tmpName += tmpNode;
				tmpName += _TL(")");
				m_pSnowparms[i].DD_FAC		= P(tmpName)		->asDouble();
			}
		}

		return(true);
	}
	return(false);
}