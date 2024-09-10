int iniparse_args(configctx_t *ctx, int argc, char *argv[])
{
    int  i;
    int  ret;
    char *arg;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i] && argv[i][0] == '-' ) {
            if ( argv[i][1] == '-' ) {
                char  *temp_section = ctx->current_group;
                char  *ptr, *option,*value = NULL;
                int    optc = i;

                arg = STRDUP(argv[i]);
                /* Long option handling - break out the section if present */
                if ( ( ptr = strchr(arg,':') ) != NULL ) {
                    *ptr = 0;  /* Truncate section */
                    ctx->current_group = &arg[2];
                    option = ptr + 1;
                } else {
                    option = &arg[2];
                    temp_section = NULL;
                }


                /* Now we have to find where the option is - it could either
                   be after an '=', or the next argument */
                if ( ( ptr = strchr(option,'=') ) != NULL ) {
                    *ptr = 0;
                    value = ptr + 1;
                } else if ( i + 1 < argc ) {
                    value = argv[i+1];
                    optc = i + 1;
                }

                if ( option ) {
                    if ( (ret = option_set(ctx, option,value) ) > 0 ) {
//                        argv[i] = NULL;
                        if ( ret > 0 ) {
//                            argv[optc] = NULL;
                            i = optc;
                        } else {
                            i++;
                        }
                    }
                }
                /* Restore the default section */
                if ( temp_section ) {
                    ctx->current_group = temp_section;
                }

                FREENULL(arg);
                if ( option == NULL ) {                    
                    return -1;
                }
            } else {   /* Short option handling */
                char sopt = argv[i][1];
                char *nextarg = NULL;

                if ( i + 1 < argc ) {
                    nextarg = argv[i+1];
                }

                if ( ( ret = option_set_sopt(ctx,sopt,nextarg) ) > 0 ) {
                    argv[i] = NULL;
                    argv[i + ret] = NULL;
                    i += ret;
                }
            }
        }
    }
    return 0;
}