void AutoChannelConfig(uint8_t ch,best_cfg* final_result)
{
	uint16_t div, i;
	uint16_t current = 1;
	S_TK_CH_CFG ch_cfg = {1, 0, 0xFFFF, 0x0000};
	uint8_t sen_level, sen_state,tmp_div;
	uint16_t sen_data;	
	int8_t tmp_score;
	uint8_t tmp_cur;
	uint8_t progress=0;

	final_result->current = 1;
	final_result->div = 0;
	final_result->base = 0;
	final_result->diff = 0;

	base_rank[0].val = 0xFFFF;							
	base_rank[0].div = 0;
	base_rank[0].current = 1;
	diff_rank[0].val = 0;
	diff_rank[0].div = 0;
	diff_rank[0].current = 1;
	
			progress=20;
			SendChars((uint8_t *)&progress,sizeof(progress));

			for(div = 1; div < 12; div++) {			
				for(current = 1; current <= 15; current++) {
					ch_cfg.u8Level = current;
					ch_cfg.u8Div = div;
					TK_ConfigChannel(ch, &ch_cfg);		
					result[div][current - 1].level_off = 0;	
					result[div][current - 1].data_off = 0;					
		
					for(i = 0; i < 2; i++) {
						complete = 0;
						TK_Start(1 << ch);
						while(complete != 1);
						TK_ReadStatus(&sen_level, &sen_state, NULL);
						sen_data = TK_ReadData(ch);
						if(sen_state != 0 || sen_data == 0 || sen_data == 0xFFFF) {
							result[div][current - 1].level_off = 0;	
							result[div][current - 1].data_off = 0;
							break;
						} else {
							result[div][current - 1].level_off += sen_level;
							result[div][current - 1].data_off += (sen_data >> 1);						
						}									
					}
					result[div][current - 1].level_off >>= 1;
				}
			}
			
			
			progress=40;
			SendChars((uint8_t *)&progress,sizeof(progress));
	
		 	while(1)
			{	
				if(kbhit())												
					if(GetChar()==progress)															
						break;				
			} 	

			for(div = 1; div < 12; div++) {				
				for(current = 1; current <= 15; current++) {
					ch_cfg.u8Level = current;
					ch_cfg.u8Div = div;
					TK_ConfigChannel(ch, &ch_cfg);
		
					result[div][current - 1].level_on = 0;	
					result[div][current - 1].data_on = 0;					
					if(result[div][current - 1].level_off == 0)
						continue;
					for(i = 0; i < 2; i++) {
						complete = 0;
						TK_Start(1 << ch);
						while(complete != 1);
						TK_ReadStatus(&sen_level, &sen_state, NULL);
						sen_data = TK_ReadData(ch);
						if(sen_state != 0 || sen_data == 0 || sen_data == 0xFFFF) {
							result[div][current - 1].level_on = 0;	
							result[div][current - 1].data_on = 0;
							break;
						} else {
							result[div][current - 1].level_on += sen_level;
							result[div][current - 1].data_on += (sen_data >> 1);
						
						}									
					}
					result[div][current - 1].level_on >>= 1;
				}
			}


			// calculate sense level, timer divider, and change current score
			for(div = 1; div < 12; div++) {
				for(current = 1; current <= 15; current++) {

					result[div][current - 1].score = 0;

					if((result[div][current - 1].level_off != 0) &&
					   (result[div][current - 1].level_on != 0) &&	
					   (result[div][current - 1].data_on > result[div][current - 1].data_off)) {
						
						result[div][current - 1].score += (div_score[div] + cur_score[current] + lvl_score[result[div][current - 1].level_off]);
		
					}
				}
			}	
			
			// find out entry with highest diff
			for(div = 1; div < 12; div++) {
				for(current = 1; current <= 15; current++) {
					if(result[div][current - 1].score != 0) {
						if(((result[div][current - 1].data_on - result[div][current - 1].data_off) > diff_rank[0].val) &&
						   (result[div][current - 1].data_on > result[div][current - 1].data_off) &&
						   ((result[div][current - 1].data_on - result[div][current - 1].data_off) > 0x100)) {
							diff_rank[0].val = (result[div][current - 1].data_on - result[div][current - 1].data_off);
							diff_rank[0].current = current;
							diff_rank[0].div = div;
							break;
						}	
					}
				}
			}				

		   progress=60;
			SendChars((uint8_t *)&progress,sizeof(progress));

			// give score base on the differences
			for(div = 1; div < 12; div++) {
				for(current = 1; current <= 15; current++) {
					if(result[div][current - 1].score > 0) {											
						if(result[div][current - 1].data_on < result[div][current - 1].data_off)
							result[div][current - 1].score -=	100;
						else if((result[div][current - 1].data_on - result[div][current - 1].data_off) < 0x50)
							result[div][current - 1].score -=	100;	
						else
							result[div][current - 1].score += (8 - (diff_rank[0].val - (result[div][current - 1].data_on - result[div][current - 1].data_off)) / 0x800);
					}
				}
			}

			
			// find out lowest base
			for(div = 1; div < 12; div++) {
				for(current = 1; current <= 15; current++) {
					if(result[div][current - 1].score > 0) {
						if((result[div][current - 1].data_off < base_rank[0].val) && (result[div][current - 1].data_off < 0xF000)) {
							base_rank[0].val = result[div][current - 1].data_off;
							base_rank[0].current = current;
							base_rank[0].div = div;
							break;
						}
	
					}
				}
			}

			progress=80;
			SendChars((uint8_t *)&progress,sizeof(progress));

			// give score base on the differences
			for(div = 1; div < 12; div++) {
				for(current = 1; current <= 15; current++) {
					if(result[div][current - 1].score > 0) {											
							result[div][current - 1].score += (4 - (diff_rank[0].val - result[div][current - 1].data_off) / 0x1000);
					}
				}
			}

			// find the entry with highest score
			tmp_score = 0;
			tmp_cur = 1;  // eliminate compilation warning
			tmp_div = 0;						 // eliminate compilation warning
			for(div = 1; div < 12; div++) {
				for(current = 1; current <= 15; current++) {
					if(result[div][current - 1].score > tmp_score) {
						tmp_score = result[div][current - 1].score;
						tmp_div = div;
						tmp_cur = current;
							
					}
				}
			}

		   	progress=100;
			SendChars((uint8_t *)&progress,sizeof(progress));

			if(tmp_score == 0) {
				final_result->base=0;
				final_result->diff=0;
				final_result->current=0;
				final_result->div=0;
			} else {
				final_result->base = result[tmp_div][tmp_cur - 1].data_off;
				final_result->diff = result[tmp_div][tmp_cur - 1].data_on - result[tmp_div][tmp_cur - 1].data_off;
				final_result->current = tmp_cur;
				final_result->div = tmp_div;
			}
}