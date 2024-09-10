void ScriptFindWindow(ScriptValue &s, ScriptValue *args) {
	wchar_t *p1 = 0, *p2 = 0;
	if (args[0].stringVal->len) {
		p1 = UTF8toUTF16Alloc(args[0].stringVal->value);
	}
	if (args[1].stringVal->len) {
		p2 = UTF8toUTF16Alloc(args[1].stringVal->value);
	}
	__int64 res = (__int64)FindWindowExW((HWND)args[2].intVal, (HWND)args[3].intVal, p1, p2);
	if (res) {
		CreateIntValue(s, res);
	}
	if (p1) free(p1);
	if (p2) free(p2);
}