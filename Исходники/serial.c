void serial_mainloop(void)
{

	unsigned char buf;
	int countbyte = 0, started = 0;
	datarecord data;	// used to collect datas from plc
	datarecord data_response;	// used to send responses to plc

	setzero(&data, sizeof(data));
	first_loop = 1;

	while (1) {

		int buflen = 0;

		buflen = read(portfd, &buf, 1);

		if (buflen == -1) {
			printFatal(strerror(errno));
		}

		if (!started && buf == SOH && !countbyte) {
			started = 1;
			countbyte++;
			data.start = buf;
			continue;
		}

		if (started) {
			switch (countbyte) {
			case 1:
				/* 0x18 == 24 */
				/* if byte 1 isn't 0x18 retry... */
				if (buf != 0x18) {
					started = 0;
					countbyte = 0;
					continue;
				}
				data.length = buf;
				break;
				/* if byte 2 isn't 0x04 retry... */
			case 2:
				if (buf != 0x04) {
					started = 0;
					countbyte = 0;
					continue;
				}
				data.cmd = buf;
				break;
			}

			/* put bytes from 3 to 27 into the struct field */
			if (countbyte >= 3 && countbyte < data.length + 3) {
				data.databytes[countbyte - 3] = buf;
			}

			/* the byte 27 is the checksum given by the plc */
			if (countbyte == 27) {
				data.checksum = buf;
				if (cfg.verbose) {
					// TODO: improve logging and printf debug behaviour
					// TODO: take the log util functions from netsukuku src
					printf
					    ("catch BCC checksum value: %#x\n",
					     data.checksum);
					printf
					    ("calculated BCC checksum value: %#x\n",
					     (unsigned char)
					     calculateBCC(data));
				}
			}

			/* the byte 28 is the last byte of the record and it must be ETX */
			if (countbyte == 28 && buf == ETX) {
				data.end = buf;
				started = 0;
				countbyte = 0;
				int tmpcurr = 0;
				float tmpvolt = 0;

				// MAX_VOLT : MAX_HEX_VALUE = x : bytes
				tmpvolt =
				    (unsigned int) FETCH2BYTES(5, 4,
							       data.databytes);
				if (tmpvolt > MAX_HEX_VALUE)
					data.voltage = 0;
				else
					data.voltage =
					    tmpvolt * (float) MAX_VOLT /
					    (float) MAX_HEX_VALUE *emb_info.k1;

				tmpcurr =
				    (unsigned int) FETCH2BYTES(7, 6,
							       data.databytes);
				if (tmpcurr > MAX_HEX_VALUE)
					data.current = 0;
				else
					data.current =
					    (int) ((float) tmpcurr *
						   (float) MAX_VOLT /
						   (float) MAX_HEX_VALUE *
						   emb_info.k2);

				data.encoder[0] =
				    (unsigned long int) FETCH4BYTES(data.
								    databytes,
								    8) /
				    emb_info.array_island_k1[0];
				data.encoder[1] =
				    (unsigned long int) FETCH4BYTES(data.
								    databytes,
								    12) /
				    emb_info.array_island_k1[1];
				data.encoder[2] =
				    (unsigned long int) FETCH4BYTES(data.
								    databytes,
								    16) /
				    emb_info.array_island_k1[2];
				data.encoder[3] =
				    (unsigned long int) FETCH4BYTES(data.
								    databytes,
								    20) /
				    emb_info.array_island_k1[3];
				if (cfg.verbose) {
					// TODO: improve logging and printf debug behaviour
					printf
					    ("contacolpi1: %f, contacolpi2: %f, ",
					     data.encoder[0], data.encoder[1]);
					printf
					    ("contacolpi3: %f, contacolpi4: %f, ",
					     data.encoder[2], data.encoder[3]);
					printf
					    ("voltage value: %f, current value: %d\n",
					     data.voltage, data.current);
				}

				if (cfg.verbose) {
					int i;
					// TODO: take the log util functions from netsukuku src
					// TODO: improve logging and printf debug behaviour
					// printf("catch start code: %#x\n", data.start);
					// printf("catch len code: %#x\n",   data.length);
					// printf("catch cmd  code: %#x\n",  data.cmd);
					for (i = 0; i < 24; i++) {
						printf("byte[%d]: %#x\n",
						       i, data.databytes[i]);
					}
				}

				/* if the checksum given by the plc is the same we have 
				 * calculated send ack */
				if ((unsigned char) calculateBCC(data) ==
				    (unsigned char) data.checksum) {
					/* compile the response data record with the ACK byte
					 * the response is the same record except for the first 
					 * data byte that is ACK
					 */
					memcpy(&data_response, &data,
					       sizeof(data));
					data_response.databytes[0] = ACK;
					connect_db(cfg.dsn, cfg.dbuser,
						   cfg.dbpass);
					if (cfg.polling)
						get_embedded_infos();
					/* TODO: do all the processing SQL things */
					do_sql_things(data);
					disconnect_db();
					if (cfg.verbose)
						printf("ok, sending ACK...\n");
					/* send response */
					send_response(portfd, data_response);
				} else {
					memcpy(&data_response, &data,
					       sizeof(data));
					data_response.databytes[0] = NACK;
					//if(cfg.polling)       get_embedded_infos();
					//do_sql_things(data);
					if (cfg.verbose)
						printf("ok, sending NACK...\n");
					/* send response */
					send_response(portfd, data_response);
				}

				setzero(&data, sizeof(data));
				setzero(&data_response, sizeof(data_response));

				continue;
			}

			countbyte++;

		}

	}

	close(portfd);

}