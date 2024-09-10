EXPORT	void	g_prompt_for_composition_type(
	INIT_DATA	*init)
{
	int	i;
	int	dim = i_intfc(init)->dim;
	char	s[Gets_BUF_SIZE];
	static	Prompt_type ctypes[] = {
	    {"PURE_NON_REACTIVE","PNR",3,{PURE_NON_REACTIVE} },
#if defined(MULTI_COMPONENT)
	    {"MULTI_COMP_NON_REACTIVE","MCNR",4,{MULTI_COMP_NON_REACTIVE}},
#endif /* defined(MULTI_COMPONENT) */
#if defined(COMBUSTION_CODE)
	    {"PTFLAME","PTF",3,{PTFLAME}},
	    {"ZND","ZND",3,ZND},
	    {"TWO_CONSTITUENT_REACTIVE","TCR",3,{TWO_CONSTITUENT_REACTIVE}},
	    {"THINFLAME","THF",3,{THINFLAME}},
#endif /* defined(COMBUSTION_CODE) */
	    {NULL, NULL, 0, {ERROR} }
	};

	material_composition_type(init) = PURE_NON_REACTIVE;
	screen("\nRequest composition type of materials. "
	       "Available types are\n");
	for (i = 0; ctypes[i].prompt != NULL; ++i)
	{
	    screen("\t\t%s (%s",ctypes[i].prompt,ctypes[i].select);
	    if (ctypes[i].type.itype == material_composition_type(init))
	    	screen(", default");
	    screen(")\n");
	}
	screen("\tEnter choice here: ");
	(void) Gets(s);
	if (s[0] != '\0')
	{
	    for (i = 0; ctypes[i].prompt != NULL; ++i)
	    {
	        if (strncasecmp(s,ctypes[i].select,ctypes[i].ncmp) == 0)
	        {
	            material_composition_type(init) = ctypes[i].type.itype;
	            break;
	        }
	    }
	}

        /* NOTE: NumberFloats(init) will be modified in g_compute_sizest() **/
        if(MULTI_COMP_NON_REACTIVE == material_composition_type(init))
        {
            (void) printf("Request for maximum number of composed materials: ");
            (void) Scanf("%d\n",&NumberFloats(init));
	    (void) printf("The maximum number of composed materials is %d\n",
                       NumberFloats(init));
        }
	g_compute_sizest(material_composition_type(init),
			 &StateSize(init),&NumberFloats(init),dim);
        /* This change should be universal */
        if(MULTI_COMP_NON_REACTIVE == material_composition_type(init))
        {
            g_set_sizeof_state(NULL,StateSize(init),NumberFloats(init));
            set_composition_type(material_composition_type(init));
        }
}		/*end g_prompt_for_composition_type*/