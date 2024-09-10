/* when vectorize = 0 */
void c_out(const char* prefix)
{
#if NMODL
	Item *q;
	extern int point_process;
#endif

	Fprintf(fcout, "/* Created by Language version: %s */\n", nmodl_version_);
	Fflush(fcout);

#if VECTORIZE
	if (vectorize) {
		vectorize_do_substitute();
		kin_vect2();	/* heh, heh.. bet you can't guess what this is */
		c_out_vectorize(prefix);
		return;
	}
#endif
#if VECTORIZE
	P("/* NOT VECTORIZED */\n");
#endif
	Fflush(fcout);
	/* things which must go first and most declarations */
#if SIMSYS
	P("#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>\n#include \"mathlib.h\"\n");
	P("#include \"common.h\"\n#include \"softbus.h\"\n");
	P("#include \"sbtypes.h\"\n#include \"Solver.h\"\n");
#else
	P("#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>\n#include \"scoplib_ansi.h\"\n");
	P("#undef PI\n");
	P("#define nil 0\n");
P("#include \"md1redef.h\"\n");
P("#include \"section.h\"\n");
P("#include \"nrniv_mf.h\"\n");
P("#include \"md2redef.h\"\n");

#endif
	printlist(defs_list);
	printlist(firstlist);
	P("static int _reset;\n");
#if NMODL
	P("static ");
#endif	
	if (modelline) {
		Fprintf(fcout, "char *modelname = \"%s\";\n\n", modelline);
	} else {
		Fprintf(fcout, "char *modelname = \"\";\n\n");
	}
	Fflush(fcout);		/* on certain internal errors partial output
				 * is helpful */
	P("static int error;\n");
#if NMODL
	P("static ");
#endif	
	P("int _ninits = 0;\n");
	P("static int _match_recurse=1;\n");
#if NMODL
	P("static void ");
#endif	
	P("_modl_cleanup(){ _match_recurse=1;}\n");
	/*
	 * many machinations are required to make the infinite number of
	 * definitions involving _p in defs.h to be invisible to the user 
	 */
	/*
	 * This one allows scop variables in functions which do not have the
	 * p array as an argument 
	 */
#if SIMSYS || HMODL || NMODL
#else
	P("static double *_p;\n\n");
#endif
	funcdec();
	Fflush(fcout);

	/*
	 * translations of named blocks into functions, procedures, etc. Also
	 * some special declarations used by some blocks 
	 */
	printlist(procfunc);
	Fflush(fcout);

	/* Initialization function must always be present */
#if NMODL
	P("\nstatic void initmodel() {\n  int _i; double _save;");
#endif
#if SIMSYS || HMODL
	P("\ninitmodel() {\n  int _i; double _save;");
#endif
#if (!(SIMSYS || HMODL || NMODL))
	P("\ninitmodel(_pp) double _pp[]; {\n int _i; double _save; _p = _pp;");
#endif
#if !NMODL
	P("_initlists();\n");
#endif
	P("_ninits++;\n");
	P(saveindep); /*see solve.c; blank if not a time dependent process*/
	P("{\n");
	initstates();
	printlist(initfunc);
	if (match_bound) {
		P("\n_init_match(_save);");
	}
	P("\n}\n}\n");
	Fflush(fcout);

#if NMODL
	/* generation of initmodel interface */
#if VECTORIZE
	P("\nstatic void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){\n");
	  P("Node *_nd; double _v; int* _ni; int _iml, _cntml;\n");
	  P("#if CACHEVEC\n");
	  P("    _ni = _ml->_nodeindices;\n");
	  P("#endif\n");
	  P("_cntml = _ml->_nodecount;\n");
	  P("for (_iml = 0; _iml < _cntml; ++_iml) {\n");
	  P(" _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];\n");
#else
	P("\nstatic nrn_init(_prop, _v) Prop *_prop; double _v; {\n");
	P(" _p = _prop->param; _ppvar = _prop->dparam;\n");
#endif
	if (debugging_ && net_receive_) {
		P(" _tsav = -1e20;\n");
	}
	if (!artificial_cell) {ext_vdef();}
	if (!artificial_cell) {P(" v = _v;\n");}
	printlist(get_ion_variables(1));
	P(" initmodel();\n");
	printlist(set_ion_variables(2));
#if VECTORIZE
	P("}}\n");
#else
	P("}\n");
#endif

	/* standard modl EQUATION without solve computes current */
	P("\nstatic double _nrn_current(double _v){double _current=0.;v=_v;");
#if CVODE
	if (cvode_nrn_current_solve_) {
		fprintf(fcout, "if (cvode_active_) { %s(); }\n", cvode_nrn_current_solve_->name);
	}
#endif
	P("{");
	if (currents->next != currents) {
		printlist(modelfunc);
	}
	ITERATE(q, currents) {
		Sprintf(buf, " _current += %s;\n", SYM(q)->name);
		P(buf);
	}