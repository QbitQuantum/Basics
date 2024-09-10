static void
global_init(void)
{
	InitOnceExecuteOnce(&global_init_once,
			    global_init1,
			    nullptr, nullptr);
}