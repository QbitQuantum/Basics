AndGate::~AndGate()
{
	GdiplusShutdown(g_GdiPlusTokenBoxData_AND);
}