int coroutine_init(struct coroutine *co)
{
	if (leader.fiber == NULL) {
		leader.fiber = ConvertThreadToFiber(&leader);
		if (leader.fiber == NULL)
			return -1;
	}

	co->fiber = CreateFiber(0, &coroutine_trampoline, co);
	co->ret = 0;
	if (co->fiber == NULL)
		return -1;

	return 0;
}