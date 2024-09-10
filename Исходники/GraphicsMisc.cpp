BOOL GraphicsMisc::EnableFlip3D(HWND hWnd, BOOL bEnable)
{
#ifndef DWMWA_FLIP3D_POLICY
# define DWMWA_FLIP3D_POLICY 8
# define DWMFLIP3D_DEFAULT      0
# define DWMFLIP3D_EXCLUDEBELOW 1
# define DWMFLIP3D_EXCLUDEABOVE 2
#endif
	
	int nPolicy = bEnable ? DWMFLIP3D_DEFAULT : DWMFLIP3D_EXCLUDEBELOW;
	
	return DwmSetWindowAttribute(hWnd, DWMWA_FLIP3D_POLICY, &nPolicy, sizeof(nPolicy));
}