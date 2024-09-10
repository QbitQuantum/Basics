int pdnopen(char filename[256], int gametype)
	{
	// parses a pdn file and makes it ready to be used by PDNfind 
	// the games are read and the struct PDNlistentry positions is used
	// to store all games.
	// PDNlistentry contains the game index in the database, so it can
	// be retrieved from a position

	int games_in_pdn;
	int maxpos;
	int i,ply,gamenumber=0;
	FILE *fp;
	char *start, *startheader, *starttoken, *buffer, game[GAMESIZE],header[256],token[1024];
	int from,to;
	int from2,to2;
	size_t bytesread;
	struct move movelist[MAXMOVES];
	int moves;
	struct pos p;
	int color=BLACK;
	char notation[256];
	char headername[256],headervalue[256];
	int result=UNKNOWN;
	int win=0,loss=0,draw=0,unknown=0;
	char FEN[255];
	char setup[255];
	char pdnopenname[MAX_PATH];
	int board8[8][8];
	int filesize=0;
	int square[32] = {SQ1, SQ2, SQ3, SQ4, SQ5, SQ6, SQ7, SQ8, SQ9, SQ10, SQ11, SQ12,
		              SQ13, SQ14, SQ15, SQ16, SQ17, SQ18, SQ19, SQ20, SQ21, SQ22,
					  SQ23, SQ24, SQ25, SQ26, SQ27, SQ28, SQ29, SQ30, SQ31, SQ32};

	
	// get number of games in PDN
	games_in_pdn = PDNparseGetnumberofgames(filename);

	// allocate memory for database positions. 
	// hans' 22'000 game archive has about 1.2 million positions, i.e. 54 
	// a typical game might have 80 moves. allocate 80x the number of games
	maxpos = 1000 + 80*games_in_pdn;
	
	if(positions == NULL)
		{
//		positions = (PDNlistentry *) malloc(maxpos * sizeof(struct PDNlistentry));
		positions =  malloc(maxpos * sizeof(struct PDNlistentry));
		if(positions == NULL)
			return 0;
        }

	
	// get size of the file we want to open
	filesize = getfilesize(filename);
	filesize = ((filesize/1024)+1)*1024;
	
	// allocate memory for the file
	buffer = (char *) malloc(filesize);
	if (buffer == NULL)
		return 0;

	// open the file
	fp=fopen(filename,"r");
	if(fp==NULL)
		{
		printf("\ncould not open input file %s\n",filename);
		free(buffer);
		return 0;
		}
	
	// read file into memory 
	bytesread=fread(buffer,1,filesize,fp);
	fclose(fp);
	// set termination 0 so functions wont run out of the buffer
	buffer[bytesread]=0;

	// start parsing
	start = buffer;
	while(PDNparseGetnextgame(&start,game)) 
		//pdnparsenextgame puts PDN of one game in "game" and terminates "game" with a 0.					
		{
		// load headers 
		startheader = game;
		// double check zero termination of game
		game[GAMESIZE-1]=0;
		sprintf(setup,"");
		while(PDNparseGetnextheader(&startheader,header))
			{
			sscanf(header,"%s %s",headername,headervalue);
			for(i=0; i<(int)strlen(headername);i++)
				headername[i] = (char)tolower(headername[i]);
			
			if(strcmp(headername,"result")==0)
				{
				if(strcmp(headervalue,"\"1/2-1/2\"")==0)
					{
					result=DRAW;
					draw++;
					}
				if(strcmp(headervalue,"\"1-0\"")==0)
					{
					result=WIN;
					win++;
					}
				if(strcmp(headervalue,"\"0-1\"")==0)
					{
					result=LOSS;
					loss++;
					}
				if(strcmp(headervalue,"\"*\"")==0)
					{
					result=UNKNOWN;
					unknown++;
					}
				}
			
			if(strcmp(headername,"setup")==0)
				sprintf(setup,"%s",headervalue);
			if(strcmp(headername,"fen")==0)
				{
				// headervalue+1 because headervalue contains "W:...", it has these """" thingies in.
				sprintf(FEN,"%s",headervalue+1);
				// pdn requires that fen tag is accompanied by "setup "1"" tag, which is
				// kind of redundant. so i just set that anyway to make it work always.
				sprintf(setup,"\"1\"");
				}
			}

		if(strcmp(setup,"\"1\"")==0)
			{
			FENtoboard8(board8,FEN,&color, gametype);
			// it's a setup position - have to parse FEN!
			boardtobitboard(board8,&p);
			ply=0;
			}
		else
			{
			// set start position 
			p.bk=0;
			p.wk=0;
			p.bm=0x00000FFF;
			p.wm=0xFFF00000;
			color = BLACK;
			ply = 0;
			}
		// save position:
		positions[n].black = p.bm|p.bk;
		positions[n].white = p.wm|p.wk;
		positions[n].kings = p.bk|p.wk;
		positions[n].gameindex = gamenumber;
		positions[n].result = result;
		positions[n].color = color;
		n++;
		// load moves 

		starttoken = startheader;
		while(PDNparseGetnexttoken(&starttoken,token))
			{
			// if it's a move, continue
			if(token[strlen(token)-1]=='.') 
				continue;
			// if it's a comment, continue
			if(token[0]=='{')
				continue;
			// if it's a nemesis-style comment or a variation, continue
			if(token[0]=='(')
				continue;

			PDNparseTokentonumbers(token,&from,&to);
			// we now have the from and to squares of the move in 
			// the variables from, to
			
			// find the move which corresponds to this 
			
			moves=makecapturelist(&p, movelist, color);
			if(moves==0)
				moves=makemovelist(&p,movelist,color);
			for(i=0;i<moves;i++)
				{
				// speed improvement here: we already know our from
				// square, check against the move, and throw out all
				// moves which don't fit the from square.
				if(((movelist[i].bm|movelist[i].bk|movelist[i].wm|movelist[i].wk) & square[from-1]) == 0)
					continue;
				movetonotation(p,movelist[i],notation,color);
				PDNparseTokentonumbers(notation,&from2,&to2);
				if(from==from2 && to==to2)
					{
					// inline domove as its an inner loop.
					p.bm ^= movelist[i].bm;
					p.bk ^= movelist[i].bk;
					p.wm ^= movelist[i].wm;
					p.wk ^= movelist[i].wk;
					color^=CC;
					break;
					}
				}
			// save position:
			positions[n].black = p.bm|p.bk;
			positions[n].white = p.wm|p.wk;
			positions[n].kings = p.bk|p.wk;
			positions[n].gameindex = gamenumber;
			positions[n].result = result;
			positions[n].color = color;
		
			ply++;
			n++;
			if(n>=maxpos)
				{
				free(buffer);
				return 0;
				}
			} // end game
		gamenumber++;
		if(gamenumber >= MAXGAMES)
			break;
		}


	free(buffer);
	strcpy(pdnopenname, CBdirectory);
	PathAppend(pdnopenname, "pdnopen.txt");
	fp = fopen(pdnopenname,"w");
	fprintf(fp,"games %i positions %i",gamenumber, n);
	fprintf(fp,"/ngames_in_pdn %i, maxpos guess %i", games_in_pdn, maxpos);
	fclose(fp);
	return 1;
	}