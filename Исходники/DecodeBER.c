int checkBindRes(BerElement *ber)
	{
		ber_tag_t tag;
		ber_int_t resultCode;
		ber_len_t len;
#ifdef DEBUG		
		int ival = -1;
        ber_set_option( NULL, LBER_OPT_DEBUG_LEVEL, &ival );
#endif
		if ( (tag = ber_peek_tag( ber, &len )) == LBER_ERROR ) {
			/* log, close and send error */
			printf(">>Error<< PeeK failed, tag;%d\n", tag);
			ber_free( ber, 1 );
			return LBER_ERROR;
		}

		
		tag = ber_scanf( ber, "{i}" , &resultCode );
		if ( tag == LBER_ERROR ) {
			return LBER_ERROR;
			//printf("BER decode Error! Ber_Scanf return tag:%d.\n", tag);
		}
		return resultCode;
	}