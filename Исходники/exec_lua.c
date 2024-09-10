static int tek_lib_exec_child_sigjoin(lua_State *L, TUINT sig, TBOOL sigparent,
	TBOOL do_results)
{
	struct LuaExecChild *ctx = luaL_checkudata(L, 1, TEK_LIB_TASK_CLASSNAME);
	struct TExecBase *TExecBase = ctx->exec;
	struct TTask *self = TFindTask(TNULL), *task = ctx->task;
	union TTaskRequest *req = &self->tsk_Request;
	TBOOL abort = TFALSE;
	int nres = 0;
	if (!task)
		return 0;
	
	TDBPRINTF(TDB_TRACE,("child_join sig=%d sigparent=%d\n", sig, sigparent));
	
	/* signal task */
	TSignal(task, sig);
	/* prepare destroy request */
	self->tsk_ReqCode = TTREQ_DESTROYTASK;
	req->trq_Task.trt_Task = task;
	/* send to exec */
	TPutMsg(TExecBase->texb_ExecPort, &self->tsk_SyncPort, self);
	for (;;)
	{
		/* wait for return of request or receiving abort ourselves: */
		TUINT sig = TWait(TTASK_SIG_SINGLE | TTASK_SIG_ABORT);
		if (sig & TTASK_SIG_SINGLE)
			break;
		if (sig & TTASK_SIG_ABORT)
		{
			/* forward to child task */
			TSignal(task, TTASK_SIG_ABORT);
			if (sigparent)
			{
				/* also forward to own parent task */
				struct LuaExecTask *parent = getparent(TExecBase);
				if (parent)
					TSignal(parent->task, TTASK_SIG_ABORT);
				abort = TTRUE;
			}
		}
	}
	/* take delivery of replied destroy request */
	TGetMsg(&self->tsk_SyncPort);
	/* free task */	
	TFreeTask(task);
	
	ctx->task = TNULL;
	tek_lib_exec_freectxargs(ctx);
	if (!abort && do_results)
	{
		int i;
		nres = ctx->numres + 1;
		lua_pushboolean(L, ctx->luastatus == 0);
		for (i = 0; i < ctx->numres; ++i)
			lua_pushlstring(L, ctx->results[i].arg, ctx->results[i].len);
	}
	tek_lib_exec_freeargs(TExecBase, ctx->results, ctx->numres);
	luaL_unref(L, lua_upvalueindex(1), ctx->ref);
	if (abort)
		luaL_error(L, "received abort signal");
	return nres;
}