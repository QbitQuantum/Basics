/*
 * ppb_MS_init_msq()
 *
 * Initialize a microsequence - see macros in ppb_msq.h
 *
 */
int
ppb_MS_init_msq(struct ppb_microseq *msq, int nbparam, ...)
{
	int i;
	int param, ins, arg, type;
	__va_list p_list;

	__va_start(p_list, nbparam);

	for (i=0; i<nbparam; i++) {
		/* retrieve the parameter descriptor */
		param = __va_arg(p_list, int);

		ins  = MS_INS(param);
		arg  = MS_ARG(param);
		type = MS_TYP(param);

		/* check the instruction position */
		if (arg >= PPB_MS_MAXARGS)
			panic("%s: parameter out of range (0x%x)!",
				__func__, param);

#if 0
		kprintf("%s: param = %d, ins = %d, arg = %d, type = %d\n", 
			__func__, param, ins, arg, type);
#endif

		/* properly cast the parameter */
		switch (type) {
		case MS_TYP_INT:
			msq[ins].arg[arg].i = __va_arg(p_list, int);
			break;

		case MS_TYP_CHA:
			msq[ins].arg[arg].i = (int)__va_arg(p_list, int);
			break;

		case MS_TYP_PTR:
			msq[ins].arg[arg].p = __va_arg(p_list, void *);
			break;

		case MS_TYP_FUN:
			msq[ins].arg[arg].f = __va_arg(p_list, void *);
			break;

		default:
			panic("%s: unknown parameter (0x%x)!", __func__,
				param);
		}
	}

	return (0);
}