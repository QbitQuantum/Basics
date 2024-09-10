void read_code(void) {
	
	int type, tr_num, sp, i, src, dest, val;
	int* ptr = 0;
	
	while(1) {
		type 	= get_int();
		if (type == END_OF_FILE_TYPE) break;
		else if (type == DIST_TYPE){
			src = get_int();
			dest = get_int();
			val = get_int();
			ptr = ((int*)DIST_TABLE_BASE) + src*USED_INDICIES + dest;
			*ptr = val;
		}
		else {
			tr_num	= get_int();
			sp 		= get_int();
			i		= get_int();
			if(type == STOP_DIST_TYPE) {
				val		= get_int();
				ptr = ((int*)STOP_DIST_TABLE_BASE) + tr_num*USED_TR_SPEEDS*2 + sp*2 + i;
				*ptr = val;
			}
			else if(type == REL_VEL_TYPE) {
				val 	= get_int();
				ptr = ((int*)REL_VEL_TABLE_BASE) + tr_num*USED_TR_SPEEDS*2 + sp*2 + i;
				*ptr = val;
			}
			else if(type == AVG_VEL_TYPE) {
				val 	= get_int();
				ptr = ((int*)AVG_VEL_TABLE_BASE) + tr_num*USED_TR_SPEEDS*2 + sp*2 + i;
				*ptr = val;
			}
			else if (type == ACC_TIME_TYPE){
				int sp2 = get_int();
				val		= get_int();
				ptr = ((int*)ACC_TIME_TABLE_BASE) + tr_num*USED_TR_SPEEDS*2*USED_TR_SPEEDS + sp*2*USED_TR_SPEEDS + i*USED_TR_SPEEDS + sp2;
				*ptr = val;
			}
			else {
				src		= get_int();
				dest	= get_int();
				val		= get_int();
				if (type == VEL_COUNT_TYPE) {
					ptr = 	((int*)VEL_COUNT_TABLE_BASE) + tr_num*USED_TR_SPEEDS*2*USED_INDICIES*USED_INDICIES +
							sp*2*USED_INDICIES*USED_INDICIES + i*USED_INDICIES*USED_INDICIES + src*USED_INDICIES + dest;
				}
				else {
					ptr = 	((int*)VEL_TICKS_TABLE_BASE) + tr_num*USED_TR_SPEEDS*2*USED_INDICIES*USED_INDICIES +
							sp*2*USED_INDICIES*USED_INDICIES + i*USED_INDICIES*USED_INDICIES + src*USED_INDICIES + dest;	
				}
				*ptr = val;
			}
		}
	}
	SHUTDOWN();
}