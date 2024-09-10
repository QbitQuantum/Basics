void cFishing::FishTarget(P_CLIENT ps)
{
	// fixes an exploit with fishing, LB
	int px,py,cx,cy;
	UOXSOCKET s=ps->socket();
	P_CHAR pPlayer=ps->player();
	if (!pPlayer) return;

	px=((buffer[s][0x0b]<<8)+(buffer[s][0x0c]%256));
	py=((buffer[s][0x0d]<<8)+(buffer[s][0x0e]%256));
	cx=abs(pPlayer->pos.x-px);
	cy=abs(pPlayer->pos.y-py);
//	int cz=abs(pPlayer->z-buffer[s][0x10]);

	if(!(cx<=6 && cy<=6))
	{
		sysmessage(s, "You are too far away to reach that");
		return;
	}
	// end exploit fix

	bool ok=false;
	if (IsFishWater(ShortFromCharPtr(buffer[s]+0x11)))
		ok = true;
	else
	{	// it might be offshore fishing (client returns id=0 for deep sea ) Duke, Thx for the hint goes to Avanoon guys
		map_st map = Map->SeekMap(Coord_cl(px, py, pPlayer->pos.map));	// search the ground tile where they casted
		if ( map.id == 0x00A8 || map.id == 0x00A9 || map.id == 0x00AA || map.id == 0x00AB )
			ok = true;
	}
	if (ok)
	{
		action(s,0x0b);
		if (SrvParams->randomtime()!=0) pPlayer->setFishingtimer(rand()%SrvParams->randomtime()+SrvParams->basetime());
		else
		pPlayer->setFishingtimer(SrvParams->basetime());
		
		soundeffect(s, 0x02, 0x3F);
		pPlayer->unhide();
		Fish(pPlayer);
	}
	else
		sysmessage(s, "You need to be closer to the water to fish!");
}