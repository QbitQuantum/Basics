// SORGT FÜR DIE BEWEGUNG DES BALLES
int ballmove(int Ball,int *direction,int *upDown){
	
	playingField[YMIDDLE][XMIDDLE]=' '; // LÖSCHT STARTBALL IN MITTE MIT LEERZEICHEN

	// ERSTELLEN DER MITTELLINIE MUSS NACH JEDEM DURCHLAUF PASSIEREN; DA BEIM ÜBERQUEREN IMMER GELÖSCHT WIRD
	for(int i=0; i<YVALUE; i++){
		playingField[i][XMIDDLE]='|';
	}

	// ANWEISUNGEN FÜR DIE GRENZSTELLE x=XVALUE-5 -> Schläger2-Ball-Konfrontation
	if(playingField[YMIDDLE+*upDown][Ball+1]==16 && Ball==XVALUE-5){ // WENN BALL-> SCHLÄGER 2
		PlaySoundA("pong.wav",NULL,SND_ASYNC);
		if(playingField[YMIDDLE+*upDown-1][Ball+1]==' '){            // WENN BALL VON VORNE/UNTEN -> SCHLÄGER2 OBERE HÄLFTE
			*direction=-2;Ball--;    // BEDINGUNG FÜR RÜCKWÄRTS-HOCH FOLGEBÄLLE
			playingField[YMIDDLE+*upDown][Ball+1]=' ';               // ÜBERSCHREIBT LETZTEN BALL DER VORHERIGEN BEWEGUNG MIT LEERZEICHEN
		}else
		if(playingField[YMIDDLE+*upDown+1][Ball+1]==' '){           // WENN BALL VON VORNE/OBEN -> SCHLÄGER2 UNTERE HÄLFTE
			*direction=-3; Ball--;  // BEDINGUNG FÜR RÜCKWÄRTS-RUNTER FOLGEBÄLLE
			playingField[YMIDDLE+*upDown][Ball+1]=' ';   // ÜBERSCHREIBT LETZTEN BALL DER VORHERIGEN BEWEGUNG MIT LEERZEICHEN
		}else
		if(playingField[YMIDDLE+*upDown+1][Ball+1]==16 && playingField[YMIDDLE+*upDown-1][Ball+1]==16){ // WENN BALL VON VORNE/UNTEN/OBEN -> SCHLÄGER2 MITTE
			*direction=-1; Ball--; // BEDINGUNG FÜR RÜCKWÄRTS-GERADEAUS FOLGEBÄLLE
			playingField[YMIDDLE+*upDown][Ball+1]=' '; // ÜBERSCHREIBT LETZTEN BALL DER VORHERIGEN BEWEGUNG MIT LEERZEICHEN
		}
	} 

	// ANWEISUNGEN FÜR DIE GRENZSTELLE x=3 -> Schläger1-Ball-Konfrontation
	if(playingField[YMIDDLE+*upDown][Ball-1]==17 && Ball==3){       // WENN BALL -> SCHLÄGER1
		PlaySoundA("pong.wav",NULL,SND_ASYNC);
		if(playingField[YMIDDLE+*upDown-1][Ball-1]==' '){           // WENN BALL VON VORNE/UNTEN -> SCHLÄGER1 OBEN
			*direction=2;	// BEDINGUNG FÜR GERADEAUS-HOCH FOLGEBÄLLE
		}else
		if(playingField[YMIDDLE+*upDown+1][Ball-1]==' '){           // WENN BALL VON VORNE/OBEN -> SCHLÄGER1 UNTEN
			*direction=3;   // BEDINGUNG FÜR GERADEAUS-RUNTER
		}else
		if(playingField[YMIDDLE+*upDown+1][Ball-1]==17 && playingField[YMIDDLE+*upDown-1][Ball-1]==17){ // WENN BALL VON VORNE/UNTEN/OBEN -> SCHLÄGER1 MITTE
			*direction=1; Ball++; // BEDINGUNG FÜR GERADEAUS
			playingField[YMIDDLE+*upDown][Ball-1]=' ';              // ÜBERSCHREIBT LETZTEN BALL DER VORHERIGEN BEWEGUNG MIT LEERZEICHEN
		}
	}

	// FOLGENDE If's SORGEN FÜR ALLE RÜCKWÄRTSBEWEGUNGEN (RÜCKWÄRTS-GERADE;RÜCKWÄRTS-HOCH;RÜCKWÄRTS-RUNTER)
	// RÜCKWARTS-HOCH
	if(*direction==-2){
		*upDown-=1;Ball--;
		playingField[YMIDDLE+*upDown+1][Ball+1]=' ';                // LÖSCHT ALTEN BALL MIT LEERZEICHEN
		playingField[YMIDDLE+*upDown][Ball]=1;                      // SCHREIBT EINEN BALL EINE X/Y STELLE ZURÜCK
        if(*upDown==-YMIDDLE/*playingField[YMIDDLE+upDown][Ball]==playingField[0][Ball]*/){ // FALLS SPIELRAND OBEN
			PlaySoundA("pong.wav",NULL,SND_ASYNC);
			*direction=-3;*upDown-=1;Ball++;
		}
	}

	// RÜCKWÄRTS-RUNTER
	if(*direction==-3){
		*upDown+=1;Ball--;
		playingField[YMIDDLE+*upDown-1][Ball+1]=' ';     // LÖSCHT ALTEN BALL MIT LEERZEICHEN
		playingField[YMIDDLE+*upDown][Ball]=1;           // SCHREIBT EINEN BALL EINE X STELLE ZURÜCK UND EINE Y STELLE VOR
		if(playingField[YMIDDLE+*upDown+1][Ball]==playingField[YVALUE][Ball]){ // FALLS SPIELRAND UNTEN
			PlaySoundA("pong.wav",NULL,SND_ASYNC);
			*direction=-2;
		}
	}

	// RÜCKWÄRTS-GERADEAUS
	if(*direction==-1){
		Ball--;
		playingField[YMIDDLE+*upDown][Ball+1]=' ';   // LÖSCHT ALTEN BALL MIT LEERZEICHEN
		playingField[YMIDDLE+*upDown][Ball]=1;       // SCHREIBT EINEN BALL EINE X STELLE ZURÜCK
	}

	// FOLGENDE if's SORGEN FÜR ALLE VORWÄRTSBEWEGUNGEN (VORWÄRTS-HOCH;VORWÄRTS-RUNTER;FORWÄRTS-GERADE)
	// FORWÄRTS-HOCH
	if(*direction==2){
		*upDown-=1;Ball++;
		playingField[YMIDDLE+*upDown+1][Ball-1]=' ';    // LÖSCHT ALTEN BALL MIT LEERZEICHEN
		playingField[YMIDDLE+*upDown][Ball]=1;          // SCHREIBT EINEN BALL EINE X/Y STELLE VOR
        if(*upDown==-YMIDDLE/*playingField[YMIDDLE+upDown][Ball]==playingField[0][Ball]*/){ // FALLS SPIELRAND OBEN
			PlaySoundA("pong.wav",NULL,SND_ASYNC);
			*direction=3;*upDown-=1;Ball--;
		}
	}

	// FORWÄRTS-RUNTER
	if(*direction==3){
		*upDown+=1;Ball++;
		playingField[YMIDDLE+*upDown-1][Ball-1]=' ';   // LÖSCHT ALTEN BALL MIT LEERZEICHEN
		playingField[YMIDDLE+*upDown][Ball]=1;         // SCHREIBT EINEN BALL EINE X/Y-STELLE VOR
		if(playingField[YMIDDLE+*upDown+1][Ball]==playingField[YVALUE][Ball]){// FALLS SPIELRAND UNTEN
			PlaySoundA("pong.wav",NULL,SND_ASYNC);
			*direction=2;
		}
	}

	// SORGT FÜR DIE GERADEAUSBEWEGUNG BEI START UND SCHLÄGER1-MITTE
	if(*direction==1){
		playingField[YMIDDLE+*upDown][Ball]=1;         // SCHREIBT EINEN NEUEN BALL EINE X-STELLE WEITER
		playingField[YMIDDLE+*upDown][Ball-1]=' ';     // ÜBERSCHREIBT ALTEN BALL MIT LEERZEICHEN
	}
	return 0;
}