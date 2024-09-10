WP_status upi_stm1_stat_get(WP_U32 stm1id,STRU_UPI_STATICS *p)
{
    WP_status status;
    WP_U16 i;
    STRU_UPI_STATICS pos_fr;
    STRU_SET_INITAIL_CONFIG *initial_cfg = npu_get_initial_cfg_info();
    WP_U32 line_index_base,line_index_counts;

    if(initial_cfg->stru_stm1_cfg_info[stm1id].E1T1type == NPU_MODE_E1)
    {
        line_index_base = stm1id*N_UFE_MAX_LINES_E1/2;
        line_index_counts = (1+stm1id)*N_UFE_MAX_LINES_E1/2;
    }
    else
    {
        line_index_base = stm1id*N_UFE_MAX_LINES_T1/2;
        line_index_counts = (1+stm1id)*N_UFE_MAX_LINES_T1/2;

    }

    if(NPU_VALID == initial_cfg->stru_stm1_cfg_info[stm1id].stm1Valid)
    {
        memset (&pos_fr, 0, sizeof(STRU_UPI_STATICS));
        for(i = line_index_base; i < line_index_counts; i ++)
        {
            if(NPU_VALID == initial_cfg->stru_stm1_cfg_info[stm1id].trunk_info[i-line_index_base].trunkValid)
            {
                memset(p, 0, sizeof(STRU_UPI_STATICS));
                status = upi_stat_get_by_trunk(i,p);
                if(-1 == status)
                {
                    continue;
                }
                if (status)
                {
                    Fprintf("Error upi_stat_get_by_trunk!\n");
                    return status;
                }
                struct_upi_statics_add(&pos_fr, p);
            }
        }
        memcpy((void *)p,(void *)&pos_fr,sizeof(pos_fr));
    }
    else
    {
        Fprintf("This stm1 %d is not configed!\n",stm1id);
        return -1;
    }
    return WP_OK;
}