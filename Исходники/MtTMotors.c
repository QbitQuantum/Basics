void ExecutaOrdre(void) {
	switch (OrdreAct.Opcode) {
		case M_LIN:
			MtSetPWM(M_ESQUERRA, GetVelocitatEsquerra(), GetDireccio());
			MtSetPWM(M_DRET, GetVelocitatDreta(), GetDireccio());
			if (GetDireccio() == M_DIR_ENDARRERA) V = -GetV(GetVelocitatDreta()); 
			else V = GetV(GetVelocitatDreta());
			W = 0;
			// LS_USB_printf("LIN V = %f, W = %f\n\r", V, W);
			break;
		case M_GD:
			// Si el radi és menor que la meitat de la distància entre rodes, cal oposar els motors
			// Si no, sempre vas endavant
			if (OrdreAct.Radi < RADI_COTXE) {
				MtSetPWM(M_ESQUERRA, GetRadi(), M_DIR_ENDAVANT);
				MtSetPWM(M_DRET, GetRadi(), M_DIR_ENDARRERA);
				W = -GetW(GetRadi()); V = 0;
				// LS_USB_printf("GD V = %f, W = %f\n\r", V, W);
			} else {
				MtSetPWM(M_ESQUERRA, GetVelocitatEsquerra(), GetDireccio());
				MtSetPWM(M_DRET, GetRadiInterior(GetVelocitatDreta()), GetDireccio());
				if (GetDireccio() == M_DIR_ENDARRERA) V = -GetV(GetVelocitatEsquerra()); 
				else V = GetV(GetVelocitatEsquerra());
				NvSetOmega(GetVelocitatEsquerra(), GetDireccio(), GetRadiInterior(GetVelocitatDreta()), GetDireccio());
			}
			break;
		case M_GE:
			// Si el radi és menor que la meitat de la distància entre rodes, cal oposar els motors
			// Si no, sempre vas endavant
			if (OrdreAct.Radi < RADI_COTXE) {
				MtSetPWM(M_ESQUERRA, GetRadi(), M_DIR_ENDARRERA);
				MtSetPWM(M_DRET, GetRadi(), M_DIR_ENDAVANT);
				W = GetW(GetRadi()); V = 0;
				// LS_USB_printf("GE V = %f, W = %f\n\r", V, W);
			} else {
				MtSetPWM(M_ESQUERRA, GetRadiInterior(GetVelocitatEsquerra()), GetDireccio());
				MtSetPWM(M_DRET, GetVelocitatDreta(), GetDireccio());
				if (GetDireccio() == M_DIR_ENDARRERA) V = -GetV(GetVelocitatDreta()); 
				else V = GetV(GetVelocitatDreta());
				NvSetOmega(GetRadiInterior(GetVelocitatEsquerra()), GetDireccio(), GetVelocitatDreta(), GetDireccio());
			}
			break;
	}
}