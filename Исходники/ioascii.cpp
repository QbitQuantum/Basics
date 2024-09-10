int WinEDA_BasePcbFrame::ReadGeneralDescrPcb(wxDC * DC, FILE * File, int * LineNum)
/**********************************************************************************/
{
char Line[1024], *data;
BASE_SCREEN * screen = m_CurrentScreen;

	while(  GetLine(File, Line, LineNum ) != NULL )
	{
		data = strtok(Line," =\n\r");
		if(strnicmp(data,"$EndGENERAL",10) == 0) break;

		if( strncmp(data, "Ly", 2) == 0 )	// Old format for Layer count
		{
			int Masque_Layer = 1, ii;
			data = strtok(NULL," =\n\r");
			sscanf(data,"%X",&Masque_Layer);
			// Setup layer count
			m_Pcb->m_BoardSettings->m_CopperLayerCount = 0;
			for ( ii = 0; ii < NB_COPPER_LAYERS; ii++ )
			{
				if ( Masque_Layer & 1 ) m_Pcb->m_BoardSettings->m_CopperLayerCount++;
				Masque_Layer >>= 1;
			}
			continue;
		}

		if(strnicmp(data, "Links", 5) == 0)
		{
			data = strtok(NULL," =\n\r");
			m_Pcb->m_NbLinks = atoi(data);
			continue;
		}

		if(strnicmp(data, "NoConn", 6) == 0)
		{
			data = strtok(NULL," =\n\r");
			m_Pcb->m_NbNoconnect = atoi(data);
			continue;
		}

		if(strnicmp(data, "Di", 2) == 0)
		{
			int ii, jj, bestzoom;
			wxSize pcbsize, screensize;
			data = strtok(NULL," =\n\r");
			m_Pcb->m_BoundaryBox.SetX(atoi(data));
			data = strtok(NULL," =\n\r");
			m_Pcb->m_BoundaryBox.SetY(atoi(data));
			data = strtok(NULL," =\n\r");
			m_Pcb->m_BoundaryBox.SetWidth(atoi(data) - m_Pcb->m_BoundaryBox.GetX());
			data = strtok(NULL," =\n\r");
			m_Pcb->m_BoundaryBox.SetHeight(atoi(data) - m_Pcb->m_BoundaryBox.GetY());

			/* calcul du zoom optimal */
			pcbsize = m_Pcb->m_BoundaryBox.GetSize();
			screensize = DrawPanel->GetClientSize();
			ii = pcbsize.x/screensize.x;
			jj = pcbsize.y/screensize.y;
			bestzoom = max(ii, jj);
			screen->m_Curseur = m_Pcb->m_BoundaryBox.Centre();

			screen->SetZoom(bestzoom);
			// la position des tracés a changé: mise a jour dans le DC courant
			wxPoint org;
			DrawPanel->GetViewStart(&org.x, &org.y);
			DrawPanel->GetScrollPixelsPerUnit(&ii, &jj);
			org.x *= ii; org.y *= jj;
#ifdef WX_ZOOM
			DC->SetUserScale(1.0/(double)screen->GetZoom(), 1.0/screen->GetZoom());
			org.x *= screen->GetZoom(); org.y *= screen->GetZoom();
			DC->SetDeviceOrigin(-org.x, -org.y);
#endif
			DrawPanel->SetBoundaryBox();
			Recadre_Trace(TRUE);
			continue;
		}

			/* Lecture du nombre de segments type DRAW , TRACT, ZONE */
		if(stricmp(data, "Ndraw") == 0)
		{
			data = strtok(NULL," =\n\r");
			NbDraw = atoi(data);;
			continue;
		}

		if(stricmp(data, "Ntrack") == 0)
		{
			data = strtok(NULL," =\n\r");
			NbTrack = atoi(data);
			continue;
		}

		if(stricmp(data, "Nzone") == 0)
		{
			data = strtok(NULL," =\n\r");
			NbZone = atoi(data);
			continue;
		}

		if(stricmp(data, "Nmodule") == 0)
		{
			data = strtok(NULL," =\n\r");
			NbMod = atoi(data);
			continue;
		}

		if(stricmp(data, "Nnets") == 0)
		{
			data = strtok(NULL," =\n\r");
			NbNets = atoi(data);
			continue;
		}

	}