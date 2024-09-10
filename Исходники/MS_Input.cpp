void MenuStanje::Input()
{
    static sf::Clock clock;
    float deltaT=clock.restart().asSeconds();
	
	if(tranzicija==T_NEMA)
	{
		if(stanje==GLAVNI_MENU)
		{
			if(misOtpusten==true)
			{
				if(startGumb.odabran==true)
				{						
					stanje=NIVO_ODABIR;
				}
				if(oigriGumb.odabran==true)
				{					
					stanje=O_IGRI;
				}
				if(izlazGumb.odabran==true)
				{
					tranzicija=T_FADEOUT;			
				}
				misOtpusten=false;
			}
		}
		if(stanje==NIVO_ODABIR)
		if(misOtpusten==true)
		{
			if(natragGumb.odabran==true)
				stanje=GLAVNI_MENU;
			for(int i=0; i<nivoi.size(); i++)
			{
				if(nivoi[i].gumb.odabran==true)
				{
					RenderLoading();
					nivo_datoteka=nivoi[i].datoteka;
					nivo_datoteka_g=nivoi[i].datoteka_g;
					nivo_trenutni=i;
					igra->SetState(new GameState(), true);
					break;
				}
			}
			misOtpusten=false;
		}
		if(stanje==O_IGRI)
		if(misOtpusten==true)
		{
			if(natragGumb.odabran==true)
				stanje=GLAVNI_MENU;
		}
	}
	misOtpusten=false;	
}