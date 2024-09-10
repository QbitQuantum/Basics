// ************ The ship handling screen ************ //
void Base::ShipScreen()
{
	char tempstring[200], temp2string[200];

	meter[0].value = dummy.maxpower;			//Ship power usage
	meter[0].maxvalue = MAXPOWERMETERVALUE;
	meter[0].type = MPOWER;
	meter[1].value = dummy.maxenergy;			//Ship energy
	meter[1].maxvalue = MAXENERGYMETERVALUE;
	meter[1].type = MENERGY;
	meter[2].value = dummy.forwardsspeed;			//Ship speed
	meter[2].maxvalue = MAXSPEEDMETERVALUE;
	meter[2].type = MSPEED;

	sprintf_s(descstring,2048,"%s",dummy.description);
	if(playmode==SINGLEPLAYER)
	{
		UINT m[6];
		m[0] = messageindex;
		for(int i=1;i<6;++i)
			m[i] = (m[0]+i)%6;
		if(newmessagetime<=thistick)
		{
			newmessagetime = thistick + rand()%800;
			PrintMessage(message[messageindex].txt);
			messageindex = (messageindex + 1)%6;
		}
		sprintf_s(descstring2,2048,"%s\n%s\n%s\n%s\n%s\n%s\n",message[m[0]].txt,message[m[1]].txt,message[m[2]].txt,message[m[3]].txt,message[m[4]].txt,message[m[5]].txt);
	}
	else sprintf_s(descstring2,2048," \0");

	sprintf_s(datastring,2048,"Ship: %s\nManufacturer: %s\nPower: %.1f\nEnergy: %.1f\nEngines: %d\nWeapon mounts: %d\nMissile capacity: %d \0",dummy.name,dummy.manufacturer,dummy.maxpower,dummy.maxenergy,dummy.engines,dummy.weaponmounts,dummy.maxmissiles);

	if(ship[player].keys.OPERATE)
	{
		ship[player].keys.OPERATE = false;
		soundeffect[MENUSELECT].SetSoundEffect(0);
		switch(button[buttonselector])
		{
		case EXIT:
			ChangeScreen(HOME);
			return;
		case SELECT:		//Select
			if(strcmp(data->ships[listselector].name,ship[player].name)==0)
			{
				soundeffect[MENUREJECT].SetSoundEffect(0);
				sprintf_s(messagestring,1024,"This is the same as your current ship!");
				break;
			}
			if(ship[player].credits>=dummy.cost)
			{
				ship[player].credits -= dummy.cost;

				if(ship[player].equipment[LASER_DRONE])
				{
					SET(ship[player].drone->state,FORDESTRUCTION);
					ship[player].drone = NULL;
				}
				if(ship[player].equipment[LIGHTNING_DRONE])
				{
					SET(ship[player].lightningdrone->state,FORDESTRUCTION);
					ship[player].lightningdrone = NULL;
				}
				if(ship[player].equipment[SHIELD_DRONE])
				{
					for(int i=0;i<3;i++)
					{
						SET(ship[player].shielddrone[i]->state,FORDESTRUCTION);
						ship[player].shielddrone[i] = NULL;
					}
				}
				for(int i=0;i<NUMEQUIPTYPES;i++)
					if(ship[player].equipment[i])
					{
						data->equipment[i] = true;
						ship[player].equipment[i] = false;
					}

				if(ship[player].missiles)
				{
					if(dummy.missilemount)
					{
						if(dummy.maxmissiles>=ship[player].missiles) dummy.missiles = ship[player].missiles;
						else dummy.missiles = dummy.maxmissiles;
					}
					else dummy.missiles = 0;
				}
				ship[player].power = 0;
				dummy.credits = ship[player].credits;
				strcpy_s(tempstring,50,ship[player].filename);	//Save file name of our ship
				strcpy_s(temp2string,50,ship[player].name);		//Save name of our ship
				DuplicatePlayer(&dummy,&ship[player]);
				ship[player].equipment[RADAR] = true;
				ship[player].equipment[SCANNER] = true;
				sprintf_s(messagestring,1024,"Changed to %s, charge %d",ship[player].name,ship[player].cost);
				//dbout<<"Current ship now "<<ship[player].name<<", ship in base "<<data->ships[listselector].name<<endl;
			}
			else
			{
				soundeffect[MENUREJECT].SetSoundEffect(0);
				sprintf_s(messagestring,1024,"Not enough credits - cost %d",dummy.cost);
			}
			break;
		case EQUIP:		//Equip screen
			ChangeScreen(EQUIP);
			return;
		case WEAPON:		//Weapon screen
			ChangeScreen(WEAPON);
			return;
		case SHIP:
			ChangeScreen(SHIP);
			return;
		}
	}
	if(ship[player].keys.UP)
	{
		ship[player].keys.UP = false;
		if(--listselector<0) listselector = data->numships-1;
		LoadDummy(data->ships[listselector].filename);
		//glyph.CreateGraphicalObject(dummy.blueprintfile,1);
		sprintf_s(messagestring,1024,"Cost: %d    Credits: %d",dummy.cost,ship[player].credits);
		soundeffect[MENUMOVE].SetSoundEffect(0);
	}
	else if(ship[player].keys.DOWN)
	{
		ship[player].keys.DOWN = false;
		if(++listselector==data->numships) listselector = 0;
		LoadDummy(data->ships[listselector].filename);
		//glyph.CreateGraphicalObject(dummy.blueprintfile,1);
		sprintf_s(messagestring,1024,"Cost: %d    Credits: %d",dummy.cost,ship[player].credits);
		soundeffect[MENUMOVE].SetSoundEffect(0);
	}

	return;
}