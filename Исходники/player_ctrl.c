/* --------------------------------------------------------------------------*/
int player_get_media_info(int pid, media_info_t *minfo)
{
    play_para_t *player_para;
    player_status sta;

    player_para = player_open_pid_data(pid);
    if (player_para == NULL) {
        return PLAYER_NOT_VALID_PID;    /*this data is 0 for default!*/
    }

    sta = get_player_state(player_para);
    if (sta >= PLAYER_ERROR && sta <= PLAYER_EXIT) {
        player_close_pid_data(pid);
        return PLAYER_INVALID_CMD;
    }

    MEMSET(minfo, 0, sizeof(media_info_t));
    MEMCPY(minfo, &player_para->media_info, sizeof(media_info_t));

    log_print("[player_get_media_info]video_num=%d vidx=%d\n", minfo->stream_info.total_video_num, minfo->stream_info.cur_video_index);
    player_close_pid_data(pid);

    return PLAYER_SUCCESS;
}