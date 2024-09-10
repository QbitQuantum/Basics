int main(int argc, WCHAR* argv[])
{
	fiberA = CreateFiber(0, (LPFIBER_START_ROUTINE)FiberA, (LPVOID)0);
	fiberB = CreateFiber(0, (LPFIBER_START_ROUTINE)FiberB, (LPVOID)0);
	mainFiber = ConvertThreadToFiber(NULL);
	for (int i = 0; i < 20; i++) {
		SwitchToFiber(fiberA);
		SwitchToFiber(fiberB);
		Sleep(100);
	}
	return 0;
}