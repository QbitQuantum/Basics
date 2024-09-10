char *
atom2sql(atom *a)
{
	int ec = a->tpe.type->eclass;
	char buf[BUFSIZ];

	if (a->data.vtype == TYPE_str && EC_INTERVAL(ec))
		ec = EC_STRING; 
	/* todo handle NULL's early */
	switch (ec) {
	case EC_BIT:
		assert( a->data.vtype == TYPE_bit);
		if (a->data.val.btval)
			return _STRDUP("true");
		return _STRDUP("false");
	case EC_CHAR:
	case EC_STRING:
		assert (a->data.vtype == TYPE_str);
		if (a->data.val.sval)
			sprintf(buf, "'%s'", a->data.val.sval);
		else
			sprintf(buf, "NULL");
		break;
	case EC_BLOB:
		/* TODO atom to string */
		break;
	case EC_MONTH: 
	case EC_SEC: {
		lng v;
		switch (a->data.vtype) {
		case TYPE_lng:
			v = a->data.val.lval;
			break;
		case TYPE_int:
			v = a->data.val.ival;
			break;
		case TYPE_sht:
			v = a->data.val.shval;
			break;
		case TYPE_bte:
			v = a->data.val.btval;
			break;
		default:
			v = 0;
			break;
		}
		switch (a->tpe.digits) {
		case 1:		/* year */
			v /= 12;
			break;
		case 2:		/* year to month */
		case 3:		/* month */
			break;
		case 4:		/* day */
			v /= 60 * 60 * 24;
			break;
		case 5:		/* day to hour */
		case 8:		/* hour */
			v /= 60 * 60;
			break;
		case 6:		/* day to minute */
		case 9:		/* hour to minute */
		case 11:	/* minute */
			v /= 60;
			break;
		case 7:		/* day to second */
		case 10:	/* hour to second */
		case 12:	/* minute to second */
		case 13:	/* second */
			break;
		}
		if (a->tpe.digits < 4) {
			sprintf(buf, LLFMT, v);
		} else {
			lng sec = v/1000;
			lng msec = v%1000;
			sprintf(buf, LLFMT "." LLFMT, sec, msec);
		}
		break;
	}
	case EC_NUM:
		switch (a->data.vtype) {
#ifdef HAVE_HGE
		case TYPE_hge:
		{	char *_buf = buf;
			int _bufsiz = BUFSIZ;
			hgeToStr(&_buf, &_bufsiz, &a->data.val.hval);
			break;
		}
#endif
		case TYPE_lng:
			sprintf(buf, LLFMT, a->data.val.lval);
			break;
		case TYPE_int:
			sprintf(buf, "%d", a->data.val.ival);
			break;
		case TYPE_sht:
			sprintf(buf, "%d", a->data.val.shval);
			break;
		case TYPE_bte:
			sprintf(buf, "%d", a->data.val.btval);
			break;
		default:
			break;
		}
		break;
	case EC_DEC: {
#ifdef HAVE_HGE
		hge v = 0;
#else
		lng v = 0;
#endif
		switch (a->data.vtype) {
#ifdef HAVE_HGE
		case TYPE_hge: v = a->data.val.hval; break;
#endif
		case TYPE_lng: v = a->data.val.lval; break;
		case TYPE_int: v = a->data.val.ival; break;
		case TYPE_sht: v = a->data.val.shval; break;
		case TYPE_bte: v = a->data.val.btval; break;
		default: break;
		}
		return decimal_to_str(v, &a->tpe);
	}
	case EC_FLT:
		if (a->data.vtype == TYPE_dbl)
			sprintf(buf, "%f", a->data.val.dval);
		else
			sprintf(buf, "%f", a->data.val.fval);
		break;
	case EC_TIME:
	case EC_DATE:
	case EC_TIMESTAMP:
		if (a->data.vtype == TYPE_str) {
			if (a->data.val.sval)
				sprintf(buf, "%s '%s'", a->tpe.type->sqlname, 
					a->data.val.sval);
			else
				sprintf(buf, "NULL");
		}
		break;
        default:
                snprintf(buf, BUFSIZ, "atom2sql(TYPE_%d) not implemented", a->data.vtype);
	}
	return _STRDUP(buf);
}