/**
 * 実行中スレッドの終了
 */
SQRESULT
Thread::global_exit(HSQUIRRELVM v)
{
	Thread *th = getCurrentThread(v);
	if (!th) {
		return ERROR_NOTHREAD(v);
	}
	th->exit(v);
	return sq_suspendvm(v);
}