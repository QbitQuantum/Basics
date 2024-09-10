static int32 ini_write_mode_value(INI_FILE *fp, int32 modu, int8 * puc_var, int8 * puc_value)
{
	int32 l_len;
	int32 ret;
	int8 auc_tmp[MAX_READ_LINE_NUM + 1] = {0};
	int8 auc_mode_var[INI_STR_MODU_LEN + 1] = {0};
	int8 *puc_val = NULL;
	int8 auc_change_bin[INI_STR_MODU_LEN * 2 + 1] = {0};
	int8 auc_cmd[INI_STR_MODU_LEN * 4 + 1] = {0};
    int16 search_var_len;

	switch (modu)
	{
		case INI_MODU_WIFI:			 
			strncpy(auc_mode_var, INI_MODE_VAR_WIFI, INI_STR_MODU_LEN);
			if ('0' > puc_value[0] || '2' < puc_value[0])
			{
				INI_ERROR("not support mode!!!");
				return INI_FAILED;
			}
			break;
		case INI_MODU_GNSS:			 
			if ('0' > puc_value[0] || '1' < puc_value[0])
			{
				INI_ERROR("not support mode!!!");
				return INI_FAILED;
			}
			strncpy(auc_mode_var, INI_MODE_VAR_GNSS, INI_STR_MODU_LEN);
			break;
		case INI_MODU_BT:			 
			if ('0' != puc_value[0])
			{
				INI_ERROR("not support mode!!!");
				return INI_FAILED;
			}
			strncpy(auc_mode_var, INI_MODE_VAR_BT, INI_STR_MODU_LEN);
			break;
		case INI_MODU_FM:			 
			if ('0' != puc_value[0])
			{
				INI_ERROR("not support mode!!!");
				return INI_FAILED;
			}
			strncpy(auc_mode_var, INI_MODE_VAR_FM, INI_STR_MODU_LEN);
			break;
		case INI_MODU_WIFI_PLAT:			 
			if ('0' != puc_value[0])
			{
				INI_ERROR("not support mode!!!");
				return INI_FAILED;
			}
			strncpy(auc_mode_var, INI_MODE_VAR_WIFI_PLAT, INI_STR_MODU_LEN);
			break;
		case INI_MODU_BFG_PLAT:			 
			if ('0' != puc_value[0])
			{
				INI_ERROR("not support mode!!!");
				return INI_FAILED;
			}
			strncpy(auc_mode_var, INI_MODE_VAR_BFG_PLAT, INI_STR_MODU_LEN);
			break;
		default :
			INI_ERROR("not suport modu type!!!");
			break;
	}

	while(1)
	{
        ret = ini_readline_func(fp, auc_tmp);
        if (INI_FAILED == ret)
        {
            INI_ERROR("have end of .ini file!!!");
            return INI_FAILED;
        }

		if (NULL != strstr(auc_tmp, INI_STR_WIFI_NORMAL0))
		{
			INI_ERROR("not find %s!!!", auc_mode_var);
			return INI_FAILED;
		}
		
        ret = ini_check_str(fp, auc_tmp, auc_mode_var);
        if (INI_SUCC == ret)
        {
            INI_DEBUG("have found %s", auc_mode_var);
            break;
        }
        else
        {
            continue;
        }
	}

	puc_val = strstr(auc_tmp, "=");
	if (NULL == puc_val)
	{
		INI_ERROR("has not find = in %s", auc_tmp);
		return INI_FAILED;
	}
	if (INI_FAILED == ini_check_value(puc_val + 1))
	{
		INI_ERROR("not support to write :%s:", auc_tmp);
		return INI_FAILED;
	}
	
	l_len = strlen(auc_tmp);
	search_var_len = strlen(puc_var);
    strncpy(&auc_tmp[search_var_len+1], puc_value, 1);

	if (INI_FAILED == fseek(fp, -l_len, SEEK_CUR))
	{
		INI_ERROR("file seek failed!!!");
		return INI_FAILED;
	}
	if (fputs(auc_tmp, fp))
	{
		INI_DEBUG("puc_write_val :%s: ok", auc_tmp);
	}
	
    if (INI_MODU_WIFI == modu)
    {
        if ('0' == puc_value[0])
        {
            strncpy(auc_change_bin, INI_SDIOBIN_NORMAL, INI_STR_MODU_LEN * 2);
        }
        else if ('1' == puc_value[0])
        {
            strncpy(auc_change_bin, INI_SDIOBIN_PERFORMANCE, INI_STR_MODU_LEN * 2);
        }
        else if ('2' == puc_value[0])
        {
            strncpy(auc_change_bin, INI_SDIOBIN_CERTIFY, INI_STR_MODU_LEN * 2);
        }
        else
        {
            INI_ERROR("not support to bin type %s", auc_change_bin);
            return INI_FAILED;
        }
        sprintf(auc_cmd, INI_STR_MODU_LEN * 4,"cp %s %s", auc_change_bin, INI_SDIOBIN_DEFAULT);
        INI_INFO("exct %s", auc_cmd);
        system(auc_cmd);
    }

	return INI_SUCC;
}