LRESULT ControlMediaPlayer::Evento_Mouse_Movimiento(const int cX, const int cY, const UINT wParam) {
	UltimoMovimiento = GetTickCount();
	if (EstaEnPantallaCompleta() == true) {
		DWL::SO::DWLMouse::Visible(TRUE);
		RECT  Recta;
		POINT MousePos;
		DWL::SO::DWLMouse::ObtenerPosicion(&MousePos);
		HRGN RMP = CreateRectRgn(0, 0, 0, 0);
		GetWindowRgn(Sistema.App.ControlesMP.hWnd(), RMP);
		
		GetWindowRect(_hWnd, &Recta);
		int x;
		if (Recta.left > 0) x = ((Recta.right - Recta.left) - CONTROLESMP_ANCHO) / 2;
		else				x = (((Recta.right + Recta.left) + CONTROLESMP_ANCHO) / 2) - CONTROLESMP_ANCHO;
		if (ControlesMP_Abajo == true) {
			int y = (Recta.bottom - Recta.top) - CONTROLESMP_ALTO;
			int r = OffsetRgn(RMP, x, y);
			if (PtInRegion(RMP, MousePos.x, MousePos.y) == TRUE) {
				Sistema.App.ControlesMP.Mostrar(_hWnd, ControlesMP_Abajo);
			}
			else {
				Sistema.App.ControlesMP.Ocultar(hWnd());
			}
		}
		else {
			OffsetRgn(RMP, x, 0);
			if (PtInRegion(RMP, MousePos.x, MousePos.y) == TRUE) {
				Sistema.App.ControlesMP.Mostrar(_hWnd, ControlesMP_Abajo);
			}
			else {
				Sistema.App.ControlesMP.Ocultar(hWnd());
			}
		}
		DeleteObject(RMP);
	}
	return 0;
}