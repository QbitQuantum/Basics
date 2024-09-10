//-------------------------------------------------------------
//------------------------------ 设置系统启动毫秒
uint64	setSystemTick64	()
{
	g_uSystemTick64 = getTickCount64();

	return g_uSystemTick64;
}