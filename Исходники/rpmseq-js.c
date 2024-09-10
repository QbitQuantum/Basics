static JSBool
rpmseq_getprop(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmseqClass, NULL);
    DB_SEQUENCE * seq = ptr;
    jsval idval;
    JS_IdToValue(cx, id, &idval);
    jsint tiny = JSVAL_TO_INT(idval);
    jsdouble d = 0;
    int ret;

    /* XXX the class has ptr == NULL, instances have ptr != NULL. */
    if (ptr == NULL)
	return JS_TRUE;

    switch (tiny) {
    case _DEBUG:
	*vp = INT_TO_JSVAL(_debug);
	break;
    case _DB:
    {	DB * _db = NULL;
	if ((ret = seq->get_db(seq, &_db)) != 0) {
	    *vp = JSVAL_VOID;
	    break;
	}
	*vp = _db->app_private ? OBJECT_TO_JSVAL(_db->app_private) : JSVAL_NULL;
    }	break;
    case _KEY:
    {	DBT _k = {0};
	if ((ret = seq->get_key(seq, &_k)) != 0) {
	    *vp = JSVAL_VOID;
	    break;
	}
	*vp = _k.data
		? STRING_TO_JSVAL(JS_NewStringCopyZ(cx, _k.data)) : JSVAL_NULL;
    }	break;
    case _CACHESIZE:
    {	int32_t _i = 0;
	if ((ret = seq->get_cachesize(seq, &_i)) != 0) {
	    *vp = JSVAL_VOID;
	    break;
	}
	d = _i;
	if (!JS_NewNumberValue(cx, d, vp))
	    *vp = JSVAL_FALSE;
    }	break;
    case _FLAGS:
    {	uint32_t _u = 0;
	if ((ret = seq->get_flags(seq, &_u)) != 0) {
	    *vp = JSVAL_VOID;
	    break;
	}
	d = _u;
	if (!JS_NewNumberValue(cx, d, vp))
	    *vp = JSVAL_FALSE;
    }	break;
    case _RANGEMIN:
    case _RANGEMAX:
    {	db_seq_t _min = 0;
	db_seq_t _max = 0;

	if ((ret = seq->get_range(seq, &_min, &_max)) != 0) {
	    *vp = JSVAL_VOID;
	    break;
	}
	switch (tiny) {
	case _RANGEMIN:	d = _min;	break;
	case _RANGEMAX:	d = _max;	break;
	}
	if (!JS_NewNumberValue(cx, d, vp))
	    *vp = JSVAL_FALSE;
    }	break;
    case _ST_WAIT:
    case _ST_NOWAIT:
    case _ST_CURRENT:
    case _ST_VALUE:
    case _ST_LAST_VALUE:
    case _ST_MIN:
    case _ST_MAX:
    case _ST_CACHESIZE:
    case _ST_FLAGS:
    {	DB_SEQUENCE_STAT * sp = NULL;
	uint32_t _flags = 0;

	if ((ret = seq->stat(seq, &sp, _flags)) != 0) {
	    *vp = JSVAL_VOID;
	    break;
	}
	switch (tiny) {
	case _ST_WAIT:		d = sp->st_wait;	break;
	case _ST_NOWAIT:	d = sp->st_nowait;	break;
	case _ST_CURRENT:	d = sp->st_current;	break;
	case _ST_VALUE:		d = sp->st_value;	break;
	case _ST_LAST_VALUE:	d = sp->st_last_value;	break;
	case _ST_MIN:		d = sp->st_min;		break;
	case _ST_MAX:		d = sp->st_max;		break;
	case _ST_CACHESIZE:	d = sp->st_cache_size;	break;
	case _ST_FLAGS:		d = sp->st_flags;	break;
	}
	sp = _free(sp);
	if (!JS_NewNumberValue(cx, d, vp))
	    *vp = JSVAL_FALSE;
    }	break;
    default:
	break;
    }

    return JS_TRUE;
}