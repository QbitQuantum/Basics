/* our exit handler */
void win_exit(void)
{
	/* if we didn't exit through gs_exit() then do so now */
	if (win_init)
		gs_exit(0);

	fcloseall();
	DestroyWindow(hwndeasy);
}