/* Format of _o:  column1 [ASC|DESC], column2 [ASC|DESC], ... */
int dbt_parse_orderbyclause(db_key_t **_o_k, char **_o_op, int *_o_n, db_key_t _o)
{
	char *_po, *_ps, *_pe;
	char _c = '\0';
	char _d[8];
	int _n;
	int _i;
	str *_s;

	/* scan _o, count ',' -> upper bound for no of columns */
	_n = 1;
	for (_i=0; _i < _o->len; _i++)
		if (_o->s[_i] == ',')
			_n++;

    /* *_o_k will include the db_key_ts, the strs, a copy of _o and \0 */
	*_o_k = pkg_malloc((sizeof(db_key_t)+sizeof(str)) * _n + _o->len + 1);
	if (!*_o_k)
		return -1;
	_s = (str *)((char *)(*_o_k) + sizeof(db_key_t) * _n);
	for (_i=0; _i < _n; _i++)
	    (*_o_k)[_i] = &_s[_i];
	_po = (char *)(*_o_k) + (sizeof(db_key_t) + sizeof(str)) * _n;
	memcpy(_po, _o->s, _o->len);
	*(_po+_o->len) = '\0';

	*_o_op = pkg_malloc(sizeof(char) * _n);
	if (!*_o_op)
	{
		pkg_free(*_o_k);
		return -1;
	}

	*_o_n = 0;
	_ps = _po;
	while (*_o_n < _n)
	{
		while (*_ps == ' ') _ps++;
		if (*_ps == '\0')
			break;
		strcpy(_d, " \f\n\r\t\v,"); /* isspace() and comma */
		if (*_ps == '"' || *_ps == '\'') /* detect quote */
		{
			_d[0] = *_ps;
			_d[1] = '\0';
			_ps++;
		}
		_pe = strpbrk(_ps, _d); /* search quote, space, comma or eos */
		if (!_pe && _d[0] == ' ') /* if token is last token in string */
			_pe = _po + _o->len; /* point to end of string */
		if (! _pe) /* we were looking for quote but found none */
			goto parse_error;

		/* _ps points to start of column-name,
		 * _pe points after the column-name, on quote, space, comma, or '\0' */
		_c = *_pe;
		*_pe = '\0';
		(*_o_k)[*_o_n]->s = _ps;
		(*_o_k)[*_o_n]->len = _pe - _ps;
		(*_o_op)[*_o_n] = '<'; /* default */
		(*_o_n)++;

		if (_c == '\0')
			break;

		/* go beyond current token */
		_ps = _pe + 1;
		if (_c == ',')
			continue;
		while (*_ps == ' ') _ps++;
		if (*_ps == ',')
		{
			_ps++;
			continue;
		}
		if (*_ps == '\0')
			break;

		/* there is ASC OR DESC qualifier */
		if (strncasecmp(_ps, "DESC", 4) == 0)
		{
			(*_o_op)[*_o_n-1] = '>';
			_ps += 4;
		} else if (strncasecmp(_ps, "ASC", 3) == 0)
		{
			_ps += 3;
		} else goto parse_error;

		/* point behind qualifier */
		while (*_ps == ' ') _ps++;
		if (*_ps == ',')
		{
			_ps++;
			continue;
		}
		if (*_ps == '\0')
			break;
		goto parse_error;
	}

	if (*_ps != '\0' && _c != '\0')   /* that means more elements than _tbc->nrcols */
		goto parse_error;

	if (*_o_n == 0) /* there weren't actually any columns */
	{
		pkg_free(*_o_k);
		pkg_free(*_o_op);
		*_o_op = NULL;
		*_o_k = NULL;
		return 0; /* return success anyway */
	}

	return 0;

parse_error:
	pkg_free(*_o_k);
	pkg_free(*_o_op);
	*_o_op = NULL;
	*_o_k = NULL;
	*_o_n = 0;
	return -1;
}