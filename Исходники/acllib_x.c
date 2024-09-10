void moveTo(int x, int y)
{
	ACL_ASSERT_BEGIN_PAINT;
	MoveToEx(g_hmemdc, x, y,NULL);
}