BOOL TabletBase::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam) 
{
	PACKET          pkt;             /* the current packet */
	HDC             hDC;             /* handle for Device Context */
	PAINTSTRUCT     psPaint;         /* the paint structure */

	//渡された message から、イベントの種類を解析する
	switch(msg){

	case WM_PAINT: { /* Paint the window */
		int ZAngle;         /* Raw Altitude */
		UINT Thata;         /* Raw Azimuth */
		double ZAngle2;     /* Adjusted Altitude */
		double Thata2;      /* Adjusted Azimuth */

		char szOutput[128]; /* String for outputs */

		if (m_TiltSupport) {                             
			/* 
			wintab.h defines .orAltitude 
			as a UINT but documents .orAltitude 
			as positive for upward angles 
			and negative for downward angles.
			WACOM uses negative altitude values to 
			show that the pen is inverted; 
			therefore we cast .orAltitude as an 
			(int) and then use the absolute value. 
			*/
			ZAngle  = (int)m_ortNew.orAltitude;
			ZAngle2 = m_altAdjust - (double)abs(ZAngle)/m_altFactor;
			/* adjust azimuth */
			Thata  = m_ortNew.orAzimuth;
			Thata2 = (double)Thata/m_aziFactor;
			/* get the length of the diagnal to draw */  
			m_Z1Angle.x = (int)(ZAngle2*sin(Thata2));
			m_Z1Angle.y = (int)(ZAngle2*cos(Thata2));
		}
		else {
			m_Z1Angle.x = 0;
			m_Z1Angle.y = 0;
		}

		if (hDC = BeginPaint(m_hWnd, &psPaint)) {

			/* write raw tilt info */ 
			if (m_TiltSupport) {                             
				wsprintf((LPSTR)szOutput,"Tilt: %03i, Thata: %04u\0",
					ZAngle,Thata);
			}
			else {
				strcpy(szOutput,"Tilt not supported.");
			}
			DrawText(hDC,szOutput,strlen(szOutput),&m_rcInfoTilt,DT_LEFT);

			/* write current cursor name */ 
			gpWTInfoA(WTI_CURSORS + m_curNew, CSR_NAME, szOutput);
			DrawText(hDC,szOutput,strlen(szOutput),&m_rcInfoName,DT_LEFT);

			/* write tablet name */
			gpWTInfoA(WTI_DEVICES, DVC_NAME, szOutput);
			DrawText(hDC,szOutput,strlen(szOutput),&m_rcInfoGen,DT_LEFT);

			/* draw circle based on tablet pressure */
			Ellipse(hDC, m_ptNew.x - m_prsNew, m_ptNew.y - m_prsNew,
				m_ptNew.x + m_prsNew, m_ptNew.y + m_prsNew);

			/* draw a line based on tablet tilt */
			MoveTo(hDC, m_ptNew.x, m_ptNew.y);
			LineTo(hDC, m_ptNew.x + m_Z1Angle.x, m_ptNew.y - m_Z1Angle.y);

			/* draw CROSS based on tablet position */ 
			MoveTo(hDC, m_ptNew.x - 20, m_ptNew.y     );
			LineTo(hDC, m_ptNew.x + 20, m_ptNew.y     );
			MoveTo(hDC, m_ptNew.x     , m_ptNew.y - 20);
			LineTo(hDC, m_ptNew.x     , m_ptNew.y + 20);
			EndPaint(m_hWnd, &psPaint);
		}
		break;
				   }

	case WT_PACKET: /* A packet is waiting from WINTAB */
		if (gpWTPacket((HCTX)lParam, wParam, &pkt)) {

			/* old co-ordinates used for comparisons */
			POINT 		ptOld = m_ptNew; 
			UINT  		prsOld = m_prsNew;
			UINT  		curOld = m_curNew;
			ORIENTATION ortOld = m_ortNew;

			/* save new co-ordinates */
			m_ptNew.x = (UINT)pkt.pkX;
			m_ptNew.y = (UINT)pkt.pkY;
			m_curNew = pkt.pkCursor;
			m_prsNew = pkt.pkNormalPressure;
			m_ortNew = pkt.pkOrientation;

			/* If the visual changes update the main graphic */
			if (m_ptNew.x != ptOld.x ||
				m_ptNew.y != ptOld.y ||
				m_prsNew != prsOld ||
				m_ortNew.orAzimuth != ortOld.orAzimuth ||
				m_ortNew.orAltitude != ortOld.orAltitude ||
				m_ortNew.orTwist != ortOld.orTwist) {                                     
					InvalidateRect(m_hWnd, &m_rcDraw, TRUE);
			}
			/* if the displayed data changes update the text */
			if (m_ortNew.orAzimuth != ortOld.orAzimuth ||
				m_ortNew.orAltitude != ortOld.orAltitude ||
				m_ortNew.orTwist != ortOld.orTwist) {
					InvalidateRect(m_hWnd, &m_rcInfoTilt, TRUE);
			}
			/* if the cursor changes update the cursor name */
			if (m_curNew != curOld) {
				InvalidateRect(m_hWnd, &m_rcInfoName, TRUE);
			}
		}
		break;

		//----終了処理----
	case WM_DESTROY:
		UnloadWintab( );
		PostQuitMessage(0);
		break;

		//----デフォルトの処理----
	default :
		return DefWindowProc(m_hWnd,msg,wParam,lParam);
	}

	return 0L;
}