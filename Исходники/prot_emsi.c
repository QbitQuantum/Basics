/* SM2 */
static int sm_tx_waitseq(s_tx_emsidat *d)
{
	int rc, pos = 0;
	
	timer_set(&d->sync_timer, (d->tries > 1) ? 20 : 10);
	
	while(1)
	{
		if( timer_expired(d->mast_timer) )
		{
			DEB((D_HSHAKE, "sm_tx_waitseq: master timer expired"));
			log("master timer expired");
			return(SME);
		}
		
		if( timer_expired(d->sync_timer) )
		{
			DEB((D_HSHAKE, "sm_tx_waitseq: sync timer expired"));
			return(SM1);
		}
		
		if( (rc = GETCHAR(1)) < 0 )
		{
			if( rc != TTY_TIMEOUT )
			{
				DEB((D_HSHAKE, "sm_rx_waitseq: got ERROR/HANGUP"));
				return SME;
			}
		}
		else if( rc == XON || rc == XOFF )
		{
			/* Do nothing. Drop them down */
		}
		else if( rc == '*' )
		{
			memset(d->buf, '\0', sizeof(d->buf));
			pos = 0;
			d->emsi_seq = 1;
		}
		else if( d->emsi_seq && rc > ' ' && rc < '~' )
		{
			if( pos < sizeof(d->buf)-1 )
			{
				d->buf[pos++] = rc;
				d->buf[pos  ] = '\0';
			}
			
			if( pos == (sizeof(d->buf) - 1) )
			{
				DEB((D_HSHAKE, "sm_tx_waitseq: emsi buffer full \"%s\"", d->buf));
				
				d->emsi_seq = 0;
				
				if( !strncasecmp(d->buf, "EMSI_REQA77E", 12) )
				{
					/* Do nothing. Drop it down */
				}
				else if( !strncasecmp(d->buf, "EMSI_ACKA490", 12) )
				{
					/*
					 * Remote acknowleged our
					 * emsi data packet. exit.
					 */
					return SM0;
				}
				else if( !strncasecmp(d->buf, "EMSI_NAKEEC3", 12) )
				{
					/*
					 * Remote failed on our emsi data
					 * packet. Resend EMSI_DAT only after
					 * first EMSI_NAK
					 */
					DEB((D_HSHAKE, "sm_tx_waitseq: got NAK"));
					if( !d->nakcount++ )
						return SM1;
				}
				else if( !strncasecmp(d->buf, "EMSI_INQC816", 12) )
				{
					/*
					 * Do nothing. Just update sync timer
					 */
					return SM2;
				}
				else if( !strncasecmp(d->buf, "EMSI_DAT", 8) )
				{
					/*
					 * 1) We are calling system
					 * We got an echo of our sequence,
					 * possible they don't know about
					 * FIDO. yet :) Resend EMSI_INQ
					 * again.
					 * 2) We are asnwering system
					 * Think where is a stupid mailer
					 * that didn't seen our EMSI_ACK,
					 * so send it again in hope to the
					 * best
					 */
					DEB((D_HSHAKE, "sm_tx_waitseq: got echo \"%s\"",
							string_printable(d->buf)));

					if( d->caller )
					{
						/* Wait for a login prompt */
						sleep(2);
						
						if( PUTSTR("**EMSI_INQC816\r") < 0
						 || FLUSHOUT() < 0 )
							return SME;

						/* Wait for a password prompt */
						sleep(2);
						
						if( PUTSTR("**EMSI_INQC816\r") < 0
						 || FLUSHOUT() < 0 )
							return SME;
						
						return SM1;
					}
					else
					{
						/* Send acknowlegment */
						if( PUTSTR("**EMSI_ACKA490\r**EMSI_ACKA490\r") < 0 )
							return SME;
						if( FLUSHOUT() < 0 )
							return SME;
					}
				}
				else
				{
					DEB((D_HSHAKE, "got unexpected emsi sequence: \"%s\"",
							string_printable(d->buf)));
					log("got unexpected emsi sequence \"%s\"",
							string_printable(d->buf));
				}
			}
		}
		else if( d->emsi_seq )
		{
			d->emsi_seq = 0;
			DEB((D_HSHAKE, "sm_tx_waitseq: bad character 0x%02x in \"%s\"",
					rc, string_printable(d->buf)));
		}
	}

	return SME;
}