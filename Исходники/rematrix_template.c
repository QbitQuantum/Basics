static RENAME(mix_any_func_type) *RENAME(get_mix_any_func)(SwrContext *s){
    if(   s->out_ch_layout == AV_CH_LAYOUT_STEREO && (s->in_ch_layout == AV_CH_LAYOUT_5POINT1 || s->in_ch_layout == AV_CH_LAYOUT_5POINT1_BACK)
       && s->matrix[0][2] == s->matrix[1][2] && s->matrix[0][3] == s->matrix[1][3]
       && !s->matrix[0][1] && !s->matrix[0][5] && !s->matrix[1][0] && !s->matrix[1][4]
    )
        return RENAME(mix6to2);

    if(   s->out_ch_layout == AV_CH_LAYOUT_STEREO && s->in_ch_layout == AV_CH_LAYOUT_7POINT1
       && s->matrix[0][2] == s->matrix[1][2] && s->matrix[0][3] == s->matrix[1][3]
       && !s->matrix[0][1] && !s->matrix[0][5] && !s->matrix[1][0] && !s->matrix[1][4]
       && !s->matrix[0][7] && !s->matrix[1][6]
    )
        return RENAME(mix8to2);

    return NULL;
}