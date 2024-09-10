LOCAL	bool	g_prompt_and_reset_for_cauchy_deposition(
	INIT_DATA	*init,
	INIT_PHYSICS	*ip,
	Wave		*wave)
{
	char		axis[]={'t','x','y','z'}, s[Gets_BUF_SIZE];
	int		i, d, dim = wave->rect_grid->dim;
	Gas_param	*new_param;
	Front		*front = ip->root->front;
	INTERFACE	*intfc = front->interf;

	debug_print("deposition","Entered g_cauchy_deposition()\n");

	/* prompt for Cauchy deposition */
	screen("Type \'y\' to set cauchy deposition: ");
	Gets(s);
	if (s[0] != 'Y' && s[0] != 'y') return NO;

	screen("Type \'y\' to change the eos for states: ");
	Gets(s);
	if (s[0] == 'Y' || s[0] == 'y')
	    new_param = init_eos_params(init, ip, "  ", YES);
	else
	    new_param = NULL;

	screen("Enter the number of depositions (1 to %d): ",MAX_DEPOSITION_NUMBER);
	Scanf("%d\n", &dep_number);
	if (dep_number < 1 || dep_number > MAX_DEPOSITION_NUMBER)
	{
	    screen("Illegal number of depositions.\n");
	    clean_up(ERROR);
	}
	
	for (i = 0; i < dep_number; i++)
	{
	    screen("For deposition %d\n", i);
    	    
	    screen("Enter the component number for the deposition: ");
	    Scanf("%d\n",&deparam[i].comp);

	    screen("Choose the deposition type from\n");
	    screen("\tEnergy(dflt), Pressure, Temperature, X-Velocity,\n");
	    screen("\tY-Velocity, Z-Velocity, Density\n");
	    screen("Enter the deposition type: ");
	    Gets(s);
	    if (s[0] == 'P' || s[0] == 'p')
		deparam[i].type = EXT_PRESSURE;
	    else if (s[0] == 'T' || s[0] == 't')
		deparam[i].type = EXT_TEMPER;
	    else if (s[0] == 'X' || s[0] == 'x')
		deparam[i].type = EXT_VX;
	    else if (s[0] == 'Y' || s[0] == 'y')
		deparam[i].type = EXT_VY;
	    else if (s[0] == 'Z' || s[0] == 'z')
		deparam[i].type = EXT_VZ;
	    else if (s[0] == 'D' || s[0] == 'd')
		deparam[i].type = EXT_DENSITY;
	    else
		deparam[i].type = EXT_ENERGY;
	    printf("deparam[%d].type = %d\n",i,deparam[i].type);
	    
	    screen("Enter the base value of deposition: ");
	    Scanf("%f\n",&deparam[i].base);
	    screen("Enter the amplitude of deposition: ");
	    Scanf("%f\n",&deparam[i].amp);

	    screen("Enter the shape of deposition region (Rect or Ellip): ");
	    Gets(s);
	    if (s[0] == 'E' || s[0] == 'e')
		deparam[i].region = DEP_ELLIP;
	    else
		deparam[i].region = DEP_RECT;
	    
	    for (d = 0; d < dim+1; d++)
	    {
		screen("Along %c direction\n",axis[d]);
		if (d == 0 || deparam[i].region == DEP_RECT)
		{
		    deparam[i].bd[d][0] = -HUGE_VAL;
		    deparam[i].bd[d][1] = HUGE_VAL;
		    screen("Enter the lower and upper boundary: ");
		}
		else
		{
		    deparam[i].bd[d][0] = 0;
		    deparam[i].bd[d][1] = HUGE_VAL;
		    screen("Enter the center and radius: ");
		}

		Scanf("%f %f\n",deparam[i].bd[d],deparam[i].bd[d]+1);
		if (deparam[i].bd[d][0] == deparam[i].bd[d][1])
		{
		    deparam[i].prof[d] = CONSTANT_PROFILE;
		    continue; // depo layer length[d] = 0: CONSTANT
		}

		screen("Choose deposition profile from\n");
		screen("\tGaussian, Power, Sinusoidal, Constant(dflt)\n"); 
		screen("Enter the deposition profile: ");
		Gets(s);
		if (s[0] == 'g' || s[0] == 'G')
		{
		    deparam[i].prof[d] = GAUSSIAN;

		    screen("Enter the origin of the profile: ");
		    Scanf("%f\n",&deparam[i].orig[d]);
		    screen("Enter the decay length: ");
		    Scanf("%f\n",deparam[i].param[d]);
		    screen("Enter if it is exponential decay: ");
		    Gets(s);
		    if (s[0] == 'y' || s[0] == 'Y')
			deparam[i].flag[d][0] = true;
		    else
			deparam[i].flag[d][0] = false;
		}
		else if (s[0] == 'p' || s[0] == 'P')
		{
		    deparam[i].prof[d] = POWER;

		    screen("Enter the origin of the profile: ");
		    Scanf("%f\n",&deparam[i].orig[d]);
		    screen("Enter the decay exponent: ");
		    Scanf("%f\n",deparam[i].param[d]);
		}
		else if (s[0] == 's' || s[0] == 'S')
		{
		    deparam[i].prof[d] = SINUSOIDAL;

		    screen("Enter the origin of the profile: ");
		    Scanf("%f\n",&deparam[i].orig[d]);
		    screen("Enter the period: ");
		    Scanf("%f\n",deparam[i].param[d]);
		    screen("Enter the phase at origin in degrees: ");
		    Scanf("%f\n",deparam[i].param[d]+1);
		} 
		else
		{
		    deparam[i].prof[d] = CONSTANT_PROFILE;
		}
	    }
	}

	if(new_param != NULL)
	    change_states_param(front, wave, deparam[0].comp, new_param);

	debug_print("deposition","\nLeft g_cauchy_deposition()\n");

	return YES;
}	/* end of set_ext_deposition */