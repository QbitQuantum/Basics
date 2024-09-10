u16 ui_video_m_get_video_icon(u16 *p_filename)
{
    u16  id    = IM_M_ICON_AVI;
    u16 *p_tip = NULL;
    u8  *p_ext = NULL;

    if(NULL == p_filename)
    {
        return id;
    }

    p_tip = uni_strrchr(p_filename, char_asc2uni('.'));

    if(NULL == p_tip)
    {
        return id;
    }

    p_ext = (u8 *)mtos_malloc(uni_strlen(p_tip) + 1);

    str_uni2asc(p_ext, p_tip);

    if(STRCMPI(p_ext, ".AVI") == 0)
    {
        id = IM_M_ICON_AVI;
    }
    else if(STRCMPI(p_ext, ".MKV") == 0)
    {
        id = IM_M_ICON_MKV;
    }
    else if(STRCMPI(p_ext, ".MP4") == 0)
    {
        id = IM_M_ICON_MP4;
    }
    else if(STRCMPI(p_ext, ".M2TS") == 0)
    {
        id = IM_M_ICON_M2TS;
    }
    else if(STRCMPI(p_ext, ".F4V") == 0)
    {
        id = IM_M_ICON_F4V;
    }  
    else if(STRCMPI(p_ext, ".3GP") == 0)
    {
        id = IM_M_ICON_3GP;
    }  
    else if(STRCMPI(p_ext, ".MOV") == 0)
    {
        id = IM_M_ICON_MOV;
    }  
    else if(STRCMPI(p_ext, ".FLV") == 0)
    {
        id = IM_M_ICON_FLV;
    }  
    else if(STRCMPI(p_ext, ".TS") == 0)
    {
        id = IM_M_ICON_TS;
    }  
    else if(STRCMPI(p_ext, ".MPG") == 0)
    {
        id = IM_M_ICON_MPG;
    }
    mtos_free(p_ext);

    return id;
}