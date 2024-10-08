bool ONScripter::doEffect( EffectLink *effect, bool clear_dirty_region )
{
    effect_start_time = SDL_GetTicks();
    if ( effect_counter == 0 ) effect_start_time_old = effect_start_time - 1;
    //printf("effect_counter %d timer between %d %d\n",effect_counter,effect_start_time,effect_start_time_old);
    effect_timer_resolution = effect_start_time - effect_start_time_old;
    effect_start_time_old = effect_start_time;
    
    int effect_no = effect->effect;
    if (effect_cut_flag && (skip_mode & SKIP_NORMAL || ctrl_pressed_status)) 
        effect_no = 1;

    int i, amp;
    int width, width2;
    int height, height2;
    SDL_Rect src_rect = screen_rect, dst_rect = screen_rect;
    SDL_Rect quake_rect = screen_rect;

    /* ---------------------------------------- */
    /* Execute effect */
    //printf("Effect number %d %d\n", effect_no, effect_duration );

    bool not_implemented = false;
    switch ( effect_no ){
      case 0: // Instant display
      case 1: // Instant display
        //drawEffect( &src_rect, &src_rect, effect_dst_surface );
        break;

      case 2: // Left shutter
        width = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=0 ; i<screen_width/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = i * EFFECT_STRIPE_WIDTH;
            src_rect.y = 0;
            src_rect.w = width;
            src_rect.h = screen_height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 3: // Right shutter
        width = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=1 ; i<=screen_width/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = i * EFFECT_STRIPE_WIDTH - width - 1;
            src_rect.y = 0;
            src_rect.w = width;
            src_rect.h = screen_height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 4: // Top shutter
        height = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=0 ; i<screen_height/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = 0;
            src_rect.y = i * EFFECT_STRIPE_WIDTH;
            src_rect.w = screen_width;
            src_rect.h = height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 5: // Bottom shutter
        height = EFFECT_STRIPE_WIDTH * effect_counter / effect_duration;
        for ( i=1 ; i<=screen_height/EFFECT_STRIPE_WIDTH ; i++ ){
            src_rect.x = 0;
            src_rect.y = i * EFFECT_STRIPE_WIDTH - height - 1;
            src_rect.w = screen_width;
            src_rect.h = height;
            drawEffect(&src_rect, &src_rect, effect_dst_surface);
        }
        break;

      case 6: // Left curtain
        width = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_width/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            width2 = width - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_width;
            if ( width2 >= 0 ){
                src_rect.x = i * EFFECT_STRIPE_CURTAIN_WIDTH;
                src_rect.y = 0;
                src_rect.w = width2;
                src_rect.h = screen_height;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      case 7: // Right curtain
        width = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_width/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            width2 = width - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_width;
            if ( width2 >= 0 ){
                if ( width2 > EFFECT_STRIPE_CURTAIN_WIDTH ) width2 = EFFECT_STRIPE_CURTAIN_WIDTH;
                src_rect.x = screen_width - i * EFFECT_STRIPE_CURTAIN_WIDTH - width2;
                src_rect.y = 0;
                src_rect.w = width2;
                src_rect.h = screen_height;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      case 8: // Top curtain
        height = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_height/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            height2 = height - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_height;
            if ( height2 >= 0 ){
                src_rect.x = 0;
                src_rect.y = i * EFFECT_STRIPE_CURTAIN_WIDTH;
                src_rect.w = screen_width;
                src_rect.h = height2;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      case 9: // Bottom curtain
        height = EFFECT_STRIPE_CURTAIN_WIDTH * effect_counter * 2 / effect_duration;
        for ( i=0 ; i<=screen_height/EFFECT_STRIPE_CURTAIN_WIDTH ; i++ ){
            height2 = height - EFFECT_STRIPE_CURTAIN_WIDTH * EFFECT_STRIPE_CURTAIN_WIDTH * i / screen_height;
            if ( height2 >= 0 ){
                src_rect.x = 0;
                src_rect.y = screen_height - i * EFFECT_STRIPE_CURTAIN_WIDTH - height2;
                src_rect.w = screen_width;
                src_rect.h = height2;
                drawEffect(&src_rect, &src_rect, effect_dst_surface);
            }
        }
        break;

      default:
        not_implemented = true;
        
      case 10: // Cross fade
        height = 256 * effect_counter / effect_duration;
        alphaBlend( NULL, ALPHA_BLEND_CONST, height, &dirty_rect.bounding_box );
        break;
        
      case 11: // Left scroll
        width = screen_width * effect_counter / effect_duration;
        src_rect.x = 0;
        dst_rect.x = width;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width - width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);
        
        src_rect.x = screen_width - width - 1;
        dst_rect.x = 0;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 12: // Right scroll
        width = screen_width * effect_counter / effect_duration;
        src_rect.x = width;
        dst_rect.x = 0;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width - width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = 0;
        dst_rect.x = screen_width - width - 1;
        src_rect.y = dst_rect.y = 0;
        src_rect.w = dst_rect.w = width;
        src_rect.h = dst_rect.h = screen_height;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 13: // Top scroll
        width = screen_height * effect_counter / effect_duration;
        src_rect.x = dst_rect.x = 0;
        src_rect.y = 0;
        dst_rect.y = width;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = screen_height - width;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = dst_rect.x = 0;
        src_rect.y = screen_height - width - 1;
        dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = width;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 14: // Bottom scroll
        width = screen_height * effect_counter / effect_duration;
        src_rect.x = dst_rect.x = 0;
        src_rect.y = width;
        dst_rect.y = 0;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = screen_height - width;
        drawEffect(&dst_rect, &src_rect, effect_src_surface);

        src_rect.x = dst_rect.x = 0;
        src_rect.y = 0;
        dst_rect.y = screen_height - width - 1;
        src_rect.w = dst_rect.w = screen_width;
        src_rect.h = dst_rect.h = width;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 15: // Fade with mask
        alphaBlend( effect->anim.image_surface, ALPHA_BLEND_FADE_MASK, 256 * effect_counter / effect_duration, &dirty_rect.bounding_box );
        break;

      case 16: // Mosaic out
        generateMosaic( effect_src_surface, 5 - 6 * effect_counter / effect_duration );
        break;
        
      case 17: // Mosaic in
        generateMosaic( effect_dst_surface, 6 * effect_counter / effect_duration );
        break;
        
      case 18: // Cross fade with mask
        alphaBlend( effect->anim.image_surface, ALPHA_BLEND_CROSSFADE_MASK, 256 * effect_counter * 2 / effect_duration, &dirty_rect.bounding_box );
        break;

      case (MAX_EFFECT_NUM + 0): // quakey
        if ( effect_timer_resolution > effect_duration / 4 / effect->no )
            effect_timer_resolution = effect_duration / 4 / effect->no;
        amp = (Sint16)(sin(M_PI * 2.0 * effect->no * effect_counter / effect_duration) *
                              EFFECT_QUAKE_AMP * effect->no * (effect_duration -  effect_counter) / effect_duration);
        dst_rect.x = 0;
        dst_rect.y = amp;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);

        if (amp >= 0){
            quake_rect.y = 0;
            quake_rect.h = amp;
        }
        else{
            quake_rect.y = screen_height + amp;
            quake_rect.h = -amp;
        }
        SDL_FillRect( accumulation_surface, &quake_rect, SDL_MapRGBA( accumulation_surface->format, 0, 0, 0, 0xff ) );
        break;
        
      case (MAX_EFFECT_NUM + 1): // quakex
        if ( effect_timer_resolution > effect_duration / 4 / effect->no )
            effect_timer_resolution = effect_duration / 4 / effect->no;
        amp = (Sint16)(sin(M_PI * 2.0 * effect->no * effect_counter / effect_duration) *
                              EFFECT_QUAKE_AMP * effect->no * (effect_duration -  effect_counter) / effect_duration);
        dst_rect.x = amp;
        dst_rect.y = 0;
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);

        if (amp >= 0){
            quake_rect.x = 0;
            quake_rect.w = amp;
        }
        else{
            quake_rect.x = screen_width + amp;
            quake_rect.w = -amp;
        }
        SDL_FillRect( accumulation_surface, &quake_rect, SDL_MapRGBA( accumulation_surface->format, 0, 0, 0, 0xff ) );
        break;
        
      case (MAX_EFFECT_NUM + 2): // quake
        dst_rect.x = effect->no*((int)(3.0*rand()/(RAND_MAX+1.0)) - 1) * 2;
        dst_rect.y = effect->no*((int)(3.0*rand()/(RAND_MAX+1.0)) - 1) * 2;
        SDL_FillRect( accumulation_surface, NULL, SDL_MapRGBA( accumulation_surface->format, 0, 0, 0, 0xff ) );
        drawEffect(&dst_rect, &src_rect, effect_dst_surface);
        break;

      case 99: // dll-based
        if (effect->anim.image_name != NULL){
            if (!strncmp(effect->anim.image_name, "breakup.dll", 11)){
                effectBreakup(effect->anim.image_name, effect_duration);
            } else {
                // do crossfade
                height = 256 * effect_counter / effect_duration;
                alphaBlend( NULL, ALPHA_BLEND_CONST, height, &dirty_rect.bounding_box );
                not_implemented = true;
            }
        } else { //just in case no dll is given
            // do crossfade
            height = 256 * effect_counter / effect_duration;
            alphaBlend( NULL, ALPHA_BLEND_CONST, height, &dirty_rect.bounding_box );
            not_implemented = true;
        }
        break;
    }

    if (effect_counter == 0 && not_implemented)
        logw(stderr, "effect No. %d not implemented; substituting crossfade\n", effect_no);

    //printf("effect conut %d / dur %d\n", effect_counter, effect_duration);
    
    effect_counter += effect_timer_resolution;

    event_mode = WAIT_INPUT_MODE;
    waitEvent(0);
    if ( !((automode_flag || autoclick_time > 0) ||
           (usewheel_flag  && current_button_state.button == -5) ||
           (!usewheel_flag && current_button_state.button == -2)) ){
        effect_counter = effect_duration; // interrupted
    }

    if ( effect_counter < effect_duration && effect_no != 1 ){
        if ( effect_no != 0 ) flush( REFRESH_NONE_MODE, NULL, false );
    
        return true;
    }
    else{
        SDL_BlitSurface( effect_dst_surface, &dirty_rect.bounding_box, accumulation_surface, &dirty_rect.bounding_box );

        if ( effect_no != 0 ) flush(REFRESH_NONE_MODE, NULL, clear_dirty_region);
        if ( effect_no == 1 ) effect_counter = 0;
        skip_mode &= ~SKIP_TO_EOL;

        event_mode = IDLE_EVENT_MODE;
        if (effect_blank != 0 && effect_counter != 0)
            waitEvent(effect_blank);
        
        return false;
    }
}