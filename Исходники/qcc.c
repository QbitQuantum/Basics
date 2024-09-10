void WriteData (int crc)
{
	def_t		*def;
	ddef_t		*dd;
	dprograms_t	progs;
	char tname[1024];
	int			h;
	unsigned int			i;
	int size;

	for (def = pr.def_head.next ; def ; def = def->next)
	{
		if ((def->type->type == ev_field) && def->constant)
		{
			dd = &fields[numfielddefs];
			numfielddefs++;
			dd->type = def->type->aux_type->type == ev_int ? ev_float : def->type->aux_type->type;
			if (def->save == 0)
			{
					strcpy(tname, def->name);
					strcat(tname, "__");
					dd->s_name = CopyString(tname, 0);
			}
			else 
				dd->s_name = CopyString (def->name, 0);
			dd->ofs = G_INT(def->ofs);
		}
		else if (pr_optimize_constant_names && def->constant && (def->type->type != ev_function))
		{
			num_constant_names += strlen(def->name) + 1;
			num_constant_names += sizeof(ddef_t);
			continue;
		}
		else if (pr_optimize_unreferenced && pr_global_refs[def->ofs] <= 0)
		{
			if (!(def->type->type != ev_function))
			{
				num_unreferenced += 1;
				continue;
			}
		}
		else if (pr_optimize_unreferenced && def->type->type == ev_vector)
		{

			if (pr_global_refs[def->ofs] + pr_global_refs[def->ofs + 1] + pr_global_refs[def->ofs +1] == 3)
			{
				num_unreferenced += 3;
				def = def->next; // def_x
				def = def->next; // def_y
				def = def->next; // def_z
				continue;
			}
		}
		dd = &globals[numglobaldefs];
		dd->type = def->type->type == ev_int ? ev_float : def->type->type;
		if (def->save && ( dd->type != ev_field || def->constant != 1))
			dd->type |= DEF_SAVEGLOBAL;
		if (def->name)
		{
			if (pr_optimize_locals && (def->scope || !(STRCMP(def->name, "IMMEDIATE"))))
			{
				num_locals_saved += strlen(def->name);
				dd->s_name = 0;
			}
			else
				dd->s_name = CopyString (def->name, 0);
		}

		dd->ofs = def->ofs;
		numglobaldefs++;
	}
	strofs = (strofs+3)&~3;
	if (strofs > INT_MAX)
		PR_ParseWarning(122, "strofs exceeds INT_MAX by %i", strofs - INT_MAX);
	if (numstatements > INT_MAX)
		PR_ParseWarning(123, "numstatements exceeds INT_MAX by %i", numstatements - INT_MAX);
	if (numfunctions > SHRT_MAX)
		PR_ParseWarning(124, "numfunctions exceeds SHRT_MAX by %i", numfunctions - SHRT_MAX);
	if (numglobaldefs > SHRT_MAX)
		PR_ParseWarning(125, "numglobaldefs exceeds SHRT_MAX by %i", numglobaldefs - SHRT_MAX);
	if (numfielddefs > SHRT_MAX)
		PR_ParseWarning(126, "numfielddefs exceeds SHRT_MAX by %i", numfielddefs - SHRT_MAX);
	if (numpr_globals > SHRT_MAX)
		PR_ParseWarning(127, "numpr_globals exceeds SHRT_MAX by %i", numpr_globals - SHRT_MAX);
	if (crc != NQ_PROGHEADER_CRC && crc != QW_PROGHEADER_CRC)
		PR_ParseWarning(208, "System defs do match internal crcs.");
	if (summary)
	{

		summary_print("----------- Summary -----------\n");

		i = I_FloatTime() - StartTime;
		summary_print (" %02i:%02i elapsed time\n", (i / 60) % 59, i % 59);
		summary_print ("%6i strofs         (MAX: %6i)\n", strofs, MAX_STRINGS	);
		summary_print ("%6i numstatements  (MAX: %6i)\n", numstatements, MAX_STATEMENTS);
		summary_print ("%6i numfunctions   (MAX: %6i)\n", numfunctions, SHRT_MAX);
		summary_print ("%6i numglobaldefs  (MAX: %6i)\n", numglobaldefs, SHRT_MAX);
		summary_print ("%6i numfielddefs   (MAX: %6i)\n", numfielddefs, SHRT_MAX);
		summary_print ("%6i numpr_globals  (MAX: %6i)\n", numpr_globals, SHRT_MAX);
	}
	h = SafeOpenWrite (destfile);
	SafeWrite (h, &progs, sizeof(progs));

	progs.ofs_strings = lseek (h, 0, SEEK_CUR);
	progs.numstrings = strofs;
	SafeWrite (h, strings, strofs);

	progs.ofs_statements = lseek (h, 0, SEEK_CUR);
	progs.numstatements = numstatements;
	for (i=0 ; i<numstatements ; i++)
	{
		statements[i].op = LittleShort(statements[i].op);
		statements[i].a = LittleShort(statements[i].a);
		statements[i].b = LittleShort(statements[i].b);
		statements[i].c = LittleShort(statements[i].c);
	}
	SafeWrite (h, statements, numstatements*sizeof(dstatement_t));

	progs.ofs_functions = lseek (h, 0, SEEK_CUR);
	progs.numfunctions = numfunctions;
	for (i=0 ; i<numfunctions ; i++)
	{
		functions[i].first_statement = LittleLong (functions[i].first_statement);
		functions[i].parm_start = LittleLong (functions[i].parm_start);
		functions[i].s_name = LittleLong (functions[i].s_name < 0 || functions[i].s_name > strofs ? 0 : functions[i].s_name);
		functions[i].s_file = LittleLong (functions[i].s_file < 0 || functions[i].s_file > strofs ? 0 : functions[i].s_file);
		functions[i].numparms = LittleLong (functions[i].numparms > MAX_PARMS ? MAX_PARMS : functions[i].numparms);
		functions[i].locals = LittleLong (functions[i].locals);
	}	
	SafeWrite (h, functions, numfunctions*sizeof(dfunction_t));

	progs.ofs_globaldefs = lseek (h, 0, SEEK_CUR);
	progs.numglobaldefs = numglobaldefs;
	for (i=0 ; i<numglobaldefs ; i++)
	{
		globals[i].type = LittleShort (globals[i].type);
		globals[i].ofs = LittleShort (globals[i].ofs);
		globals[i].s_name = LittleLong (globals[i].s_name);
	}
	SafeWrite (h, globals, numglobaldefs*sizeof(ddef_t));

	progs.ofs_fielddefs = lseek (h, 0, SEEK_CUR);
	progs.numfielddefs = numfielddefs;
	for (i=0 ; i<numfielddefs ; i++)
	{
		fields[i].type = LittleShort (fields[i].type);
		fields[i].ofs = LittleShort (fields[i].ofs);
		fields[i].s_name = LittleLong (fields[i].s_name < 0 || fields[i].s_name > strofs ? 0: fields[i].s_name);
	}
	SafeWrite (h, fields, numfielddefs*sizeof(ddef_t));

	progs.ofs_globals = lseek (h, 0, SEEK_CUR);
	progs.numglobals = numpr_globals;
	for (i=0 ; i<numpr_globals ; i++)
		((int *)pr_globals)[i] = LittleLong (((int *)pr_globals)[i]);
	SafeWrite (h, pr_globals, numpr_globals*4);

	i = (int)lseek(h, 0, SEEK_CUR);
	if (summary)
		summary_print ("%6i TOTAL SIZE\n", i);	
	size = (i+16)&(~15);
	progs.entityfields = pr.size_fields;

	progs.version = PROG_VERSION;
	progs.crc = crc;
	if (summary)
	{
		summary_print("%6i Progheader CRC ", crc);
		if (crc == NQ_PROGHEADER_CRC)
			summary_print("(   Quake   )\n");
		else if (crc == QW_PROGHEADER_CRC)
			summary_print("(Quake World)\n");
		else
			summary_print("(  UNKNOWN  )\n");
	}

// byte swap the header and write it out
	for (i=0 ; i<sizeof(progs)/4 ; i++)
		((int *)&progs)[i] = LittleLong ( ((int *)&progs)[i] );		
	lseek (h, 0, SEEK_SET);
	SafeWrite (h, &progs, sizeof(progs));

// look for progs
	if ((def = PR_GetDef(&type_entity, "progs", NULL, false, 0, 0)))
	{
		lseek(h, progs.ofs_globals + 4 * def->ofs, SEEK_SET);
		i = - (size + 112);
		SafeWrite (h, &i, 4);
	}

	for (def = pr.def_head.next ; def ; def = def->next)
	{
		if (def->type->arraysize)
		{
			lseek(h, progs.ofs_globals + 4 * def->ofs, SEEK_SET);
			i = (-(size + 112)) + progs.ofs_globals + 4 * (def->arraystart);
			//printf("filled in %s with %i\n", def->name, def->arraystart);
			SafeWrite (h, &i, 4);		
		}
	}
	if (summary)
	{
		summary_print ("%6i precache_sounds(MAX: %6i)\n", numsounds, MAX_SOUNDS);
		summary_print ("%6i precache_models(MAX: %6i)\n", nummodels, MAX_MODELS);
	}
	close (h);
	
	if (summary)
	{
		if (pr_optimize_eliminate_temps || pr_optimize_shorten_ifs || pr_optimize_nonvec_parms
			|| pr_optimize_constant_names || pr_optimize_defs || pr_optimize_hash_strings ||
			pr_optimize_locals || pr_optimize_function_names || pr_optimize_filenames ||
			pr_optimize_unreferenced || pr_optimize_logicops || pr_optimize_recycle
			|| pr_optimize_constant_arithmetic) 
		{
			summary_print("----------- Optimization Summary -----------\n");
			if (pr_optimize_eliminate_temps)
				summary_print("%d stores shortened\n", num_stores_shortened);
			if (pr_optimize_shorten_ifs)
				summary_print("%d ifs shortened\n", num_ifs_shortened);
			if (pr_optimize_nonvec_parms)
				summary_print("%d non-vector parms\n", num_nonvec_parms);
			if (pr_optimize_constant_names)
				summary_print("%d bytes of constant defs/names eliminated\n", num_constant_names);
			if (pr_optimize_defs)
				summary_print("%d duplicate defs eliminated\n", num_defs);
			if (pr_optimize_hash_strings)
				summary_print("%d bytes of duplicate strings eliminated\n", num_strings);
			if (pr_optimize_locals)
				summary_print("%d bytes of immediate and local names eliminated\n", num_locals_saved);
			if (pr_optimize_function_names)
				summary_print("%d bytes of function names eliminated\n", num_funcs_saved);
			if (pr_optimize_filenames)
				summary_print("%d bytes of filenames eliminated\n", num_files_saved);
			if (pr_optimize_unreferenced)
				summary_print("%d unreferenced global defs eliminated\n", num_unreferenced);
			if (pr_optimize_logicops)
				summary_print("%d logic jumps added\n", num_logic_jumps);
			if (pr_optimize_recycle)
				summary_print("%d temporary globals recycled\n", num_recycled);
			if (pr_optimize_constant_arithmetic)
				summary_print("%d constant arithmetic statements eliminated\n", num_constant_ops_saved);
		}
	}
}