// --------------------------------------------------------------------------------------------
// EditierDialog anzeigen;
// in ulCnt wird die Anzahl und in ppIOG werden die ObjektGeometrien der aktuell editierten
// Objekte übergeben;
// wenn Linienobjekte verlängert werden sollen, werden in iCloseCnt, plCloseX und plCloseY
// die Anzahl und die Koordinaten der Endpunkte dieser Linienobjekte erwartet;
// in piResult wird das Ergebnis der DialogBedienung (OK, Abbrechen, Fortsetzen, Inselbeginn)
// zurückgegeben
STDMETHODIMP CGeoEditExtension::ShowEditDialog (LPCSTR pcCapt, LPCSTR pcRegKey, ulong ulCnt,
	 IUnknown** ppIOG, int* piGrabCnt, long* pGrabPktX, long* pGrabPktY, HRESULT hrComBorder,
	 long lComONr, int iCloseCnt, long* plCloseX, long* plCloseY, int* piResult)
{
	_ASSERTE (pcRegKey != NULL);
	_ASSERTE (piResult != NULL);

// Neueditierung (true) oder Modifizierung (false), also z.B. Linienverlängerung bzw.
// Inselergänzung
bool bNewEdit = (0 == strcmp (g_cbGeoEditNewPoint, pcRegKey) ||
				 0 == strcmp (g_cbGeoEditNewLine, pcRegKey) ||
				 0 == strcmp (g_cbGeoEditNewArea, pcRegKey));

// !!!! es wird vorläufig nur EIN ppIOG-Objekt berücksichtigt !!!!!
WObjektGeometrie wObj = *ppIOG;		// mit implizitem QueryInterface

CEditDlg sheetED (pcCapt, wObj, lComONr, piGrabCnt);
// eigene Pages zum	Einfügen in sheetED
CEditBaseDlg pageEB (pGrabPktX, pGrabPktY, hrComBorder, iCloseCnt,
					 plCloseX, plCloseY, bNewEdit);
CEditCoordDlg pageEC (iCloseCnt, plCloseX, plCloseY);

	sheetED.AddPage (&pageEB);	// 1. Page einfügen
	sheetED.AddPage (&pageEC);	// nächste Page hinzufügen

	// zusätzliche Pages über die Registry nachladen
	sheetED.LoadExtPagesFromRegistry (pcRegKey, ulCnt, ppIOG);

	sheetED.Show();

	if (piGrabCnt) *piGrabCnt = sheetED.GetGrabCnt();

	*piResult = sheetED.Result();

int iMarkGr;	// Markergröße
Rectangle Rec;	// rechteckiger Bereich, der (evtl.) gezeichnet werden soll

	m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
	wObj->RectangleToDraw2 ((RECT*)&Rec, iMarkGr);

HRESULT hrRet = S_OK;

	switch (*piResult)
	{
		case IDOK:
			if (bNewEdit)
			{
			BSTR bsObjName = A2BSTR("");	// noch leerer Objektname  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				hrRet = StoreNewObject (wObj, bsObjName);
				if (S_FALSE == hrRet) {
				// Objekt wurde wieder gelöscht, IDCANCEL simulieren
					if (piGrabCnt) 
						*piGrabCnt = 0;
					DEX_RePaintRectWait (Rec);	// Objekt auf Bildschirm durch Zeichnen löschen
					*piResult = IDCANCEL;
					return S_FALSE;
				}
			}
			// die Linienverlängerungen werden in LineElongation.cpp abgespeichert;
			// Flächenobjekte mit hinzugefügten Inseln werden in IslandAdd.cpp abgespeichert
			else if	(0 != strcmp (g_cbGeoEditLineElongat, pcRegKey) &&
					 0 != strcmp (g_cbGeoEditIslandAdd, pcRegKey))
			{
				_ASSERTE (false);
				hrRet = E_UNEXPECTED;
			}

			if (piGrabCnt) *piGrabCnt = 0;

			// für "Insel hinzufügen" erfolgt das Zeichnen wegen evtl. Geometriefehler auf
			// jeden Fall in StoreAreaWithNewIsland()
			if (0 != strcmp (g_cbGeoEditIslandAdd, pcRegKey))
				DEX_RePaintRectWait (Rec);
			break;

		case IDCANCEL:
			if (piGrabCnt) *piGrabCnt = 0;
			DEX_RePaintRectWait (Rec);	// Objekt auf Bildschirm durch Zeichnen löschen
			break;

		case IDB_CONTINUE:
		case IDB_ISLAND:
			break;

		default:
			_ASSERTE (false);
			hrRet = E_UNEXPECTED;
			break;
	}

	return hrRet;

} // ShowEditDialog