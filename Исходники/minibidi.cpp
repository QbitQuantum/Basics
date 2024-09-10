/* The Main shaping function, and the only one to be used
 * by the outside world.
 *
 * line: buffer to apply shaping to. this must be passed by doBidi() first
 * to: output buffer for the shaped data
 * from: start bidi at this index
 * count: number of characters in line
 */
int doShape(BLOCKTYPE line, CHARTYPE* to, int from, int count)
{
	int i, j, ligFlag;
	unsigned char prevTemp, nextTemp;
	CHARTYPE tempChar;

	ligFlag = 0;
	prevTemp = SU;
	nextTemp = SU;
	for(i=from; i<count; i++)
	{
		/* Get Previous and next Characters type */
		j=i;
		while(--j >= 0)
		{
			if(GetType(GETCHAR(line, j)) != NSM)
			{
				prevTemp = STYPE(GETCHAR(line, j));
				break;
			}
		}
		j=i;
		while(++j < count)
		{
			if(GetType(GETCHAR(line, j)) != NSM)
			{
				nextTemp = STYPE(GETCHAR(line, j));
				break;
			}else if(j == count-1)
			{
				nextTemp = SU;
				break;
			}
		}

		switch(STYPE(GETCHAR(line, i)))
		{
		case SC:
		case SU:
			to[i] = GETCHAR(line, i);
			break;

		case SR:
			if(prevTemp == SD || prevTemp == SC)
				to[i] = SFINAL(SISOLATED(GETCHAR(line, i)));
			else
				to[i] = SISOLATED(GETCHAR(line, i));
			break;

		case SD:
      /* Make Ligatures */
			if(GETCHAR(line, i) == 0x644)
			{
				j=i;
				while(j++<count)
				{
					if(GetType(GETCHAR(line, j)) != NSM)
					{
						tempChar = GETCHAR(line, j);
						break;
					}
				}
				switch(tempChar)
				{
				case 0x622:
					ligFlag = 1;
					if(prevTemp == SD || prevTemp == SC)
						to[i] = 0xFEF6;
					else
						to[i] = 0xFEF5;
					break;
				case 0x623:
					ligFlag = 1;
					if(prevTemp == SD || prevTemp == SC)
						to[i] = 0xFEF8;
					else
						to[i] = 0xFEF7;
					break;
				case 0x625:
					ligFlag = 1;
					if(prevTemp == SD || prevTemp == SC)
						to[i] = 0xFEFA;
					else
						to[i] = 0xFEF9;
					break;
				case 0x627:
					ligFlag = 1;
					if(prevTemp == SD || prevTemp == SC)
						to[i] = 0xFEFC;
					else
						to[i] = 0xFEFB;
					break;
				}
				if(ligFlag)
				{
					to[j] = 0x20;
					i = j;
					ligFlag = 0;
					break;
				}
			}
			if((prevTemp == SD) || (prevTemp == SC))
			{
				if(nextTemp == SR || nextTemp == SD || nextTemp == SC)
					to[i] = SMEDIAL(SISOLATED(GETCHAR(line, i)));
				else 
					to[i] = SFINAL(SISOLATED(GETCHAR(line, i)));
				break;
			}else
			{
				if(nextTemp == SR || nextTemp == SD || nextTemp == SC)
					to[i] = SINITIAL(SISOLATED(GETCHAR(line, i)));
				else
					to[i] = SISOLATED(GETCHAR(line, i));
				break;
			}

		}
		nextTemp = SU;
	}
	return 1;
}