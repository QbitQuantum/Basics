void task_c_remove()
{
	asm("cli");
	task_destroy(taskc_tid);
	asm("sti");
	memset(StackC, 0, sizeof(StackC));
	settextcolor(0xf,0x0);
	screen_pos_putch(' ', 70, 0);
}