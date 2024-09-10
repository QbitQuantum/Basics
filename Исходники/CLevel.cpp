bool CLevel::loadNW(CString& pFileName)
{
	CStringList levelData;
	CString version;
	char* dataFile = getDataFile(pFileName.text());
	if(!strlen(dataFile))
		return false;

	if(!levelData.load(dataFile))
		return false;

	if(levelData.count() < 1)
		return false;

	version = levelData[0];
	modTime = getFileModTime(dataFile);
	fileName = pFileName;
	if(version == "GLEVNW01" || version == "GSERVL01")
	{
		for(int i = 1; i < levelData.count(); i ++)
		{
			CStringList words;
			words.load(levelData[i].text(), " ");
			if(words.count() <= 0)
				continue;
			if(words[0] == "BOARD")
			{
				if(words.count() <= 5)
					continue;

				int x = atoi(words[1].text());
				int y = atoi(words[2].text());
				int w = atoi(words[3].text());
				CString& data = words[5];
				if(x >= 0 && x <= 64 && y >= 0 && y <= 64 && w > 0 && x + w <= 64)
				{
					if(data.length() >= w*2)
					{
						for(int ii = x; ii < x + w; ii++)
						{
							char left = data.readChar();
							char top = data.readChar();
							short tile = base64.find(left) << 6;
							tile += base64.find(top);
							tiles[ii + y*64] = tile;
						}
					}
				}
			} else if(words[0] == "LINK")
			{
				if(words.count() <= 7)
					continue;
				if(strlen(getDataFile(words[1].text())))
				{
					links.add(new CLink(words[1], atoi(words[2].text()), atoi(words[3].text()),
						atoi(words[4].text()), atoi(words[5].text()), words[6], words[7]));
				}
			} else if(words[0] == "CHEST")
			{
				if(words.count() <= 4)
					continue;
				for(int ii = 0; ii < itemcount; ii++)
				{
					if(words[3] == itemNames[ii])
					{
						chests.add(new CChest(atoi(words[1].text()), atoi(words[2].text()),
							atoi(words[4].text()), ii));
						break;
					}
				}

			} else if(words[0] == "NPC")
			{
				if(words.count() <= 3)
					continue;
				CString image, code, code2;
				float x, y;
				if(words[1] != "-")
					image = words[1];

				x = (float)atof(words[2].text());
				y = (float)atof(words[3].text());
				for(i++; i < levelData.count() && levelData[i] != "NPCEND"; i++)
					code << levelData[i] << "\xa7";

				// Create the new NPC.  Do this before parsing the join commands.
				// The CNpc constructor will remove all comments.
				CNpc* jnpc = new CNpc( image, code, x, y, this, true );

				// Now filter out the join commands.
				CStringList npcData;
				npcData.load( jnpc->clientCode.text(), "\xa7" );
				for ( int j = 0; j < npcData.count(); ++j )
					code2 << processNpcLine( npcData[j] ) << "\xa7";
				jnpc->clientCode = code2;

				// Now, add all the joined files to the code.
				if ( joinList.count() > 0 )
				{
					CString* file = 0;
					while ( (file = (CString*)joinList[0]) != 0 )
					{
						// Load the source file into memory.
						CString dataFile = getDataFile(file->text());
						if(dataFile.length())
						{
							// Append to the end of the script.
							CString retVal;
							retVal.load(dataFile.text());
							retVal.replaceAll("\r\n", "\xa7");
							retVal.replaceAll("\n", "\xa7");
							jnpc->clientCode << retVal << "\xa7";
						}
						delete (CString*)joinList[0];
						joinList.remove(0);
					}
				}
				joinList.clear();

				npcs.add( jnpc );
			} else if(words[0] == "BADDY")
			{
				if(words.count() <= 3)
					continue;
				int x = atoi(words[1].text());
				int y = atoi(words[2].text());
				int type = atoi(words[3].text());

				CBaddy* baddy = new CBaddy(x, y, type);
				int baddyId = createBaddyId(baddy);
				baddy->id = baddyId;
				for(i++; i < levelData.count() && levelData[i] != "BADDYEND"; i++)
					baddy->verses.add(levelData[i].text());
				if(baddies.count() < 50)
					baddies.add(baddy);
				else delete baddy;
			} else if(words[0] == "SIGN")
			{
				if(words.count() <= 2)
					continue;

				CString sign;
				int x = atoi(words[1].text());
				int y = atoi(words[2].text());
				sign.writeChar(x+32);
				sign.writeChar(y+32);

				for (i++; i < levelData.count() && levelData[i] != "SIGNEND"; i++)
					sign << getSignCode(CString() << levelData[i] << "\n");
				signs.add(sign);
			} else if(words[0] == "REPLACENPC")
			{
				int npcId = atoi(words[1].text());
				CNpc* npc = (CNpc*)npcs[npcId];
				if(npc == NULL)
					continue;

				for(i++; i < levelData.count() && levelData[i] != "REPLACENPCEND"; i++)
					npc->setProps((CPacket&)levelData[i]);
			}
		}
	} else return false;

	return true;
}