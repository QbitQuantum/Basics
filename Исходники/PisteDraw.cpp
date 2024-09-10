int	PisteDraw_Alusta(HWND &main_window_handle, HINSTANCE &hinstance_app, 
					 int leveys, int korkeus, int bpp,
					 int max_colors)
{

	if (PD_unload) {

		strcpy(virhe,"Uh, oh, I think we have a bug...");

		PD_main_window_handle	= (HWND &)main_window_handle;
		PD_hinstance_app		= (HINSTANCE &)hinstance_app;
		PD_ruudun_leveys		= leveys;
		PD_ruudun_korkeus		= korkeus;
		PD_ruudun_bpp			= bpp;
		PD_max_varit			= max_colors;
		
		LPDIRECTDRAW temp = NULL;				 // väliaikainen rajapinta jolla haetaan uusin versio
		int i;

		if (FAILED(DirectDrawCreate(NULL, &temp, NULL)))	// luo rajapintaosoitin versioon 1.0
		{
			strcpy(virhe,"Cannot initialize DirectDraw!");
			PisteLog_Kirjoita("[Error] Piste Draw: Cannot initialize DirectDraw! \n");
			return PD_VIRHE;
		}

		if (FAILED(temp->QueryInterface(IID_IDirectDraw4,(LPVOID *)&PD_lpdd))) // osoitin v 4.0
		{
			strcpy(virhe,"Cannot initialize DirectDraw4!");
			PisteLog_Kirjoita("[Error] Piste Draw: Cannot initialize DirectDraw4! \n");
			return PD_VIRHE;
		}

		temp->Release();	// tuhotaan väliaikainen rajapinta
		temp = NULL;
		
		if (FAILED(PD_lpdd->SetCooperativeLevel(PD_main_window_handle, // Yhteistyö Windowsin kanssa..
											  DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX |
											  DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
		{
			strcpy(virhe,"Failed to cooperate with Windows!");
			PisteLog_Kirjoita("[Error] Piste Draw: Failed to cooperate with Windows! \n");
			return PD_VIRHE;
		}
		
		if (FAILED(PD_lpdd->SetDisplayMode(PD_ruudun_leveys, PD_ruudun_korkeus, PD_ruudun_bpp,0,0)))
		{
			strcpy(virhe,"Unable to change video mode!");
			PisteLog_Kirjoita("[Error] Piste Draw: Unable to change video mode! \n");
			return PD_VIRHE;
		}

		DD_INIT_STRUCT(PD_ddsd);

		PD_ddsd.dwFlags				=	DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		PD_ddsd.dwBackBufferCount	=	2;				//Kolmoispuskurointi = primary + 2 taustapuskuria
		PD_ddsd.ddsCaps.dwCaps		=	DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
		
		if (FAILED(PD_lpdd->CreateSurface(&PD_ddsd, &PD_lpddsprimary, NULL)))
		{
			strcpy(virhe,"Cannot create primary surface!");
			PisteLog_Kirjoita("[Error] Piste Draw: Cannot create primary surface! \n");
			return PD_VIRHE;
		}
		
		PD_buffers[PD_TAUSTABUFFER].leveys		= leveys;
		PD_buffers[PD_TAUSTABUFFER].korkeus		= korkeus;
		PisteDraw_Aseta_Klipperi(PD_TAUSTABUFFER,0,0,leveys,korkeus);
		PD_ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
		
		if (FAILED(PD_lpddsprimary->GetAttachedSurface(&PD_ddsd.ddsCaps, &PD_buffers[PD_TAUSTABUFFER].lpdds)))
		{
			strcpy(virhe,"Cannot attach back buffer to primary surface!");
			PisteLog_Kirjoita("[Error] Piste Draw: Cannot attach back buffer to primary surface! \n");
			return PD_VIRHE;
		}

		PD_buffers[PD_TAUSTABUFFER2].leveys		= leveys;
		PD_buffers[PD_TAUSTABUFFER2].korkeus	= korkeus;
		PisteDraw_Aseta_Klipperi(PD_TAUSTABUFFER2,0,0,leveys,korkeus);

		for (i=1;i<255;i++)							//Luodaan 8-bittinen paletti
		{
			PD_paletti[i].peRed		=	0;
			PD_paletti[i].peGreen	=	0;
			PD_paletti[i].peBlue	=	0;
			PD_paletti[i].peFlags	=	PC_NOCOLLAPSE;
		}

		if (FAILED(PD_lpdd->CreatePalette(DDPCAPS_8BIT |
										DDPCAPS_ALLOW256 |
										DDPCAPS_INITIALIZE,
										PD_paletti,
										&PD_lpddpal,
										NULL)))
		{
			PisteLog_Kirjoita("[Error] Piste Draw: Cannot create 8-bit palette! \n");
			strcpy(virhe,"Cannot create 8-bit palette!");
			return PD_VIRHE;
		}

		if (FAILED(PD_lpddsprimary->SetPalette(PD_lpddpal)))
		{
			PisteLog_Kirjoita("[Error] Piste Draw: Cannot set palette! \n");
			strcpy(virhe,"Cannot set palette!");
			return PD_VIRHE;
		}

		/*LIITETÄÄN KLIPPERI KUVAN REUNOJEN YLIKIRJOITUSTA ESTÄMÄÄN*/

		PD_fontbuffer = PisteDraw_Buffer_Uusi(PD_ruudun_leveys,10,true,255);

		for (i=2;i<MAX_BUFFEREITA;i++)		// alustetaan kuvabufferi taulukko.  
			PD_buffers[i].lpdds = NULL;				// 0 ja 1 on varattu taustapuskureille

		vasen_marginaali = 0;
		yla_marginaali = 0;
	
		PD_unload = false;
	}

	return 0;
}