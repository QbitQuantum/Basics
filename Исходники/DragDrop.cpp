void dump_item(NXWCLIENT ps, PKGx08 *pp) // Item is dropped on ground or a character
{
	if (ps == NULL) return;

	tile_st tile;
	NXWSOCKET  s=ps->toInt();

	P_CHAR pc=ps->currChar();
	VALIDATEPC(pc);

	P_ITEM pi=pointers::findItemBySerial(pp->Iserial);


	if (!ISVALIDPI(pi))
	{
		LogError("client sent bad itemserial %d",pp->Iserial);
		return;
	}

	if ( isCharSerial(pi->getContSerial()) && pi->getContSerial() != pc->getSerial32() ) {
		P_CHAR pc_i = pointers::findCharBySerial(pi->getContSerial());
		if (ISVALIDPC(pc_i))
			pc_i->sysmsg("Warning, backpack disappearing bug located!");

		if (ps->isDragging()) {
                        ps->resetDragging();
                        UpdateStatusWindow(s,pi);
                }
		pi->setContSerial( pi->getContSerial(true) );
                pi->setPosition( pi->getOldPosition() );
                pi->layer = pi->oldlayer;
                pi->Refresh();
	}

	if (pi->magic == 2) { //Luxor -- not movable objects
		if (ps->isDragging()) {
                        ps->resetDragging();
                        UpdateStatusWindow(s,pi);
                }
		pi->setContSerial( pi->getContSerial(true) );
		pi->MoveTo( pi->getOldPosition() );
		pi->layer = pi->oldlayer;
		pi->Refresh();
		return;
	}




    if(pi!=NULL)
	{
		weights::NewCalc(pc);
		statwindow(pc,pc);
	}


	//Ripper...so order/chaos shields disappear when on ground.
	if( pi->getId()==0x1BC3 || pi->getId()==0x1BC4 )
	{
		pc->playSFX( 0x01FE);
		staticeffect(DEREF_P_CHAR(pc), 0x37, 0x2A, 0x09, 0x06);
		pi->Delete();
		return;
	}


	//test UOP blocking Tauriel 1-12-99
	if (!pi->isInWorld())
	{
		item_bounce6(ps,pi);
		return;
	}




	data::seekTile(pi->getId(), tile);
	if (!pc->IsGM() && ((pi->magic==2 || (tile.weight==255 && pi->magic!=1))&&!pc->canAllMove()) ||
		( (pi->magic==3 || pi->magic==4) && !(pi->getOwnerSerial32()==pc->getSerial32())))
	{
		item_bounce6(ps,pi);
		return;
	}

	if (buffer[s][5]!=(unsigned char)'\xFF')
	{


		if (pi->amxevents[EVENT_IDROPINLAND]!=NULL) 
		{
			g_bByPass = false;
			pi->MoveTo(pp->TxLoc,pp->TyLoc,pp->TzLoc);
			pi->amxevents[EVENT_IDROPINLAND]->Call( pi->getSerial32(), pc->getSerial32() );
			if (g_bByPass) {
				pi->Refresh();
				return;
			}
		}

		/*
		//<Luxor>
		g_bByPass = false;
		pi->runAmxEvent( EVENT_IDROPINLAND, pi->getSerial32(), pc->getSerial32() );
	        if (g_bByPass) {
			pi->Refresh();
			return;
		}
        //</Luxor>
		*/
		NxwSocketWrapper sw;
		sw.fillOnline( pi );
		for( sw.rewind(); !sw.isEmpty(); sw++ )
		{
			SendDeleteObjectPkt( sw.getSocket(), pi->getSerial32() );
		}

		pi->MoveTo(pp->TxLoc,pp->TyLoc,pp->TzLoc);
		pi->setContSerial(-1);

		P_ITEM p_boat = Boats->GetBoat(pi->getPosition());

		if(ISVALIDPI(p_boat))
		{
			pi->SetMultiSerial(p_boat->getSerial32());
		}


		pi->Refresh();
	}
	else
	{
		if ( !ItemDroppedOnChar(ps, pp, pi) ) {
			//<Luxor>: Line of sight check
			//This part avoids the circle of transparency walls bug

			//-----
			if ( !lineOfSight( pc->getPosition(), Loc( pp->TxLoc, pp->TyLoc, pp->TzLoc ) ) ) {
		                ps->sysmsg(TRANSLATE("You cannot place an item there!"));

        	        	Sndbounce5(s);
	                	if (ps->isDragging()) {
	                        	ps->resetDragging();
                        		UpdateStatusWindow(s,pi);
                		}
                		pi->setContSerial( pi->getContSerial(true) );
                		pi->setPosition( pi->getOldPosition() );
                		pi->layer = pi->oldlayer;
                		pi->Refresh();
                		return;
        		}
        		//</Luxor>

	        	//<Luxor> Items count check
	        	if (!pc->IsGM()) {
				NxwItemWrapper si;
				si.fillItemsAtXY( pp->TxLoc, pp->TyLoc );
				if (si.size() >= 2) { //Only 2 items permitted
					ps->sysmsg(TRANSLATE("There is not enough space there!"));
					Sndbounce5(s);
					if (ps->isDragging()) {
						ps->resetDragging();
						UpdateStatusWindow(s,pi);
					}
					if (ISVALIDPI(pc->getBackpack())) {
						pi->setCont(pc->getBackpack());
						pi->SetRandPosInCont(pc->getBackpack());
					} else {
						pi->setContSerial( pi->getContSerial(true) );
						pi->setPosition( pi->getOldPosition() );
					}
					pi->layer = pi->oldlayer;
					pi->Refresh();
					return;
				}
			}
        		//</Luxor>
		}

		weights::NewCalc(pc);  // Ison 2-20-99
		statwindow(pc,pc);
		pc->playSFX( itemsfx(pi->getId()) );

		//Boats !
		if (pc->getMultiSerial32() > 0) //How can they put an item in a multi if they aren't in one themselves Cut lag by not checking everytime something is put down
		{
			P_ITEM multi = pointers::findItemBySerial( pc->getMultiSerial32() );
			if (ISVALIDPI(multi))
			{
					//setserial(DEREF_P_ITEM(pi),DEREF_P_ITEM(multi),7);
					pi->SetMultiSerial(multi->getSerial32());
			}
		}
		//End Boats
	}
}