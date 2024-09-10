static
void
pa_ip(
char *str)
{
	char *s;
	const char *args;
	char c;
	unsigned long i;
	struct pa_opcode *insn;
	char *argsStart;
	unsigned long   opcode;
	int match = FALSE;
	int comma = 0;

	int reg,reg1,reg2,s2,s3;
	unsigned int im21,im14,im11,im5;
	int m,a,u,f;
	int cmpltr,nullif, flag;
	int sfu, cond;
	char *name;
	char *save_s, *p;
	short reference;

	reference = 0;

#ifdef PA_DEBUG
	fprintf(stderr,"STATEMENT: \"%s\"\n",str);
#endif
	for (s = str; isupper(*s) || islower(*s) || (*s >= '0' && *s <= '3'); ++s)
		;
	switch (*s) {

	case '\0':
		break;

	case ',':
		comma = 1;

	/*FALLTHROUGH*/

	case ' ':
		*s++ = '\0';
		break;

	default:
		as_bad("Unknown opcode: `%s'", str);
		exit(1);
	}

	save_s = str;

	while ( *save_s ) {
		if ( isupper(*save_s) )
			*save_s = tolower(*save_s);
		save_s++;
	}

	if ((insn = (struct pa_opcode *) hash_find(op_hash, str)) == NULL) {
		as_bad("Unknown opcode: `%s'", str);
		return;
	}
	if (comma) {
		*--s = ',';
	}
	argsStart = s;
	for (;;) {
		opcode = insn->match;
		memset(&the_insn, '\0', sizeof(the_insn));
		the_insn.reloc = NO_RELOC;    /* USV */

/*
* Build the opcode, checking as we go to make
* sure that the operands match
*/
		for (args = insn->args; ; ++args) {

			switch (*args) {

			case '\0':  /* end of args */
  				if (*s == '\0') {
					match = TRUE;
  				}
  				break;

			case '(':   /* these must match exactly */
			case ')':
			case ',':
			case ' ':
  				if (*s++ == *args)
					continue;
  				break;

			case 'b':   /* 5 bit register field at 10 */
  				reg = pa_parse_number(&s);
  				if ( reg < 32 && reg >= 0 ) {
					opcode |= reg << 21;
					continue;
  				}
  				break;
			case 'x':   /* 5 bit register field at 15 */
  				reg = pa_parse_number(&s);
  				if ( reg < 32 && reg >= 0 ) {
					opcode |= reg << 16;
					continue;
  				}
  				break;
			case 't':   /* 5 bit register field at 31 */
  				reg = pa_parse_number(&s);
  				if ( reg < 32 && reg >= 0 ) {
					opcode |= reg;
					continue;
  				}
  				break;
			case 'T':   /* 5 bit field length at 31 (encoded as 32-T) */
  /*
reg = pa_parse_number(&s);
   */
				getAbsoluteExpression(s);
  				if ( the_insn.exp.X_seg == SEG_ABSOLUTE ) {
					reg = the_insn.exp.X_add_number;
					if ( reg <= 32 && reg > 0 ) {
  						opcode |= 32 - reg;
  						s = expr_end;
  						continue;
					}
  				}
  				break;
			case '5':   /* 5 bit immediate at 15 */
				getAbsoluteExpression(s);
/** PJH: The following 2 calls to as_bad() might eventually **/
/**      want to end up as as_warn().  **/
				if (   the_insn.exp.X_add_number > 15 ) {
					as_bad("5 bit immediate: %lld"
					       " > 15. Set to 15",
						the_insn.exp.X_add_number);
					the_insn.exp.X_add_number = 15;
				}
				else if ( the_insn.exp.X_add_number < -16 ) {
						as_bad("5 bit immediate: "
						   "%lld < -16. Set to -16",
						    the_insn.exp.X_add_number);
						the_insn.exp.X_add_number = -16;
					}

				im5 = low_sign_unext(evaluateAbsolute(
						     the_insn.exp,0),5);
				opcode |= ( im5 << 16 );
				s = expr_end;
				continue;

			case 's':   /* 2 bit space identifier at 17 */
				s2 = pa_parse_number(&s);
				if ( s2 < 4 && s2 >= 0 ) {
					opcode |= s2 << 14;
					continue;
				}
				break;
			case 'S':   /* 3 bit space identifier at 18 */
				s3 = pa_parse_number(&s);
				if ( s3 < 8 && s3 >= 0 ) {
					s3 = dis_assemble_3(s3);
					opcode |= s3 << 13;
					continue;
				}
				break;
			case 'c':   /* indexed load completer. */
				i = m = u = 0;
				while ( *s == ',' && i < 2 ) {
					s++;
					if ( strncasecmp(s,"sm",2) == 0 ) {
						m = u = 1;
						s++;
						i++;
					}
					else if ( strncasecmp(s,"m",1) == 0 )
	  						m = 1;
						else if ( strncasecmp(s,"s",1) == 0 )
  								u = 1;
							else
  								as_bad("Unrecognized Indexed Load"
									"Completer...assuming 0");
					s++;
					i++;
  				}
  				if ( i > 2 )
					as_bad("Illegal Indexed Load Completer Syntax..."
						"extras ignored");
  				while ( *s == ' ' || *s == '\t' )
					s++;
  
  				opcode |= m << 5;
  				opcode |= u << 13;
  				continue;
			case 'C':   /* short load and store completer */
				m = a = 0;
				if ( *s == ',' ) {
					s++;
					if ( strncasecmp(s,"ma",2) == 0 ) {
						a = 0;
						m = 1;
					}
					else if ( strncasecmp(s,"mb",2) == 0 ) {
							m = a = 1;
						}
						else
							as_bad("Unrecognized Indexed Load Completer"
								"...assuming 0");
					s += 2;
				}
				while ( *s == ' ' || *s == '\t' )
					s++;
				opcode |= m << 5;
				opcode |= a << 13;
				continue;

			/* bug #41317 .... [email protected]
			 * Fri Jul 22 09:43:46 PDT 1994
			 *
			 * Modified to parse 'cache control hints'
			 *
			 * These parse ",cc" and encode "cc" in 2 bits at 20,
			 * where "cc" encoding is as given in Tables 5-8, 5-9.
			 * Refer to 'PA-RISC 1.1 Architecture and Instruction Set
			 * Reference Manual, Second Edition' for the tables.
			 */
			case 'Y':   /* Store Bytes Short completer */
						/* with cache control hints    */
			{
				unsigned long result = (unsigned long)0UL;
				
				i = m = a = 0;
				while ( *s == ',' && i < 3 ) {
					s++;
					if ( strncasecmp(s,"m",1) == 0 )
						m = 1;
					else if ( strncasecmp(s,"b",1) == 0 &&
							  (strncasecmp((s+1),"c",1) != 0) )
							a = 0;
						else if ( strncasecmp(s,"e",1) == 0 )
								a = 1;
							else if ( strncmp(s,",",1) == 0 ) /* no completer */
								result |= parse_cache_control_hint(&s, 0);
							else if ( (strncasecmp(s,"c",1) == 0) ||
			          				(strncasecmp(s,"b",1) == 0) ) {/* just 1 completer */
								s--;
								result |= parse_cache_control_hint(&s, 0);
							}
							else
								as_bad("Unrecognized Store Bytes Short"
									"Completer with cache control hints"
									" ...assuming 0");
					if (result == (unsigned long)0UL)
						s++;
					i++;
				}
/**		if ( i >= 2 ) **/
				if ( i > 3 )
					as_bad("Illegal Store Bytes Short Completer "
						"with cache control hints ...  extras ignored");
				while ( *s == ' ' || *s == '\t' ) /* skip to next operand */
					s++;
				opcode |= result;
				opcode |= m << 5;
				opcode |= a << 13;
				continue;
			}
			case '<':   /* non-negated compare/subtract conditions. */
				cmpltr = pa_parse_nonneg_cmpsub_cmpltr(&s);
				if ( cmpltr < 0 ) {
					as_bad("Unrecognized Compare/Subtract Condition: %c",*s);
					cmpltr = 0;
				}
				opcode |= cmpltr << 13;
				continue;
			case '?':   /* negated or non-negated cmp/sub conditions. */
					/* used only by ``comb'' and ``comib'' pseudo-ops */
				save_s = s;
				cmpltr = pa_parse_nonneg_cmpsub_cmpltr(&s);
				if ( cmpltr < 0 ) {
					s = save_s;
					cmpltr = pa_parse_neg_cmpsub_cmpltr(&s);
					if ( cmpltr < 0 ) {
						as_bad("Unrecognized Compare/Subtract Condition: %c"
							,*s);
						cmpltr = 0;
					}
					else {
						opcode |= 1 << 27; /* required opcode change to make
											COMIBT into a COMIBF or a
											COMBT into a COMBF or a
											ADDBT into a ADDBF or a
											ADDIBT into a ADDIBF */
					}
				}
				opcode |= cmpltr << 13;
				continue;
			case '!':   /* negated or non-negated add conditions. */
				/* used only by ``addb'' and ``addib'' pseudo-ops */
				save_s = s;
				cmpltr = pa_parse_nonneg_add_cmpltr(&s);
				if ( cmpltr < 0 ) {
					s = save_s;
					cmpltr = pa_parse_neg_add_cmpltr(&s);
					if ( cmpltr < 0 ) {
						as_bad("Unrecognized Compare/Subtract Condition: %c",
							*s);
						cmpltr = 0;
					}
					else {
						opcode |= 1 << 27; /* required opcode change to make
											COMIBT into a COMIBF or a
											COMBT into a COMBF or a
											ADDBT into a ADDBF or a
											ADDIBT into a ADDIBF */
					}
				}
				opcode |= cmpltr << 13;
				continue;
			case '-':   /* compare/subtract conditions */
				f = cmpltr = 0;
				save_s = s;
				if ( *s == ',' ) {
					cmpltr = pa_parse_nonneg_cmpsub_cmpltr(&s);
					if ( cmpltr < 0 ) {
						f = 1;
						s = save_s;
						cmpltr = pa_parse_neg_cmpsub_cmpltr(&s);
						if ( cmpltr < 0 ) {
							as_bad("Unrecognized Compare/Subtract Condition");
						}
					}
				}
				opcode |= cmpltr << 13;
				opcode |= f << 12;
				continue;
			case '+':   /* non-negated add conditions */
				flag = nullif = cmpltr = 0;
				if ( *s == ',' ) {
					s++;
					name = s;
					while ( *s != ',' && *s != ' ' && *s != '\t' )
						s += 1;
					c = *s;
					*s = 0x00;
					if ( strcmp(name,"=") == 0 ) {
						cmpltr = 1;
						}
						else if ( strcmp(name,"<") == 0 ) {
						cmpltr = 2;
						}
						else if ( strcmp(name,"<=") == 0 ) {
						cmpltr = 3;
						}
						else if ( strcasecmp(name,"nuv") == 0 ) {
						cmpltr = 4;
						}
						else if ( strcasecmp(name,"znv") == 0 ) {
						cmpltr = 5;
						}
						else if ( strcasecmp(name,"sv") == 0 ) {
						cmpltr = 6;
						}
						else if ( strcasecmp(name,"od") == 0 ) {
						cmpltr = 7;
						}
						else if ( strcasecmp(name,"n") == 0 ) {
						nullif = 1;
						}
						else if ( strcasecmp(name,"tr") == 0 ) {
						cmpltr = 0;
						flag   = 1;
						}
						else if ( strcasecmp(name,"<>") == 0 ) {
						flag = cmpltr = 1;
						}
						else if ( strcasecmp(name,">=") == 0 ) {
						cmpltr = 2;
						flag   = 1;
						}
						else if ( strcasecmp(name,">") == 0 ) {
						cmpltr = 3;
						flag   = 1;
						}
						else if ( strcasecmp(name,"uv") == 0 ) {
						cmpltr = 4;
						flag   = 1;
						}
						else if ( strcasecmp(name,"vnz") == 0 ) {
						cmpltr = 5;
						flag   = 1;
						}
						else if ( strcasecmp(name,"nsv") == 0 ) {
						cmpltr = 6;
						flag   = 1;
						}
						else if ( strcasecmp(name,"ev") == 0 ) {
						cmpltr = 7;
						flag   = 1;
						}
						else
						as_bad("Unrecognized Add Condition: %s",name);
					*s = c;
				}
				nullif = pa_parse_nullif(&s);
				opcode |= nullif << 1;
				opcode |= cmpltr << 13;
				opcode |= flag << 12;
				continue;		
			case '&':   /* logical instruction conditions */
				f = cmpltr = 0;
				if ( *s == ',' ) {
					s++;
					name = s;
					while ( *s != ',' && *s != ' ' && *s != '\t' )
						s += 1;
					c = *s;
					*s = 0x00;
					if ( strcmp(name,"=") == 0 ) {
						cmpltr = 1;
						}
						else if ( strcmp(name,"<") == 0 ) {
						cmpltr = 2;
						}
						else if ( strcmp(name,"<=") == 0 ) {
						cmpltr = 3;
						}
						else if ( strcasecmp(name,"od") == 0 ) {
						cmpltr = 7;
						}
						else if ( strcasecmp(name,"tr") == 0 ) {
						cmpltr = 0;
						f = 1;
						}
						else if ( strcmp(name,"<>") == 0 ) {
						f = cmpltr = 1;
						}
						else if ( strcmp(name,">=") == 0 ) {
						cmpltr = 2;
						f = 1;
						}
						else if ( strcmp(name,">") == 0 ) {
						cmpltr = 3;
						f = 1;
						}
						else if ( strcasecmp(name,"ev") == 0 ) {
						cmpltr = 7;
						f = 1;
						}
						else
						as_bad("Unrecognized Logical Instruction Condition:"
							" %s",name);
					*s = c;
				}
				opcode |= cmpltr << 13;
				opcode |= f << 12;		
				continue;
			case 'U':   /* unit instruction conditions */
				cmpltr = 0;
				f = 0;
				if ( *s == ',' ) {
					s++;
					if ( strncasecmp(s,"sbz",3) == 0 ) {
						cmpltr = 2;
						s += 3;
						}
						else if ( strncasecmp(s,"shz",3) == 0 ) {
						cmpltr = 3;
						s += 3;
						}
						else if ( strncasecmp(s,"sdc",3) == 0 ) {
						cmpltr = 4;
						s += 3;
						}
						else if ( strncasecmp(s,"sbc",3) == 0 ) {
						cmpltr = 6;
						s += 3;
						}
						else if ( strncasecmp(s,"shc",3) == 0 ) {
						cmpltr = 7;
						s += 3;
						}
						else if ( strncasecmp(s,"tr",2) == 0 ) {
						cmpltr = 0;
						f = 1;
						s += 2;
						}
						else if ( strncasecmp(s,"nbz",3) == 0 ) {
						cmpltr = 2;
						f = 1;
						s += 3;
						}
						else if ( strncasecmp(s,"nhz",3) == 0 ) {
						cmpltr = 3;
						f = 1;
						s += 3;
						}
						else if ( strncasecmp(s,"ndc",3) == 0 ) {
						cmpltr = 4;
						f = 1;
						s += 3;
						}
						else if ( strncasecmp(s,"nbc",3) == 0 ) {
						cmpltr = 6;
						f = 1;
						s += 3;
						}
						else if ( strncasecmp(s,"nhc",3) == 0 ) {
						cmpltr = 7;
						f = 1;
						s += 3;
						}
						else
						as_bad("Unrecognized Logical Instruction Condition:"
							" %c",*s);
				}
				opcode |= cmpltr << 13;
				opcode |= f << 12;		
				continue;
			case '>':   /* shift/extract/deposit conditions. */
				cmpltr = 0;
				if ( *s == ',' ) {
					s++;
					name = s;
					while ( *s != ',' && *s != ' ' && *s != '\t' )
						s += 1;
					c = *s;
					*s = 0x00;
					if ( strcmp(name,"=") == 0 ) {
						cmpltr = 1;
						}
						else if ( strcmp(name,"<") == 0 ) {
						cmpltr = 2;
						}
						else if ( strcasecmp(name,"od") == 0 ) {
						cmpltr = 3;
						}
						else if ( strcasecmp(name,"tr") == 0 ) {
						cmpltr = 4;
						}
						else if ( strcmp(name,"<>") == 0 ) {
						cmpltr = 5;
						}
						else if ( strcmp(name,">=") == 0 ) {
						cmpltr = 6;
						}
						else if ( strcasecmp(name,"ev") == 0 ) {
						cmpltr = 7;
						}
						else
						as_bad("Unrecognized Shift/Extract/Deposit"
							"Condition: %s",name);
					*s = c;
				}
				opcode |= cmpltr << 13;
				continue;
			case '~':   /* bvb,bb conditions */
				cmpltr = 0;
				if ( *s == ',' ) {
					s++;
					if ( strncmp(s,"<",1) == 0 ) {
						cmpltr = 2;
						s++;
						}
						else if ( strncmp(s,">=",2) == 0 ) {
						cmpltr = 6;
						s += 2;
						}
						else
						as_bad("Unrecognized Bit Branch Condition: %c",*s);
				}
				opcode |= cmpltr << 13;
				continue;
			case 'V':   /* 5  bit immediate at 31 */
				getExpression(s);
				im5 = low_sign_unext(evaluateAbsolute(
						     the_insn.exp,0),5);
				opcode |= im5;
				s = expr_end;
				continue;
			case 'r':   /* 5  bit immediate at 31 */
						/* (unsigned value for the break instruction) */
				getExpression(s);
				im5 = evaluateAbsolute(the_insn.exp,0);
				if ( im5 > 31 ) {
					as_bad("Operand out of range. Was: %d. Should be"
						"[0..31]. Assuming %d.\n",im5,im5&0x1f);
					im5 = im5 & 0x1f;
				}
				opcode |= im5;
				s = expr_end;
				continue;
			case 'R':   /* 5  bit immediate at 15 */
/* (unsigned value for the ssm and rsm instruction) */
				getExpression(s);
				im5 = evaluateAbsolute(the_insn.exp,0);
				if ( im5 > 31 ) {
					as_bad("Operand out of range. Was: %d. Should be"
						"[0..31]. Assuming %d.\n",im5,im5&0x1f);
					im5 = im5 & 0x1f;
				}
				opcode |= im5 << 16;
				s = expr_end;
				continue;
			case 'i':   /* 11 bit immediate at 31 */
				getExpression(s);
				if ( the_insn.exp.X_seg == SEG_ABSOLUTE ) {
					im11 = low_sign_unext(evaluateAbsolute(
							the_insn.exp,0),11);
					opcode |= im11;
				}
				else {
					the_insn.code = 'i';
				}
				s = expr_end;
				continue;
			case 'j':   /* 14 bit immediate at 31 --- LO14 */
			{
				int field_selector = parse_L_or_R(s);
				switch (field_selector) {
				case 2:	/* found the field selector R`*/
				case 1:	/* found the field selector L`*/
					s += 2;  /* eat up L` or R` */
				case 0: /* not found */
					getExpression(s);
					break;
				default:
					as_bad("Bad field selector. Was: %.2s. Should be either L` or R`\n",s);
					break;
				}
				if ( the_insn.exp.X_seg == SEG_ABSOLUTE ) {
					im14 = low_sign_unext(
evaluateAbsolute(the_insn.exp,field_selector), 14);

/* I donot think the mask is necessary here  low_sign_unext() takes */
/* care of putting only 14 bits in im14 ! ...       090993 ... USV  */
/*					if (field_selector)
						opcode |= (im14 & 0x7ff);
					else
*/
					opcode |= im14;
				}
				else {
					the_insn.reloc = HPPA_RELOC_LO14;
					the_insn.code = 'j';
				}
				s = expr_end;
				continue;
			}  
			case 'z':	/* 17 bit branch displacement (non-pc-relative) */
				/* for be, ble --- BR17*/
				/* bl, ble  in absence of L` or R` can have */
				/* a 17 bit immmidiate number */
			{
				unsigned long w, w1, w2;
				int field_selector = parse_L_or_R(s);
				switch (field_selector) {
				case 2:	/* found the field selector R`*/
				case 1:	/* found the field selector L`*/
					s += 2;  /* eat up L` or R` */
				case 0: /* not found */
					getExpression(s);
					break;
				default:
					as_bad("Bad field selector. Was: %.2s." "Should be either L` or R`\n",s);
					break;
				}
				if ( the_insn.exp.X_seg == SEG_ABSOLUTE ) {
					im14 = sign_unext(
						evaluateAbsolute(the_insn.exp,field_selector),
						17);
					dis_assemble_17(im14>>2,&w1,&w2,&w);
					opcode |= ( ( w2 << 2 ) | ( w1 << 16 ) | w );
				}
				else {
					the_insn.reloc = HPPA_RELOC_BR17;
					the_insn.code = 'z';
				}
				s = expr_end;
				continue;
			}
			case 'k':   /* 21 bit immediate at 31 --- HI21 */
			{
				int field_selector = parse_L_or_R(s);
				switch (field_selector) {
				case 2:	/* found the field selector R`*/
				case 1:	/* found the field selector L`*/
					s += 2;  /* eat up L` or R` */
				case 0: /* not found */
					getExpression(s);
					break;
				default:
					as_bad("Bad field selector. Was: %.2s." "Should be either L` or R`\n",s);
					break;
				}
				if ( the_insn.exp.X_seg == SEG_ABSOLUTE ) {
					im21 = dis_assemble_21(
(evaluateAbsolute(the_insn.exp,field_selector) >> 11));
					opcode |=  im21 ;
				}
				else {
					the_insn.reloc = HPPA_RELOC_HI21;
					the_insn.code = 'k';
				}
				s = expr_end;
				continue;
  			}