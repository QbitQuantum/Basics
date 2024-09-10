int json_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	int i;
	if(((struct json_data*)log->moduleData)->followingKeyVal == 1) {
		_ftprintf(log->file, _T(","));
	}

	_ftprintf(log->file, _T("\n%*s\"%s\": \""), log->indentLevel * 3, _T(" "), key);

	for(i=0; value[i]; i++) {
		switch(value[i]) {
			case _T('"'):
				_ftprintf(log->file, _T("%s"), _T("\""));
				break;
			case _T('\\'):
				_ftprintf(log->file, _T("%s"), _T("\\\\"));
				break;
			case _T('/'):
				_ftprintf(log->file, _T("%s"), _T("\\/"));
				break;
			case _T('\b'):
				_ftprintf(log->file, _T("%s"), _T("\\b"));
				break;
			case _T('\f'):
				_ftprintf(log->file, _T("%s"), _T("\\f"));
				break;
			case _T('\n'):
				_ftprintf(log->file, _T("%s"), _T("\\n"));
				break;
			case _T('\r'):
				_ftprintf(log->file, _T("%s"), _T("\\r"));
				break;
			case _T('\t'):
				_ftprintf(log->file, _T("%s"), _T("\\t"));
				break;
			default:
				if(__isascii(value[i])) {
					_ftprintf(log->file, _T("%c"), value[i]);
				} else {
					_ftprintf(log->file, _T("%04d"), value[i]);
				}
		}
	}

	_ftprintf(log->file, _T("\""));

	((struct json_data*)log->moduleData)->followingKeyVal = 1;
	return 0;
}