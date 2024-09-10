int GetLength(ScriptValue *sv, int strict) {
	if (sv->type == SCRIPT_NULL ||
		sv->type == SCRIPT_OBJECT) {
		if (!strict) return 1;
		return 2;
	}
	else if (sv->type == SCRIPT_INT) {
		return 2 + GetIntLength(sv->intVal);
	}
	else if (sv->type == SCRIPT_STRING) {
		return 1 + sv->stringVal->len + GetIntLength(sv->stringVal->len);
	}
	else if (sv->type == SCRIPT_LIST) {
		int len = 2;
		for (int i=0; i<sv->listVal->numVals; i++) {
			len += GetLength(sv->listVal->vals+i, strict);
		}
		return len;
	}
	else if (sv->type == SCRIPT_DICT) {
		int len = 2;
		for (int i=0; i<sv->dictVal->numEntries; i++) {
			len += GetLength(&sv->dictVal->entries[i].key, strict);
			len += GetLength(&sv->dictVal->entries[i].val, strict);
		}
		return len;
	}
	else if (sv->type == SCRIPT_DOUBLE) {
		if (strict) {
			char temp[30];
			_gcvt(sv->doubleVal, 14, temp);
			int len = (int)strlen(temp);
			return 1 + len + GetIntLength(len);
		}
		return 1+8;
	}
	else
		return 0;
}