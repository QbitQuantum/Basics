void input_task(coro_input_t::self_t& self, input_args* pia)
{
	while (true)
	{
		printf("number: ");
		if (!scanf_s("%d", pia->target))
		{
			b_quit = true;
			return;
		}
    
		self.yield();
	}

	printf("ERROR: should not reach the end of input function\n");
}