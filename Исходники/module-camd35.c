static void camd35_request_emm(ECM_REQUEST *er)
{
	int32_t i;
	time_t now;
	uchar mbuf[1024];
	struct s_client *cl = cur_client();
	struct s_reader *aureader = NULL, *rdr = NULL;

	if(er->selected_reader && !er->selected_reader->audisabled && ll_contains(cl->aureader_list, er->selected_reader))
		{ aureader = er->selected_reader; }

	if(!aureader && cl->aureader_list)
	{
		LL_ITER itr = ll_iter_create(cl->aureader_list);
		while((rdr = ll_iter_next(&itr)))
		{
			if(emm_reader_match(rdr, er->caid, er->prid))
			{
				aureader = rdr;
				break;
			}
		}
	}

	if(!aureader)
		{ return; }  // TODO

	uint16_t au_caid = aureader->caid;

	if(!au_caid && caid_is_bulcrypt(er->caid)) // Bulcrypt has 2 caids and aureader->caid can't be used. Use ECM_REQUEST caid for AU.
		{ au_caid = er->caid; }

	time(&now);
	if(!memcmp(cl->lastserial, aureader->hexserial, 8))
		if(llabs(now - cl->last) < 180) { return; }

	memcpy(cl->lastserial, aureader->hexserial, 8);
	cl->last = now;

	if(au_caid)
	{
		cl->disable_counter = 0;
		cs_log("%s emm-request sent (reader=%s, caid=%04X, auprovid=%06X)",
			   username(cur_client()), aureader->label, au_caid,
			   aureader->auprovid ? aureader->auprovid : b2i(4, aureader->prid[0]));
	}
	else if(cl->disable_counter > 2)
		{ return; }
	else
		{ cl->disable_counter++; }

	memset(mbuf, 0, sizeof(mbuf));
	mbuf[2] = mbuf[3] = 0xff;           // must not be zero
	i2b_buf(2, er->srvid, mbuf + 8);

	//override request provid with auprovid if set in CMD05
	if(aureader->auprovid)
	{
		if(aureader->auprovid != er->prid)
			{ i2b_buf(4, aureader->auprovid, mbuf + 12); }
		else
			{ i2b_buf(4, er->prid, mbuf + 12); }
	}
	else
	{
		i2b_buf(4, er->prid, mbuf + 12);
	}

	i2b_buf(2, er->pid, mbuf + 16);
	mbuf[0] = 5;
	mbuf[1] = 111;
	if(au_caid)
	{
		mbuf[39] = 1;                           // no. caids
		mbuf[20] = au_caid >> 8;        // caid's (max 8)
		mbuf[21] = au_caid & 0xff;
		memcpy(mbuf + 40, aureader->hexserial, 6);  // serial now 6 bytes
		mbuf[47] = aureader->nprov;
		for(i = 0; i < aureader->nprov; i++)
		{
			if((au_caid >= 0x1700 && au_caid <= 0x1799)  ||  // Betacrypt
					(au_caid >= 0x0600 && au_caid <= 0x0699))    // Irdeto (don't know if this is correct, cause I don't own a IRDETO-Card)
			{
				mbuf[48 + (i * 5)] = aureader->prid[i][0];
				memcpy(&mbuf[50 + (i * 5)], &aureader->prid[i][1], 3);
			}
			else
			{
				mbuf[48 + (i * 5)] = aureader->prid[i][2];
				mbuf[49 + (i * 5)] = aureader->prid[i][3];
				memcpy(&mbuf[50 + (i * 5)], &aureader->sa[i][0], 4); // for conax we need at least 4 Bytes
			}
		}
		//we think client/server protocols should deliver all information, and only readers should discard EMM
		mbuf[128] = (aureader->blockemm & EMM_GLOBAL && !(aureader->saveemm & EMM_GLOBAL)) ? 0 : 1;
		mbuf[129] = (aureader->blockemm & EMM_SHARED && !(aureader->saveemm & EMM_SHARED)) ? 0 : 1;
		mbuf[130] = (aureader->blockemm & EMM_UNIQUE && !(aureader->saveemm & EMM_UNIQUE)) ? 0 : 1;
		mbuf[127] = (aureader->blockemm & EMM_UNKNOWN && !(aureader->saveemm & EMM_UNKNOWN)) ? 0 : 1;
	}
	else        // disable emm
		{ mbuf[20] = mbuf[39] = mbuf[40] = mbuf[47] = mbuf[49] = 1; }