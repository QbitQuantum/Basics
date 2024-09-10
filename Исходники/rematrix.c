int swr_rematrix_init(SwrContext *s){
    int i, j, out_i;
    double matrix[64][64]={{0}};
    int64_t unaccounted= s->in_ch_layout & ~s->out_ch_layout;
    double maxcoef=0;

    for(i=0; i<64; i++){
        if(s->in_ch_layout & s->out_ch_layout & (1LL<<i))
            matrix[i][i]= 1.0;
    }

    if(!sane_layout(s->in_ch_layout)){
        av_log(s, AV_LOG_ERROR, "Input channel layout isnt supported\n");
        return AVERROR(EINVAL);
    }
    if(!sane_layout(s->out_ch_layout)){
        av_log(s, AV_LOG_ERROR, "Output channel layout isnt supported\n");
        return AVERROR(EINVAL);
    }

//FIXME implement dolby surround
//FIXME implement full ac3


    if(unaccounted & AV_CH_FRONT_CENTER){
        if((s->out_ch_layout & AV_CH_LAYOUT_STEREO) == AV_CH_LAYOUT_STEREO){
            matrix[ FRONT_LEFT][FRONT_CENTER]+= M_SQRT1_2;
            matrix[FRONT_RIGHT][FRONT_CENTER]+= M_SQRT1_2;
        }else
            av_assert0(0);
    }
    if(unaccounted & AV_CH_LAYOUT_STEREO){
        if(s->out_ch_layout & AV_CH_FRONT_CENTER){
            matrix[FRONT_CENTER][ FRONT_LEFT]+= M_SQRT1_2;
            matrix[FRONT_CENTER][FRONT_RIGHT]+= M_SQRT1_2;
            if(s->in_ch_layout & AV_CH_FRONT_CENTER)
                matrix[FRONT_CENTER][ FRONT_CENTER] = s->clev*sqrt(2);
        }else
            av_assert0(0);
    }

    if(unaccounted & AV_CH_BACK_CENTER){
        if(s->out_ch_layout & AV_CH_BACK_LEFT){
            matrix[ BACK_LEFT][BACK_CENTER]+= M_SQRT1_2;
            matrix[BACK_RIGHT][BACK_CENTER]+= M_SQRT1_2;
        }else if(s->out_ch_layout & AV_CH_SIDE_LEFT){
            matrix[ SIDE_LEFT][BACK_CENTER]+= M_SQRT1_2;
            matrix[SIDE_RIGHT][BACK_CENTER]+= M_SQRT1_2;
        }else if(s->out_ch_layout & AV_CH_FRONT_LEFT){
            matrix[ FRONT_LEFT][BACK_CENTER]+= s->slev*M_SQRT1_2;
            matrix[FRONT_RIGHT][BACK_CENTER]+= s->slev*M_SQRT1_2;
        }else if(s->out_ch_layout & AV_CH_FRONT_CENTER){
            matrix[ FRONT_CENTER][BACK_CENTER]+= s->slev*M_SQRT1_2;
        }else
            av_assert0(0);
    }
    if(unaccounted & AV_CH_BACK_LEFT){
        if(s->out_ch_layout & AV_CH_BACK_CENTER){
            matrix[BACK_CENTER][ BACK_LEFT]+= M_SQRT1_2;
            matrix[BACK_CENTER][BACK_RIGHT]+= M_SQRT1_2;
        }else if(s->out_ch_layout & AV_CH_SIDE_LEFT){
            if(s->in_ch_layout & AV_CH_SIDE_LEFT){
                matrix[ SIDE_LEFT][ BACK_LEFT]+= M_SQRT1_2;
                matrix[SIDE_RIGHT][BACK_RIGHT]+= M_SQRT1_2;
            }else{
            matrix[ SIDE_LEFT][ BACK_LEFT]+= 1.0;
            matrix[SIDE_RIGHT][BACK_RIGHT]+= 1.0;
            }
        }else if(s->out_ch_layout & AV_CH_FRONT_LEFT){
            matrix[ FRONT_LEFT][ BACK_LEFT]+= s->slev;
            matrix[FRONT_RIGHT][BACK_RIGHT]+= s->slev;
        }else if(s->out_ch_layout & AV_CH_FRONT_CENTER){
            matrix[ FRONT_CENTER][BACK_LEFT ]+= s->slev*M_SQRT1_2;
            matrix[ FRONT_CENTER][BACK_RIGHT]+= s->slev*M_SQRT1_2;
        }else
            av_assert0(0);
    }

    if(unaccounted & AV_CH_SIDE_LEFT){
        if(s->out_ch_layout & AV_CH_BACK_LEFT){
            matrix[ BACK_LEFT][ SIDE_LEFT]+= 1.0;
            matrix[BACK_RIGHT][SIDE_RIGHT]+= 1.0;
        }else if(s->out_ch_layout & AV_CH_BACK_CENTER){
            matrix[BACK_CENTER][ SIDE_LEFT]+= M_SQRT1_2;
            matrix[BACK_CENTER][SIDE_RIGHT]+= M_SQRT1_2;
        }else if(s->out_ch_layout & AV_CH_FRONT_LEFT){
            matrix[ FRONT_LEFT][ SIDE_LEFT]+= s->slev;
            matrix[FRONT_RIGHT][SIDE_RIGHT]+= s->slev;
        }else if(s->out_ch_layout & AV_CH_FRONT_CENTER){
            matrix[ FRONT_CENTER][SIDE_LEFT ]+= s->slev*M_SQRT1_2;
            matrix[ FRONT_CENTER][SIDE_RIGHT]+= s->slev*M_SQRT1_2;
        }else
            av_assert0(0);
    }

    if(unaccounted & AV_CH_FRONT_LEFT_OF_CENTER){
        if(s->out_ch_layout & AV_CH_FRONT_LEFT){
            matrix[ FRONT_LEFT][ FRONT_LEFT_OF_CENTER]+= 1.0;
            matrix[FRONT_RIGHT][FRONT_RIGHT_OF_CENTER]+= 1.0;
        }else if(s->out_ch_layout & AV_CH_FRONT_CENTER){
            matrix[ FRONT_CENTER][ FRONT_LEFT_OF_CENTER]+= M_SQRT1_2;
            matrix[ FRONT_CENTER][FRONT_RIGHT_OF_CENTER]+= M_SQRT1_2;
        }else
            av_assert0(0);
    }

    //FIXME quantize for integeres
    for(out_i=i=0; i<64; i++){
        double sum=0;
        int in_i=0;
        int ch_in=0;
        for(j=0; j<64; j++){
            s->matrix[out_i][in_i]= matrix[i][j];
            s->matrix32[out_i][in_i]= lrintf(matrix[i][j] * 32768);
            if(matrix[i][j]){
                s->matrix_ch[out_i][++ch_in]= in_i;
                sum += fabs(matrix[i][j]);
            }
            if(s->in_ch_layout & (1ULL<<j))
                in_i++;
        }
        s->matrix_ch[out_i][0]= ch_in;
        maxcoef= FFMAX(maxcoef, sum);
        if(s->out_ch_layout & (1ULL<<i))
            out_i++;
    }
    if(s->rematrix_volume  < 0)
        maxcoef = -s->rematrix_volume;

    if((   s->out_sample_fmt < AV_SAMPLE_FMT_FLT
        || s->int_sample_fmt < AV_SAMPLE_FMT_FLT) && maxcoef > 1.0){
        for(i=0; i<SWR_CH_MAX; i++)
            for(j=0; j<SWR_CH_MAX; j++){
                s->matrix[i][j] /= maxcoef;
                s->matrix32[i][j]= lrintf(s->matrix[i][j] * 32768);
            }
    }

    if(s->rematrix_volume > 0){
        for(i=0; i<SWR_CH_MAX; i++)
            for(j=0; j<SWR_CH_MAX; j++){
                s->matrix[i][j] *= s->rematrix_volume;
                s->matrix32[i][j]= lrintf(s->matrix[i][j] * 32768);
            }
    }

    for(i=0; i<av_get_channel_layout_nb_channels(s->out_ch_layout); i++){
        for(j=0; j<av_get_channel_layout_nb_channels(s->in_ch_layout); j++){
            av_log(NULL, AV_LOG_DEBUG, "%f ", s->matrix[i][j]);
        }
        av_log(NULL, AV_LOG_DEBUG, "\n");
    }
    return 0;
}