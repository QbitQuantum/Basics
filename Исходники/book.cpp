//Obtine mutarea urmatoare, pornind de la tabla primita ca parametru;
char* Book::getNextMove (ChessBoard tabla, COLOR culoare)
{
    int i,j,poz;                                                          // DEMONSTRATION
    INITIALIZE();
                                                  // Initialize (one time call)
    if (ERROR)
     { fprintf(debug_file,"Missing obliged file(s) RANDOM1.BIN and/or RANDOM2.BIN"); exit(1); }

    //Construim EPD;
    char EPDTemp[200];
    memset(EPDTemp,' ',64);
    memset(EPD,0,200);

    BITBOARD temp_board[2][6];
    for(i=0;i<=1;i++)
        for(j=0;j<6;j++)
            temp_board[i][j]=tabla.board[i][j];
    
    //punem piesele;
    for(i=0;i<=1;i++)
        for(j=0;j<6;j++)
            for(poz=0;poz<64;poz++)
            {
		int L=poz/8;
		int C=poz%8;
                if(temp_board[i][j]%2==1){    //daca e impar => bitul e 1;
                    if(i==BLACK)    //piese albe
                        switch(j){
                            case PAWN:    EPDTemp[(7-L)*8+C]='p'; break;
                            case KNIGHT:  EPDTemp[(7-L)*8+C]='n'; break;
                            case KING:    EPDTemp[(7-L)*8+C]='k'; break;
                            case BISHOP:  EPDTemp[(7-L)*8+C]='b'; break;
                            case ROOK:    EPDTemp[(7-L)*8+C]='r'; break;
                            case QUEEN:   EPDTemp[(7-L)*8+C]='q'; break;

                        }
                    else
                         switch(j){
                            case PAWN:    EPDTemp[(7-L)*8+C]='P'; break;
                            case KNIGHT:  EPDTemp[(7-L)*8+C]='N'; break;
                            case KING:    EPDTemp[(7-L)*8+C]='K'; break;
                            case BISHOP:  EPDTemp[(7-L)*8+C]='B'; break;
                            case ROOK:    EPDTemp[(7-L)*8+C]='R'; break;
                            case QUEEN:   EPDTemp[(7-L)*8+C]='Q'; break;
                        }
                    }
                    temp_board[i][j]>>=1;

                }
	//Scurtam textul
	int abs=0;
	char k;
	for(i=0;i<8;i++)
	{
	    k=0;
	    for(j=0;j<8;j++)
	    {
		if(EPDTemp[8*i+j]==' ')
		    k++;
		else
		{
		    if(k>0)
			EPD[abs++]=k+'0';
		    EPD[abs++]=EPDTemp[8*i+j];
		    k=0;
		}
	    }
	    if(k>0)
		EPD[abs++]=k+'0';
	    if(i!=7)
		EPD[abs++]='/';
	}

	EPD[abs++]=' ';
	if(culoare==WHITE)
	    EPD[abs++]='w';
	else
	    EPD[abs++]='b';

	strcat(EPD," KQkq -");
	EPD[strlen(EPD)]=0;

	fprintf(debug_file,"%s\n",EPD);
	//EPD[14]='1';

	//Obtinem mutarea in FROM si TO
        FIND_OPENING();
        if (ERROR) fprintf(debug_file,"Something went wrong, error-code %d",ERROR);
	else fprintf(debug_file,"Move: %s-%s\nList:",FROM,TO);

	//Toate posibilitatile:
	for (i=0; i<AZ; i++) fprintf(debug_file,"%c%c-%c%c ",FROM1[i],FROM2[i],TO1[i],TO2[i]);
	    fprintf(debug_file,"\n\n");

	//Nu exista deschidere;
	if(FROM[0]==0)
	    return 0;

	//Obtinem tipul de piesa
	PIECE piesa;
	fprintf(debug_file,"Poz:%d-%d\n",(FROM[1]-'1')*8,FROM[0]-'A');
	switch(EPDTemp[(FROM[1]-'1')*8+FROM[0]-'A'])
	{
	    case 'p': piesa=PAWN; break;
	    case 'r': piesa=ROOK; break;
	    case 'b': piesa=BISHOP; break;
	    case 'k': piesa=KING; break;
	    case 'n': piesa=KNIGHT; break;
	    case 'q': piesa=QUEEN; break;

	    case 'P': piesa=PAWN; break;
	    case 'R': piesa=ROOK; break;
	    case 'B': piesa=BISHOP; break;
	    case 'K': piesa=KING; break;
	    case 'N': piesa=KNIGHT; break;
	    case 'Q': piesa=QUEEN; break;

	}
	//fprintf(debug_file,"-- %lld --\n",(tabla.board[culoare][piesa] & ((U64)1<<((FROM[1]-'1')*8+FROM[0]-'A'))));
	
        fprintf(debug_file,"Piesa:%d\n",piesa);
	if((tabla.board[culoare][piesa] & ((U64)1<<((FROM[1]-'1')*8+FROM[0]-'A'))) == (U64) 0)
		return 0;

        //Analizam rocadele
        if(!strcmp(FROM,"E8") && !strcmp(TO,"G8"))
        {
                fprintf(debug_file,"SAN: O-O");
                return strdup("O-O");
        }
        if(!strcmp(FROM,"E8") && !strcmp(TO,"A8"))
        {
                fprintf(debug_file,"SAN: O-O-O");
                return strdup("O-O-O");
        }
        if(!strcmp(FROM,"E1") && !strcmp(TO,"G1"))
        {
                fprintf(debug_file,"SAN: O-O");
                return strdup("O-O");
        }
        if(!strcmp(FROM,"E1") && !strcmp(TO,"A1"))
        {
                fprintf(debug_file,"SAN: O-O-O");
                return strdup("O-O-O");
        }

	fprintf(debug_file,"SAN:%s\n",tabla.getSANofMove(culoare,(FROM[1]-'1')*8+FROM[0]-'A',(TO[1]-'1')*8+TO[0]-'A',piesa));

	//Intoarcem SAN-ul
	return tabla.getSANofMove(culoare,(FROM[1]-'1')*8+FROM[0]-'A',(TO[1]-'1')*8+TO[0]-'A',piesa);

}