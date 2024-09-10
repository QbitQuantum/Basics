static void LoadDatabase(FILE *f, int loud)
{
	int ni,na,nw,nr,mc,pr,tr,wl,lt,mn,trm;
	int ct;
	short lo;
	Action *ap;
	Room *rp;
	Item *ip;
/* Load the header */

	if(fscanf(f,"%*d %d %d %d %d %d %d %d %d %d %d %d",
		&ni,&na,&nw,&nr,&mc,&pr,&tr,&wl,&lt,&mn,&trm)<10)
		Fatal("Invalid database(bad header)");
	GameHeader.NumItems=ni;
	Items=(Item *)MemAlloc(sizeof(Item)*(ni+1));
	GameHeader.NumActions=na;
	Actions=(Action *)MemAlloc(sizeof(Action)*(na+1));
	GameHeader.NumWords=nw;
	GameHeader.WordLength=wl;
	Verbs=MemAlloc(sizeof(char *)*(nw+1));
	Nouns=MemAlloc(sizeof(char *)*(nw+1));
	GameHeader.NumRooms=nr;
	Rooms=(Room *)MemAlloc(sizeof(Room)*(nr+1));
	GameHeader.MaxCarry=mc;
	GameHeader.PlayerRoom=pr;
	GameHeader.Treasures=tr;
	GameHeader.LightTime=lt;
	LightRefill=lt;
	GameHeader.NumMessages=mn;
	Messages=MemAlloc(sizeof(char *)*(mn+1));
	GameHeader.TreasureRoom=trm;

/* Load the actions */

	ct=0;
	ap=Actions;
	if(loud)
		printf("Reading %d actions.\n",na);
	while(ct<na+1)
	{
		if(fscanf(f,"%hu %hu %hu %hu %hu %hu %hu %hu",
			&ap->Vocab,
			&ap->Condition[0],
			&ap->Condition[1],
			&ap->Condition[2],
			&ap->Condition[3],
			&ap->Condition[4],
			&ap->Action[0],
			&ap->Action[1])!=8)
		{
			printf("Bad action line (%d)\n",ct);
			exit(1);
		}
		ap++;
		ct++;
	}
	ct=0;
	if(loud)
		printf("Reading %d word pairs.\n",nw);
	while(ct<nw+1)
	{
		Verbs[ct]=ReadString(f);
		Nouns[ct]=ReadString(f);
		ct++;
	}
	ct=0;
	rp=Rooms;
	if(loud)
		printf("Reading %d rooms.\n",nr);
	while(ct<nr+1)
	{
		if(fscanf(f,"%hd %hd %hd %hd %hd %hd",
			&rp->Exits[0],&rp->Exits[1],&rp->Exits[2],
			&rp->Exits[3],&rp->Exits[4],&rp->Exits[5])!=6)
		{
			printf("Bad room line (%d)\n",ct);
			exit(1);
		}
		rp->Text=ReadString(f);
		ct++;
		rp++;
	}
	ct=0;
	if(loud)
		printf("Reading %d messages.\n",mn);
	while(ct<mn+1)
	{
		Messages[ct]=ReadString(f);
		ct++;
	}
	ct=0;
	if(loud)
		printf("Reading %d items.\n",ni);
	ip=Items;
	while(ct<ni+1)
	{
		ip->Text=ReadString(f);
		ip->AutoGet=strchr(ip->Text,'/');
		/* Some games use // to mean no auto get/drop word! */
		if(ip->AutoGet && strcmp(ip->AutoGet,"//") && strcmp(ip->AutoGet,"/*"))
		{
			char *t;
			*ip->AutoGet++=0;
			t=strchr(ip->AutoGet,'/');
			if(t!=NULL)
				*t=0;
		}
		if(fscanf(f,"%hd",&lo)!=1)
		{
			printf("Bad item line (%d)\n",ct);
			exit(1);
		}
		ip->Location=(unsigned char)lo;
		ip->InitialLoc=ip->Location;
		ip++;
		ct++;
	}
	ct=0;
	/* Discard Comment Strings */
	while(ct<na+1)
	{
		free(ReadString(f));
		ct++;
	}
	if(fscanf(f,"%d",&ct)!=1)
	{
		puts("Cannot read version");
		exit(1);
	}
	if(loud)
		printf("Version %d.%02d of Adventure ",
		ct/100,ct%100);
	if(fscanf(f,"%d",&ct)!=1)
	{
		puts("Cannot read adventure number");
		exit(1);
	}
	if(loud)
		printf("%d.\nLoad Complete.\n\n",ct);
}