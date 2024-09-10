// funkcja okna zawieraj¹ca obs³ugê meldunków przesy³anych do okna
LRESULT CALLBACK WndProc (HWND Okno, UINT KodMeldunku, WPARAM wParam, LPARAM lParam)
{
	// deklaracja zmiennych
	HMENU mGlowne, mPlik, mInfo;
    	
	// obs³uga meldunku w zale¿noœci od kodu meldunku
	switch (KodMeldunku) 
	{ case WM_CREATE:  // obs³uga utworzenia okna - stworzenie menu
		mPlik = CreateMenu();
		AppendMenu(mPlik, MF_STRING, 100, "&Gong...");
		AppendMenu(mPlik, MF_SEPARATOR, 0, "");
		AppendMenu(mPlik, MF_STRING, 101, "&Koniec");
		mInfo = CreateMenu();
		AppendMenu(mInfo, MF_STRING, 102, "&Autor...");
		mGlowne = CreateMenu();
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mPlik, "&Plik");
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mInfo, "&Info");
		SetMenu(Okno, mGlowne);
		DrawMenuBar(Okno);
		return 0;

	  case WM_COMMAND: // obs³uga wyboru opcji z menu
		switch (wParam)
		{
		case 100: if(MessageBox(Okno, "Czy wygenerowaæ gong?", "Gong", MB_YESNO) == IDYES)
					MessageBeep(0);
                  break;
		case 101: DestroyWindow(Okno); // wymuszenie meldunku WM_DESTROY
        		  break;
		case 102: MessageBox(Okno, "imiê i nazwisko:\nnumer indeksu: ", "Student PJWSTK", MB_OK);
		}
		return 0;
	
	  case WM_PAINT: // obs³uga odœwie¿enia okna
		{	PAINTSTRUCT Paint;
			HDC Kontekst = BeginPaint(Okno, &Paint);
			HPEN Pioro = CreatePen(PS_SOLID, 15, RGB(255,0,0)); // czerwone pióro o gruboœci 15
			HBRUSH Pedzel = CreateSolidBrush(RGB(255,0,0)); // czerwony pêdzel

			SelectObject(Kontekst, Pioro);
			// SelectObject(Kontekst, GetStockObject(WHITE_BRUSH)); // standardowy bia³y pêdzel
			Ellipse(Kontekst, 100, 100, 300, 300);	// narysowanie okrêgu za pomoc¹ aktywnych pióra i pêdzla

			SelectObject(Kontekst, Pedzel);
			POINT wielokat[] = {{106, 200}, {118, 248}, {152, 282}, {200, 294}, {248, 282}, {282, 248}, {294, 200}};
			Polygon(Kontekst, wielokat, 7);  // narysowanie wielok¹ta wype³niaj¹cego doln¹ po³owê okrêgu na czerwono

			SetBkMode(Kontekst, TRANSPARENT); // wypisanie tekstu
			SetTextAlign(Kontekst, TA_CENTER | TA_BOTTOM);
			// SetTextColor(Kontekst, RGB(0,0,0));
			TextOut(Kontekst, 200, 200, "P J W S T K", 11);

			DeleteObject(Pioro); // usuniêcie niepotrzebnych przyborów graficznych
			DeleteObject(Pedzel);
			EndPaint(Okno, &Paint);
		}
		return 0;
  	
	  case WM_DESTROY: // obs³uga zamkniêcia okna - wygenerowanie meldunku WM_QUIT
		PostQuitMessage (0) ;
		return 0;
    
	  default: // standardowa obs³uga wszystkich pozosta³ych meldunków
		return DefWindowProc(Okno, KodMeldunku, wParam, lParam);
	}
}