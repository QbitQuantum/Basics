FState *FStateDefinitions::ResolveGotoLabel (AActor *actor, PClassActor *mytype, char *name)
{
	PClassActor *type = mytype;
	FState *state;
	char *namestart = name;
	char *label, *offset, *pt;
	int v;

	// Check for classname
	if ((pt = strstr (name, "::")) != NULL)
	{
		const char *classname = name;
		*pt = '\0';
		name = pt + 2;

		// The classname may either be "Super" to identify this class's immediate
		// superclass, or it may be the name of any class that this one derives from.
		if (stricmp (classname, "Super") == 0)
		{
			type = dyn_cast<PClassActor>(type->ParentClass);
			actor = GetDefaultByType(type);
		}
		else
		{
			// first check whether a state of the desired name exists
			PClass *stype = PClass::FindClass (classname);
			if (stype == NULL)
			{
				I_Error ("%s is an unknown class.", classname);
			}
			if (!stype->IsDescendantOf (RUNTIME_CLASS(AActor)))
			{
				I_Error ("%s is not an actor class, so it has no states.", stype->TypeName.GetChars());
			}
			if (!stype->IsAncestorOf (type))
			{
				I_Error ("%s is not derived from %s so cannot access its states.",
					type->TypeName.GetChars(), stype->TypeName.GetChars());
			}
			if (type != stype)
			{
				type = static_cast<PClassActor *>(stype);
				actor = GetDefaultByType (type);
			}
		}
	}
	label = name;
	// Check for offset
	offset = NULL;
	if ((pt = strchr (name, '+')) != NULL)
	{
		*pt = '\0';
		offset = pt + 1;
	}
	v = offset ? strtol (offset, NULL, 0) : 0;

	// Get the state's address.
	if (type == mytype)
	{
		state = FindState (label);
	}
	else
	{
		state = type->FindStateByString(label, true);
	}

	if (state != NULL)
	{
		state += v;
	}
	else if (v != 0)
	{
		I_Error ("Attempt to get invalid state %s from actor %s.", label, type->TypeName.GetChars());
	}
	else
	{
		Printf (TEXTCOLOR_RED "Attempt to get invalid state %s from actor %s.\n", label, type->TypeName.GetChars());
	}
	delete[] namestart;		// free the allocated string buffer
	return state;
}