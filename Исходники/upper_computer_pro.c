// 20-2-2016 添加数据库的相关处理
int proccess_upper_cmpt_discussion_parameter( uint16_t protocol_type, void *data, uint32_t data_len ) //后期可能需要修改11/10。
{
    tcmpt_discuss_parameter qu_dis_para, set_dis_para;
    uint16_t send_data_len = 0; // 协议数据负载的长度
    thost_system_set set_sys; // 系统配置文件的格式

    if ( -1 == system_db_queue_configure_system_table( &set_sys ))
    {   // load from memory(system.dat)
        memcpy( &set_sys, &gset_sys, sizeof(thost_system_set));
    }

    if((protocol_type & CMPT_MSG_TYPE_MARK) == CMPT_MSG_TYPE_QUERY )
    {
        qu_dis_para.chairman_first = set_sys.chman_first ? ENABLE_VAL : FORBID_VAL;
        qu_dis_para.chair_music = set_sys.chman_music ? ENABLE_VAL : FORBID_VAL;
        qu_dis_para.auto_close = set_sys.auto_close ? ENABLE_VAL : FORBID_VAL;
        qu_dis_para.discuss_mode = set_sys.discuss_mode & 0x07;
        qu_dis_para.limit_speak_num = set_sys.speak_limit & 0xff;
        qu_dis_para.limit_apply_num = set_sys.apply_limit & 0xff;
        qu_dis_para.limit_chm_time = set_sys.chman_limitime ? ENABLE_VAL : FORBID_VAL;
        qu_dis_para.limit_vip_time = set_sys.vip_limitime ? ENABLE_VAL : FORBID_VAL;
        qu_dis_para.limit_speak_time = set_sys.spk_limtime & 0x3f;
        send_data_len = sizeof(tcmpt_discuss_parameter);

        send_upper_computer_command( CMPT_MSG_TYPE_RESPONSE |CMPT_MSG_TYPE_QUERY, \
                                     DISCUSSION_PARAMETER, &qu_dis_para, send_data_len );
    }
    else if((protocol_type & CMPT_MSG_TYPE_MARK) == CMPT_MSG_TYPE_SET )// 设置保存系统状态值并设置系统状态
    {
        get_host_upper_cmpt_data( &set_dis_para, data, CMPT_DATA_OFFSET, sizeof(tcmpt_discuss_parameter));
        DEBUG_RECV( &set_dis_para, sizeof(tcmpt_discuss_parameter), "Dis Param ");

        send_upper_computer_command( CMPT_MSG_TYPE_RESPONSE |CMPT_MSG_TYPE_SET, \
                                     DISCUSSION_PARAMETER, NULL, 0 ); // 第三个与第四个参数与协议有些出入，这里是根据黄工代码写的。协议是数据单元仅一个字节0，设置成功；非零设置失败。而黄工的没有数据单元，故这里写NULL

        if( set_dis_para.discuss_mode == UPPER_CMPT_DISCUSS_FREE_MODE )// 数字会议系统没有自由模式
        {
            terminal_start_discuss( false );
            return 0;
        }

        // 保存配置文件
        if( (profile_dis_param_save_to_ram( &gset_sys, &set_dis_para ) != -1) && (-1 != profile_system_file_write_gb_param( profile_file_fd, &gset_sys )) )
        {
            Fflush( profile_file_fd );
            // 设置系统状态
            uint8_t temp_status = set_dis_para.auto_close;
            if( temp_status != set_sys.auto_close )
            {
                // 自动关闭麦克风
                find_func_command_link( MENUMENT_USE, MENU_AUTO_CLOSE_CMD, 0, &temp_status, 1 );
            }

            temp_status = set_dis_para.discuss_mode;
            if( temp_status != set_sys.discuss_mode )
            {
                // 设置系统讨论模式
                DEBUG_INFO("discuss mode = %d", temp_status);
                find_func_command_link( MENUMENT_USE, MENU_DISC_MODE_SET_CMD, 0, &temp_status, 1 );
            }

            temp_status = set_dis_para.limit_speak_num;
            if( temp_status != set_sys.speak_limit )
            {
                // 设置限制的发言人数
                find_func_command_link( MENUMENT_USE, MENU_SPK_LIMIT_NUM_SET, 0, &temp_status, 1 );
            }

            temp_status = set_dis_para.limit_apply_num;
            if( temp_status != set_sys.apply_limit )
            {
                // 设置限制申请人数
                find_func_command_link( MENUMENT_USE, MUNU_APPLY_LIMIT_NUM_SET, 0, &temp_status, 1 );
            }

            // 限时设置
            terminal_limit_speak_time_set( 0, NULL, 0 );

            // 设置会议讨论状态
            terminal_start_discuss( false );

            //更新数据库系统配置信息
            system_db_update_configure_system_table( gset_sys );
        }
    }

    terminal_main_state_send( 0, NULL, 0 );

    return 0;
}