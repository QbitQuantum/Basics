/* calcPerform
 *
 * Evalutate the postfix expression
 */
epicsShareFunc long
    calcPerform(double *parg, double *presult, const char *pinst)
{
    double stack[CALCPERFORM_STACK+1];	/* zero'th entry not used */
    double *ptop;			/* stack pointer */
    double top; 			/* value from top of stack */
    epicsInt32 itop;			/* integer from top of stack */
    epicsUInt32 utop;			/* unsigned integer from top of stack */
    int op;
    int nargs;

    /* initialize */
    ptop = stack;

    /* RPN evaluation loop */
    while ((op = *pinst++) != END_EXPRESSION){
	switch (op){

	case LITERAL_DOUBLE:
	    memcpy(++ptop, pinst, sizeof(double));
	    pinst += sizeof(double);
	    break;

	case LITERAL_INT:
	    memcpy(&itop, pinst, sizeof(epicsInt32));
	    *++ptop = itop;
	    pinst += sizeof(epicsInt32);
	    break;

	case FETCH_VAL:
	    *++ptop = *presult;
	    break;

	case FETCH_A:
	case FETCH_B:
	case FETCH_C:
	case FETCH_D:
	case FETCH_E:
	case FETCH_F:
	case FETCH_G:
	case FETCH_H:
	case FETCH_I:
	case FETCH_J:
	case FETCH_K:
	case FETCH_L:
	    *++ptop = parg[op - FETCH_A];
	    break;

	case STORE_A:
	case STORE_B:
	case STORE_C:
	case STORE_D:
	case STORE_E:
	case STORE_F:
	case STORE_G:
	case STORE_H:
	case STORE_I:
	case STORE_J:
	case STORE_K:
	case STORE_L:
	    parg[op - STORE_A] = *ptop--;
	    break;

	case CONST_PI:
	    *++ptop = PI;
	    break;

	case CONST_D2R:
	    *++ptop = PI/180.;
	    break;

	case CONST_R2D:
	    *++ptop = 180./PI;
	    break;

	case UNARY_NEG:
	    *ptop = - *ptop;
	    break;

	case ADD:
	    top = *ptop--;
	    *ptop += top;
	    break;

	case SUB:
	    top = *ptop--;
	    *ptop -= top;
	    break;

	case MULT:
	    top = *ptop--;
	    *ptop *= top;
	    break;

	case DIV:
	    top = *ptop--;
	    *ptop /= top;
	    break;

	case MODULO:
	    itop = (epicsInt32) *ptop--;
	    if (itop)
		*ptop = (epicsInt32) *ptop % itop;
	    else
		*ptop = epicsNAN;
	    break;

	case POWER:
	    top = *ptop--;
	    *ptop = pow(*ptop, top);
	    break;

	case ABS_VAL:
	    *ptop = fabs(*ptop);
	    break;

	case EXP:
	    *ptop = exp(*ptop);
	    break;

	case LOG_10:
	    *ptop = log10(*ptop);
	    break;

	case LOG_E:
	    *ptop = log(*ptop);
	    break;

	case MAX:
	    nargs = *pinst++;
	    while (--nargs) {
		top = *ptop--;
		if (*ptop < top || isnan(top))
		    *ptop = top;
	    }
	    break;

	case MIN:
	    nargs = *pinst++;
	    while (--nargs) {
		top = *ptop--;
		if (*ptop > top || isnan(top))
		    *ptop = top;
	    }
	    break;

	case SQU_RT:
	    *ptop = sqrt(*ptop);
	    break;

	case ACOS:
	    *ptop = acos(*ptop);
	    break;

	case ASIN:
	    *ptop = asin(*ptop);
	    break;

	case ATAN:
	    *ptop = atan(*ptop);
	    break;

	case ATAN2:
	    top = *ptop--;
	    *ptop = atan2(top, *ptop);	/* Ouch!: Args backwards! */
	    break;

	case COS:
	    *ptop = cos(*ptop);
	    break;

	case SIN:
	    *ptop = sin(*ptop);
	    break;

	case TAN:
	    *ptop = tan(*ptop);
	    break;

	case COSH:
	    *ptop = cosh(*ptop);
	    break;

	case SINH:
	    *ptop = sinh(*ptop);
	    break;

	case TANH:
	    *ptop = tanh(*ptop);
	    break;

	case CEIL:
	    *ptop = ceil(*ptop);
	    break;

	case FLOOR:
	    *ptop = floor(*ptop);
	    break;

	case FINITE:
	    nargs = *pinst++;
	    top = finite(*ptop);
	    while (--nargs) {
		--ptop;
		top = top && finite(*ptop);
	    }
	    *ptop = top;
	    break;

	case ISINF:
	    *ptop = isinf(*ptop);
	    break;

	case ISNAN:
	    nargs = *pinst++;
	    top = isnan(*ptop);
	    while (--nargs) {
		--ptop;
		top = top || isnan(*ptop);
	    }
	    *ptop = top;
	    break;

	case NINT:
	    top = *ptop;
	    *ptop = (epicsInt32) (top >= 0 ? top + 0.5 : top - 0.5);
	    break;

	case RANDOM:
	    *++ptop = calcRandom();
	    break;

	case REL_OR:
	    top = *ptop--;
	    *ptop = *ptop || top;
	    break;

	case REL_AND:
	    top = *ptop--;
	    *ptop = *ptop && top;
	    break;

	case REL_NOT:
	    *ptop = ! *ptop;
	    break;

        /* For bitwise operations on values with bit 31 set, double values
         * must first be cast to unsigned to correctly set that bit; the
         * double value must be negative in that case. The result must be
         * cast to a signed integer before converting to the double result.
         */

	case BIT_OR:
	    utop = *ptop--;
	    *ptop = (epicsInt32) ((epicsUInt32) *ptop | utop);
	    break;

	case BIT_AND:
	    utop = *ptop--;
	    *ptop = (epicsInt32) ((epicsUInt32) *ptop & utop);
	    break;

	case BIT_EXCL_OR:
	    utop = *ptop--;
	    *ptop = (epicsInt32) ((epicsUInt32) *ptop ^ utop);
	    break;

	case BIT_NOT:
	    utop = *ptop;
	    *ptop = (epicsInt32) ~utop;
	    break;

        /* The shift operators use signed integers, so a right-shift will
         * extend the sign bit into the left-hand end of the value. The
         * double-casting through unsigned here is important, see above.
         */

	case RIGHT_SHIFT:
	    utop = *ptop--;
	    *ptop = ((epicsInt32) (epicsUInt32) *ptop) >> (utop & 31);
	    break;

	case LEFT_SHIFT:
	    utop = *ptop--;
	    *ptop = ((epicsInt32) (epicsUInt32) *ptop) << (utop & 31);
	    break;

	case NOT_EQ:
	    top = *ptop--;
	    *ptop = *ptop != top;
	    break;

	case LESS_THAN:
	    top = *ptop--;
	    *ptop = *ptop < top;
	    break;

	case LESS_OR_EQ:
	    top = *ptop--;
	    *ptop = *ptop <= top;
	    break;

	case EQUAL:
	    top = *ptop--;
	    *ptop = *ptop == top;
	    break;

	case GR_OR_EQ:
	    top = *ptop--;
	    *ptop = *ptop >= top;
	    break;

	case GR_THAN:
	    top = *ptop--;
	    *ptop = *ptop > top;
	    break;

	case COND_IF:
	    if (*ptop-- == 0.0 &&
		cond_search(&pinst, COND_ELSE)) return -1;
	    break;

	case COND_ELSE:
	    if (cond_search(&pinst, COND_END)) return -1;
	    break;

	case COND_END:
	    break;

	default:
	    errlogPrintf("calcPerform: Bad Opcode %d at %p\n", op, pinst-1);
	    return -1;
	}
    }

    /* The stack should now have one item on it, the expression value */
    if (ptop != stack + 1)
	return -1;
    *presult = *ptop;
    return 0;
}