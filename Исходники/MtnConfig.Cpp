/* ------------------------------------------------------------------------ */
short mtn_cfg_PutText(char *p_blockname, char *p_config,
                      char *p_parameter)
{
    short status;
    short ii, blkno;
    long  config_start_posn;

    status = READERR;
    blkno = -1;

	/* search through the cfg_table for block identified by <p_blockname>	*/
    for (ii=0; ii<cfg_count; ii++)
    {
        // fprintf(stderr, "%d Blkname %s\n", ii, cfg_table[ii].prf_blk_name);
        if (strcmp(p_blockname, cfg_table[ii].prf_blk_name) == 0)
        {
            blkno = ii;
            ii = cfg_count + 1;
        }
    }

    if (blkno == -1)
    {
        // block does not exist, new block will be created at the end of the
        // current file pointed by fp_config.
        // fprintf(stderr, "Block does not exist! New Block is added.\n");
        if (fp_config != NULL)
            fclose(fp_config);
        fopen_s(&fp_config, cfg_file_pathname, "a");
        if (fp_config == NULL)
        {
            sprintf_s(strDebugMessage_MtnConfig, 512, "FILE: %s, LINE: %d, Open file %s error!\n", __FILE__, __LINE__, cfg_file_pathname);
            return MTN_API_ERROR_OPEN_FILE;
        }
        fprintf(fp_config,"# [%s]\n", p_blockname);
        fprintf(fp_config,"# %s <%s>\n", p_config, p_parameter);

        fclose(fp_config);
        // Open the new Configuration file
        mtn_cfg_OpenConfigFile(cfg_file_pathname);
        return MTN_API_OK_ZERO;
    }
    else // block exists
    {
        /* the desired block found, now, move the file pointer to the       */
		/* starting line for that block 									*/
        fseek(fp_config, cfg_table[blkno].start_file_pos, SEEK_SET);

        // Get the current file position
        config_start_posn = ftell(fp_config);

        // The new text will inserted 1 line after the Block
        if(mtn_cfg_insert_text(fp_config, config_start_posn,
                               p_config, p_parameter) != MTN_API_OK_ZERO)
        {
            sprintf_s(strDebugMessage_MtnConfig, 512, "FILE: %s, LINE: %d, Fail to Insert New String!\n",
				__FILE__, __LINE__);
            return MTN_API_ERR_INSERT_STRING;
        }
        status = READOK;
    }
    return (status);
}