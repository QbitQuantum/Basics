void data_read(int dev_fd, FILE *file_fd)
{
	int cnt = 0;
	int tmp;
	int offs = 0;
	int drop = 10;

	/* Write TS info the file header.		*/
	/* pktsize mode aggr_pkts_num tmstmp_offset	*/
	sprintf(data_buff,"%d %d %d %d %d %d",
		TSU_TOOL_STAMP,g_buff_info.pkt_size,g_buff_info.aggr_mode,
		g_buff_info.aggr_num_packets,
		g_buff_info.aggr_mode2_tmstmp_off, g_frequency);
	tmp = strlen(data_buff);
	while(tmp < FILE_HDR_SIZE)
		data_buff[tmp++] = ' ';
	data_buff[tmp] = '\0';

	if(!g_raw_mode)
		cnt = fwrite(data_buff,1,strlen(data_buff),file_fd);
	else
		cnt = fwrite(data_buff,1,strlen(data_buff),g_stat_fd);

	if(cnt != strlen(data_buff)) {
		fprintf(stderr,"Error wrting file header.\n");
		return;
        }

	/* Calculate the values of g_ts_data_size & g_tms_data_size.	*/
	if(g_raw_mode) {
		if(g_buff_info.aggr_mode == aggrMode1) {
			g_ts_data_size =
				(g_buff_info.pkt_size *
				 g_buff_info.aggr_num_packets);
			g_tms_data_size = (TIMESTAMP_SIZE *
					   g_buff_info.aggr_num_packets);
		}
		else if(g_buff_info.aggr_mode == aggrMode2) {
			g_ts_data_size = g_buff_info.pkt_size;
			g_tms_data_size = g_buff_info.aggr_mode2_tmstmp_off;
		}
		else { /* Aggregation disabled.	*/
			g_ts_data_size = g_buff_info.pkt_size;
			g_tms_data_size = TIMESTAMP_SIZE;
		}
	} else {
		g_ts_data_size = g_data_blk_sz;
		g_tms_data_size = 0;
	}

	/* Setup frequency.		*/
        if(ioctl(dev_fd,MVTSU_IOCFREQSET,&g_frequency) < 0) {
		fprintf(stderr,"Error configuring port frequency.\n");
		goto done;
	}

//	fprintf(stderr,"g_raw_mode = %d, g_ts_data_size = %d, g_tms_data_size = %d.\n",
//	       g_raw_mode, g_ts_data_size,g_tms_data_size);
	cnt = 0;
	while(1) {

		if(offs != 0)
			fprintf(stderr,"offs = %d.\n");
		tmp = single_read_write(READ,dev_fd,data_buff + offs,
					g_data_blk_sz - offs);
		if(tmp < 0) {
			fprintf(stderr,"Error reading from source device / file.\n");
			break;
		}
		if(drop) {
			drop--;
			continue;
		}

		cnt += tmp;
		if(cnt == 0)
			break;
		while(cnt >= (g_ts_data_size + g_tms_data_size)) {
 //                       fprintf(stderr,"cnt - %d, ",cnt);
			tmp = 0;
			if(g_tms_data_size > 0) {
				if(g_buff_info.aggr_mode == aggrMode2) {
//					fprintf(stderr,"TMSW = %d, ",offs);
					/* write only the timestamp part.	*/
					tmp = single_fread_fwrite(WRITE,g_stat_fd,
								  data_buff + offs,
						    TIMESTAMP_SIZE);
					if(tmp < TIMESTAMP_SIZE) {
						fprintf(stderr,"Error writing to timestamps file.\n");
						goto done;
					}
				} else {
					tmp = single_fread_fwrite(WRITE,g_stat_fd,
								data_buff + offs,
								g_tms_data_size);
					if(tmp < g_tms_data_size) {
						fprintf(stderr,"Error writing to timestamps file.\n");
						goto done;
					}
				}

				offs += tmp;
			}
//			fprintf(stderr,"TSDW = %d.\n",offs);
			tmp = single_fread_fwrite(WRITE,file_fd,data_buff + offs,
						g_ts_data_size);
			if(tmp < g_ts_data_size) {
				fprintf(stderr,"Error writing to data file.\n");
				goto done;
			}
			offs += g_ts_data_size;
			cnt -= (g_ts_data_size + g_tms_data_size);
		}

		if(cnt > 0) {
			memmove(data_buff,data_buff + offs, cnt);
			offs = cnt;
		}
		else {
			offs = 0;
		}
	}
done:
	return;
}