int
pfi_sprintf ( char * tgt, char * fmt, uint32_t * _stack )
{
    uint64_t data64;
    uint32_t data32;
    char spec[256], type;
    int i, d, f, len;
    uint32_t * sp;
    
    sp = _stack;
    
    for( i = 0, d = 0; fmt[i]; i++ )
    {
        #if 0
          if( d > 0 )
          {
              g_print( "%c", tgt[d-1] );
              g_usleep( G_USEC_PER_SEC / 2 );
          }
        #endif 
        
        /* Format specifier? */
        if( fmt[i] == '%' )
        {
            /* Just a percent...? */
            if( fmt[i+1] == '%' )
            {
                /* Copy & continue */
                tgt[d++] = '%';
                i += 2;
                continue;
            }
            
            /* Yes, grab it */
            for( f = 0; 
                fmt[i+f] && !isspace(fmt[i+f]); 
                f++ )
            {
                spec[f] = fmt[i+f];
                
                if( is_valid_f_char(fmt[i+f]) )
                {
                    f++;
                    break;
                }
            }
            spec[f] = '\0';
            
            #if 0
              g_print( "%s\n", spec );
              getchar();
            #endif
            
            /* Check type... */
            type = spec[f-1];
            
            /* How much data we need from stack */
            switch( type )
            {
                /* Eight bytes */
                case 'e': case 'E':
                case 'f': case 'F':
                case 'g': case 'G':
                   
                  len = 8;
                  
                break;
                
                /* Four bytes */
                case 'd': case 'i':
                case 'o': case 'u':
                case 'x': case 'X':
                  
                  /* 64-bit? */
                  if( spec[f-2] == 'l' && spec[f-3] == 'l' )
                    len = 8;
                  else
                    len = 4;
                
                break;
                
                default:
                  len = 4;
            }
            
            /* Grab the data... */
            if( len == 8 )
            {
                data64 = (uint64_t)*sp | (uint64_t)*(sp+1) << 32;
                sp += 2;
            }
            else
            {
                data32 = *sp++;
            }
            
            /* String? */
            if( type == 's' )
            {
                char str[512];
                
                /* Ok, grab it from memory */
                mem_get_str( str, data32 & MMASK );
                
                /* Go */
                d += sprintf( &tgt[d], spec, str );
            }
            else
            {
                if( len == 8 )
                {
                    d += sprintf( &tgt[d], spec, data64 );
                }
                else
                {
                    d += sprintf( &tgt[d], spec, data32 );
                }
            }
            
            /* Finished... */
            i += f - 1;
            continue;
        }
        
        /* No format -- straight copy */
        tgt[d++] = fmt[i];
    }
    
    /* NULL terminate */
    tgt[d] = '\0';
    
    return d;
}