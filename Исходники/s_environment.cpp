static void ReadReverbDef (int lump)
{
	FScanner sc;
	const ReverbContainer *def;
	ReverbContainer *newenv;
	REVERB_PROPERTIES props;
	char *name;
	int id1, id2, i, j;
	bool inited[NUM_REVERB_FIELDS];
	BYTE bools[32];

	sc.OpenLumpNum(lump);
	while (sc.GetString ())
	{
		name = copystring (sc.String);
		sc.MustGetNumber ();
		id1 = sc.Number;
		sc.MustGetNumber ();
		id2 = sc.Number;
		sc.MustGetStringName ("{");
		memset (inited, 0, sizeof(inited));
		props.Instance = 0;
		props.Flags = 0;
		while (sc.MustGetString (), NUM_REVERB_FIELDS > (i = sc.MustMatchString (ReverbFieldNames)))
		{
			if (ReverbFields[i].Float)
			{
				sc.MustGetFloat ();
				props.*ReverbFields[i].Float = (float)clamp (sc.Float,
					double(ReverbFields[i].Min)/1000,
					double(ReverbFields[i].Max)/1000);
			}
			else if (ReverbFields[i].Int)
			{
				sc.MustGetNumber ();
				props.*ReverbFields[i].Int = (j = clamp (sc.Number,
					ReverbFields[i].Min, ReverbFields[i].Max));
				if (i == 0 && j != sc.Number)
				{
					sc.ScriptError ("The Environment field is out of range.");
				}
			}
			else
			{
				sc.MustGetString ();
				bools[ReverbFields[i].Flag] = sc.MustMatchString (BoolNames);
			}
			inited[i] = true;
		}
		if (!inited[0])
		{
			sc.ScriptError ("Sound %s is missing an Environment field.", name);
		}

		// Add the new environment to the list, filling in uninitialized fields
		// with values from the standard environment specified.
		def = DefaultEnvironments[props.Environment];
		for (i = 0; i < NUM_REVERB_FIELDS; ++i)
		{
			if (ReverbFields[i].Float)
			{
				if (!inited[i])
				{
					props.*ReverbFields[i].Float = def->Properties.*ReverbFields[i].Float;
				}
			}
			else if (ReverbFields[i].Int)
			{
				if (!inited[i])
				{
					props.*ReverbFields[i].Int = def->Properties.*ReverbFields[i].Int;
				}
			}
			else
			{
				if (!inited[i])
				{
					int mask = 1 << ReverbFields[i].Flag;
					if (def->Properties.Flags & mask)
					{
						props.Flags |= mask;
					}
				}
				else
				{
					if (bools[ReverbFields[i].Flag])
					{
						props.Flags |= 1 << ReverbFields[i].Flag;
					}
				}
			}
		}

		newenv = new ReverbContainer;
		newenv->Next = NULL;
		newenv->Name = name;
		newenv->ID = (id1 << 8) | id2;
		newenv->Builtin = false;
		newenv->Properties = props;
		newenv->SoftwareWater = false;
		S_AddEnvironment (newenv);
	}
}