static void APIENTRY SetGammaRamp (Uint16 *redtable, Uint16 *greentable, Uint16 *bluetable)
#endif
{
#ifndef unix
	SetDeviceGammaRamp(m_hDC, ramp);
#else
	SDL_SetGammaRamp(redtable, greentable, bluetable);
#endif
}