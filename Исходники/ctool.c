void GetLine( char * buffer, const unsigned int size, int EchoFlag )
{
	char		ch = 0 ;
	int		c;
	char*		p = buffer ;
	unsigned int	n = 0L ;
	int		i ;

	while( n < size )
	{
		c = GetChar() ;
		if( c == -1 )
		{
		    continue;
		}
		ch = c;
		//dprintf("%x ",ch);
		if( ch == KEYCODE_LF )
		{
		    #ifdef USE_LF
		    *--p = 0 ;
		    n-- ;
		    #endif // USE_LF
		    break ;
		}
		else if( ch == KEYCODE_CR )
		{
		    *p = 0 ;
#ifndef CONFIG_HISTORY_KEYIN
		    n-- ;
#else //#ifdef CONFIG_HISTORY_KEYIN
		if(n!=0)
		{
			strcpy(history_cmd[hist_save_idx], buffer);
			(hist_save_idx >= HISTORY_CMD_ELN-1) ? hist_save_idx=0 : hist_save_idx++;
			hist_see_idx=hist_save_idx;
		}

#endif
		    break ;
		}
		else if( ch == KEYCODE_BS_7F )
		{
		    if( p != buffer )
		    {
			    p-- ;
			    n-- ;
							if(EchoFlag)
							{
								PutChar(KEYCODE_BS);
								PutChar(' ');
								PutChar(KEYCODE_BS);
							}
		    }
		}
		else if( ch == KEYCODE_TAB )
		{
		    for( i=0 ; i < TAB ; i++ )
		    {
			    *p++ = ' ' ;
			    n++ ;
							if(EchoFlag) PutChar(' ');
		    }
		}
#ifdef CONFIG_HISTORY_KEYIN
		else if( ch == KEYCODE_ESC )
		{				
			if( GetChar()!= KEYCODE_BRACKET)		continue;
			
			c=GetChar();
			
			unsigned int  vk= ( KEYCODE_ESC <<24) | (KEYCODE_BRACKET<<16) | (c<<8) | 0 ;
			
			if( vk==KEYCODE_VKUP)
			{				
				(hist_see_idx==0) ? hist_see_idx= HISTORY_CMD_ELN-1 : hist_see_idx--;
			}
			else if(vk== KEYCODE_VKDOWN) 
			{
				(hist_see_idx==HISTORY_CMD_ELN-1) ? hist_see_idx= 0 : hist_see_idx++;
					
			}
			else 
				continue;

			//clear
			for(i=0;i<n;i++)
			{
				PutChar(KEYCODE_BS);
				PutChar(' ');
				PutChar(KEYCODE_BS);
			}
			strcpy(buffer, history_cmd[hist_see_idx]);
			n= strlen(buffer);
			p=buffer+n;
			dprintf("%s", buffer);
			
		}
#endif
		else
		{
		    *p++ = ch ;
		    n++ ;
					if(EchoFlag) PutChar(ch);
		}
	}
}