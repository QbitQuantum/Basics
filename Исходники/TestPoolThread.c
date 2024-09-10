int TestPoolThread(int argc, char* argv[])
{
	TP_POOL* pool;

	pool = CreateThreadpool(NULL);

	SetThreadpoolThreadMinimum(pool, 8); /* default is 0 */
	SetThreadpoolThreadMaximum(pool, 64); /* default is 500 */

	CloseThreadpool(pool);

	return 0;
}