int MenuProvas  ( void )
   {
   static	char *Opcoes[NUMOPC] = {
					"      POS SIMPLES      ",
					"    BRONCO-DILATACAO   ",
					"   BRONCO-PROVOCACAO   ",
					"ESPIROMETRIA DE ESFORCO",
					"        RETORNAR       "
				       };

   int  cont = 0, Lin[NUMOPC], alt;
   int               i, corf, corb;


   Lin[0] =  5;
   Lin[1] = 25;
   Lin[2] = 45;
   Lin[3] = 65;
   Lin[4] = 85;

   AtivaJanelaGrafica(MENU_2,0);
   clearviewport ();
   setcolor (bea_color[14]);
   getviewsettings(&vp);
   clearviewport();

   alt = CharH;

   for ( i = 0; i < NUMOPC; i++ )
      {
      setviewport( vp.left , vp.top + DELTA_Y(Lin[i]) - 1,
		   vp.right, vp.top + DELTA_Y(Lin[i]) + 1 + alt, 1);
      clearviewport();

      if ( cont == i )
	 {
	 corb = bea_color[14];
	 corf = bea_color[ 0];
	 }
      else
	 {
	 corb = bea_color[ 0];
	 corf = bea_color[14];
	 }

      setfillstyle(1, corb);
      floodfill(1,1,1);
      setcolor(corf);
      outtextxy(  DELTA_X(50) - textwidth(Opcoes[i])/2, 2, Opcoes[i]);

      }

   do {
      LimpaBufferTeclado();
      sc.c = LeTeclado();
      if (sc.ch[0] == 0)
	 if (sc.ch[1]==72 || sc.ch[1]==80)
	    {
	    setviewport( vp.left , vp.top + DELTA_Y(Lin[cont]) - 1,
			 vp.right, vp.top + DELTA_Y(Lin[cont]) + 1 + alt, 1);

	    clearviewport();

	    setcolor(bea_color[14]);

	    outtextxy(  DELTA_X(50) - textwidth(Opcoes[cont])/2, 2, Opcoes[cont]);

	    if (sc.ch[1]==72)
	       {
	       if (--cont < 0)  cont = NUMOPC - 1;
	       }
	    else
	       {
	       cont = (cont + 1) % NUMOPC;
	       }

	    setviewport( vp.left , vp.top + DELTA_Y(Lin[cont]) - 1,
			 vp.right, vp.top + DELTA_Y(Lin[cont]) + 1 + alt, 1);

	    clearviewport();
	    setfillstyle(1, bea_color[14]);
	    floodfill(1,1,1);
	    setcolor(bea_color[0]);
	    outtextxy(  DELTA_X(50) - textwidth(Opcoes[cont])/2, 2, Opcoes[cont]);
	    }

      } while(sc.ch[0] != ENTER);

   setviewport(vp.left,vp.top,vp.right,vp.bottom,1);

   return(cont);
   }  /* End of MenuProvas () */