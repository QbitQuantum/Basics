void CWinParent::LoadAccel(wchar_t * accel) {
	hAccel = LoadAccelerators(GetInstance(), accel);
}