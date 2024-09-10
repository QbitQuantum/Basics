STATICFNDEF int4 update_trigger_hash_value(char *trigvn, int trigvn_len, char **values, uint4 *value_len, stringkey *set_hash,
					   stringkey *kill_hash, int old_trig_index, int new_trig_index)
{
	sgmnt_addrs		*csa;
	int			hash_index;
	mval			key_val;
	uint4			len;
	mval			mv_hash;
	mval			mv_hash_indx;
	int			num_len;
	char			*ptr;
	int4			result;
	char			tmp_str[MAX_MIDENT_LEN + 1 + MAX_DIGITS_IN_INT];
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	assert(!gv_cur_region->read_only);		/* caller should have already checked this */
	assert(cs_addrs->hasht_tree == gv_target);	/* should have been set up by caller */
	assert(gv_target->root);			/* should have been ensured by caller */
	csa = cs_addrs;
	if ((NULL != strchr(values[CMD_SUB], 'S')) && (set_hash->hash_code != kill_hash->hash_code))
	{
		if (!search_trigger_hash(trigvn, trigvn_len, set_hash, old_trig_index, &hash_index))
		{	/* There has to be an entry with the old hash value, we just looked it up */
			TRHASH_DEFINITION_RETRY_OR_ERROR(set_hash, csa);
		}
		MV_FORCE_UMVAL(&mv_hash, set_hash->hash_code);
		MV_FORCE_UMVAL(&mv_hash_indx, hash_index);
		BUILD_HASHT_SUB_SUB_MSUB_MSUB_CURRKEY(trigvn, trigvn_len,
			LITERAL_HASHTRHASH, STRLEN(LITERAL_HASHTRHASH), mv_hash, mv_hash_indx);
		if (!gvcst_get(&key_val))
		{	/* There has to be a #TRHASH entry */
			TRHASH_DEFINITION_RETRY_OR_ERROR(set_hash, csa);
		}
		assert((MAX_MIDENT_LEN + 1 + MAX_DIGITS_IN_INT) >= key_val.str.len);
		ptr = key_val.str.addr;
		len = MIN(key_val.str.len, MAX_MIDENT_LEN);
		STRNLEN(ptr, len, len);
		ptr += len;
		if ((key_val.str.len == len) || ('\0' != *ptr))
		{	/* We expect $c(0) in the middle of ptr. If we dont find it, this is a restartable situation */
			if (CDB_STAGNATE > t_tries)
				t_retry(cdb_sc_triggermod);
			assert(WBTEST_HELPOUT_TRIGDEFBAD == gtm_white_box_test_case_number);
			rts_error_csa(CSA_ARG(REG2CSA(gv_cur_region)) VARLSTCNT(8) ERR_TRIGDEFBAD, 6, trigvn_len, trigvn,
					LEN_AND_LIT("\"#BHASH\""), mv_hash.str.len, mv_hash.str.addr);
		}
		memcpy(tmp_str, key_val.str.addr, len);
		ptr = tmp_str + len;
		*ptr++ = '\0';
		num_len = 0;
		I2A(ptr, num_len, new_trig_index);
		len += num_len + 1;
		SET_TRIGGER_GLOBAL_SUB_SUB_MSUB_MSUB_STR(trigvn, trigvn_len,
			LITERAL_HASHTRHASH, STRLEN(LITERAL_HASHTRHASH), mv_hash, mv_hash_indx, tmp_str, len, result);
		if (PUT_SUCCESS != result)
			return result;
	}
	if (!search_trigger_hash(trigvn, trigvn_len, kill_hash, old_trig_index, &hash_index))
	{	/* There has to be an entry with the old hash value, we just looked it up */
		TRHASH_DEFINITION_RETRY_OR_ERROR(kill_hash, csa);
	}
	MV_FORCE_UMVAL(&mv_hash, kill_hash->hash_code);
	MV_FORCE_UMVAL(&mv_hash_indx, hash_index);
	BUILD_HASHT_SUB_SUB_MSUB_MSUB_CURRKEY(trigvn, trigvn_len,
		LITERAL_HASHTRHASH, STRLEN(LITERAL_HASHTRHASH), mv_hash, mv_hash_indx);
	if (!gvcst_get(&key_val))
	{	/* There has to be a #TRHASH entry */
		TRHASH_DEFINITION_RETRY_OR_ERROR(kill_hash, csa);
	}
	assert((MAX_MIDENT_LEN + 1 + MAX_DIGITS_IN_INT) >= key_val.str.len);
	ptr = key_val.str.addr;
	len = MIN(key_val.str.len, MAX_MIDENT_LEN);
	STRNLEN(ptr, len, len);
	ptr += len;
	if ((key_val.str.len == len) || ('\0' != *ptr))
	{	/* We expect $c(0) in the middle of ptr. If we dont find it, this is a restartable situation */
		if (CDB_STAGNATE > t_tries)
			t_retry(cdb_sc_triggermod);
		assert(WBTEST_HELPOUT_TRIGDEFBAD == gtm_white_box_test_case_number);
		rts_error_csa(CSA_ARG(REG2CSA(gv_cur_region)) VARLSTCNT(8) ERR_TRIGDEFBAD, 6, trigvn_len, trigvn,
				LEN_AND_LIT("\"#LHASH\""), mv_hash.str.len, mv_hash.str.addr);
	}
	memcpy(tmp_str, key_val.str.addr, len);
	ptr = tmp_str + len;
	*ptr++ = '\0';
	num_len = 0;
	I2A(ptr, num_len, new_trig_index);
	len += num_len + 1;
	SET_TRIGGER_GLOBAL_SUB_SUB_MSUB_MSUB_STR(trigvn, trigvn_len,
		LITERAL_HASHTRHASH, STRLEN(LITERAL_HASHTRHASH), mv_hash, mv_hash_indx, tmp_str, len, result);
	return result;
}