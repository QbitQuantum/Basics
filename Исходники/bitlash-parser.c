//
//	Recursive descent parser, old-school style.
//
void getfactor(void) {
numvar thesymval = symval;
byte thesym = sym;
	getsym();		// eat the sym we just saved

	switch (thesym) {
		case s_nval:
			vpush(thesymval);
			break;
			
		case s_nvar:
			if (sym == s_equals) {		// assignment, push is after the break;
				getsym();
				assignVar(thesymval, getnum());
			}
			else if (sym == s_incr) {	// postincrement nvar++
				vpush(getVar(thesymval));
				assignVar(thesymval, getVar(thesymval) + 1);
				getsym();
				break;
			}
			else if (sym == s_decr) {	// postdecrement nvar--
				vpush(getVar(thesymval));
				assignVar(thesymval, getVar(thesymval) - 1);
				getsym();
				break;
			}
			vpush(getVar(thesymval));			// both assignment and reference get pushed here
			break;

		case s_nfunct:
			dofunctioncall(thesymval);			// get its value onto the stack
			break;

		// Script-function-returning-value used as a factor
		case s_script_eeprom:				// macro returning value
			callscriptfunction(SCRIPT_EEPROM, findend(thesymval));
			break;

		case s_script_progmem:
			callscriptfunction(SCRIPT_PROGMEM, thesymval);
			break;

		case s_script_file:
			callscriptfunction(SCRIPT_FILE, (numvar) 0);	// name implicitly in idbuf!
			break;

		case s_apin:					// analog pin reference like a0
			if (sym == s_equals) { 		// digitalWrite or analogWrite
				getsym();
				analogWrite(thesymval, getnum());
				vpush(expval);
			}
			else vpush(analogRead(thesymval));
			break;

		case s_dpin:					// digital pin reference like d1
			if (sym == s_equals) { 		// digitalWrite or analogWrite
				getsym();
				digitalWrite(thesymval, getnum());
				vpush(expval);
			}
			else vpush(digitalRead(thesymval));
			break;

		case s_incr:
			if (sym != s_nvar) expected(M_var);
			assignVar(symval, getVar(symval) + 1);
			vpush(getVar(symval));
			getsym();
			break;

		case s_decr:		// pre decrement
			if (sym != s_nvar) expected(M_var);
			assignVar(symval, getVar(symval) - 1);
			vpush(getVar(symval));
			getsym();
			break;

		case s_arg:			// arg(n) - argument value
			if (sym != s_lparen) expectedchar(s_lparen);
			getsym(); 		// eat '('
			vpush(getarg(getnum()));
			if (sym != s_rparen) expectedchar(s_rparen);
			getsym();		// eat ')'
			break;

		case s_lparen:  // expression in parens
			getexpression();
			if (exptype != s_nval) expected(M_number);
			if (sym != s_rparen) missing(M_rparen);
			vpush(expval);
			getsym();	// eat the )
			break;

		//
		// The Family of Unary Operators, which Bind Most Closely to their Factor
		//
		case s_add:			// unary plus (like +3) is kind of a no-op
			getfactor();	// scan a factor and leave its result on the stack
			break;			// done
	
		case s_sub:			// unary minus (like -3)
			getfactor();
			vpush(-vpop());	// similar to above but we adjust the stack value
			break;
	
		case s_bitnot:
			getfactor();
			vpush(~vpop());
			break;
	
		case s_logicalnot:
			getfactor();
			vpush(!vpop());
			break;

		case s_bitand:		// &var gives address-of-var; &macro gives eeprom address of macro
			if (sym == s_nvar) vpush((numvar) &vars[symval]);
			else if (sym == s_script_eeprom) vpush(symval);
			else expected(M_var);
			getsym();		// eat the var reference
			break;

		case s_mul:			// *foo is contents-of-address-foo; *foo=bar is byte poke assignment

/*****
// what is really acceptable for an lvalue here? ;)
//	*y = 5 is failing now by assigning 5 to y before the * is dereferenced
//	due to calling getfactor
//	everything else works :(
*****/
			getfactor();
#if 0
			if (sym == s_equals) {
				getsym();	// eat '='
				getexpression();
				* (volatile byte *) vpop() = (byte) expval;
				vpush((numvar) (byte) expval);
			} 
			else 
#endif
			vpush((numvar) (* (volatile byte *) vpop()));
			break;

		default: 
			unexpected(M_number);
	}

}