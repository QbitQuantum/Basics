	void __cdecl Phase_Info (
		const int		*phase,					// Current phase number
		Type_Of_Phase	*phase_type,			// Type of phase (numeric, analytic)
		DLL_Item		*phase_desc,			// Phase description
		DLL_Unit_Item	*phase_time,			// Time description
		DLL_Item		*ini_cost,				// Initial cost description
		DLL_Item		*integ_cost,			// Integral cost description
		DLL_Item		*term_cost,				// Terminal cost description
		int				*error					// Error flag
		)
	/* SYNOPSIS:
	 * returns for the specified phase, the type of the phase, its
	 * name and description, name and description of the
	 * independant variable and for each cost term. */
	{
#ifdef DEBUG_MODE
printf("Phase Info\n");_flushall();
#endif

		*error = 0;

		/*	what kind of phase */
		*phase_type					= Numeric;

		Phase_Description[*phase-1].Name_len	= strlen(Phase_Description[*phase-1].Name);
		Phase_Description[*phase-1].Desc_len	= strlen(Phase_Description[*phase-1].Desc);

		phase_desc->Desc			= Phase_Description[*phase-1].Desc;
		phase_desc->Name			= Phase_Description[*phase-1].Name;

		phase_desc->Desc_len        = Phase_Description[*phase-1].Desc_len;
		phase_desc->Name_len        = Phase_Description[*phase-1].Name_len;

		/*	time info */
		Time_Description.Name_len	= strlen(Time_Description.Name);
		Time_Description.Desc_len	= strlen(Time_Description.Desc);
		Time_Description.Unit_len	= strlen(Time_Description.Unit);

		phase_time->Desc			= Time_Description.Desc;
		phase_time->Name			= Time_Description.Name;
		phase_time->Unit			= Time_Description.Unit;

		phase_time->Desc_len		= Time_Description.Desc_len;
		phase_time->Name_len		= Time_Description.Name_len;
		phase_time->Unit_len		= Time_Description.Unit_len;

		/* ini cost info */
		Initial_Cost_Item.Name_len	= strlen(Initial_Cost_Item.Name);
		Initial_Cost_Item.Desc_len	= strlen(Initial_Cost_Item.Desc);

		ini_cost->Desc					= Initial_Cost_Item.Desc;
		ini_cost->Name					= Initial_Cost_Item.Name;

		ini_cost->Desc_len				= Initial_Cost_Item.Desc_len;
		ini_cost->Name_len				= Initial_Cost_Item.Name_len;

		/*	lagrange cost info
	 	*	if there isn't any, set Integral_Cost := Unspecified.  */
		Integral_Cost_Item.Name_len	= strlen(Integral_Cost_Item.Name);
		Integral_Cost_Item.Desc_len	= strlen(Integral_Cost_Item.Desc);

		integ_cost->Desc			= Integral_Cost_Item.Desc;
		integ_cost->Name			= Integral_Cost_Item.Name;

		integ_cost->Desc_len		= Integral_Cost_Item.Desc_len;
		integ_cost->Name_len		= Integral_Cost_Item.Name_len;
		
		/* terminal cost info */
		Terminal_Cost_Item.Name_len	= strlen(Terminal_Cost_Item.Name);
		Terminal_Cost_Item.Desc_len	= strlen(Terminal_Cost_Item.Desc);
			
		term_cost->Desc				= Terminal_Cost_Item.Desc;
		term_cost->Name				= Terminal_Cost_Item.Name;

		term_cost->Desc_len			= Terminal_Cost_Item.Desc_len;
		term_cost->Name_len			= Terminal_Cost_Item.Name_len;
	}