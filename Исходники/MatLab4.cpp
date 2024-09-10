MatLab4::MatLab4(char * file_name , char * param_name , char * time_name ) {

        int len ;
        int temp ;
        int endian ;
        int mat_size ;
        int type , size ;
        int mat_type ;
        int my_byte_order ;
        div_t div_result ;
        int row , column , imaginary ;
        char * temp_ptr ;
        bool param_found , time_found ;
        int max_offset , offset = 0 ;

        fileName_ = file_name ;
        TRICK_GET_BYTE_ORDER(my_byte_order) ;

        if ((fp_ = fopen(file_name , "r")) == 0 ) {
           std::cerr << "ERROR:  Couldn't open \"" << file_name << "\": " << std::strerror(errno) << std::endl;
           exit(-1) ;
        }

        // we use fseek calls to move around so I need to know the max offset of the file
        fseek( fp_ , 0 , SEEK_END ) ;
        max_offset = ftell(fp_) ;
        rewind( fp_ ) ;

        // get field_num from param_name
        temp_ptr = rindex(param_name, '[') ;
        if ( temp_ptr != NULL ) {
                sscanf(&temp_ptr[1] , "%d" , &y_value_.field_num_ ) ;
        }
        else {
                y_value_.field_num_ = 0 ;
        }

        // get field_num from time_name
        temp_ptr = rindex(param_name, '[') ;
        if ( temp_ptr != NULL ) {
                sscanf(&temp_ptr[1] , "%d" , &time_value_.field_num_ ) ;
        }
        else {
                time_value_.field_num_ = 0 ;
        }

        param_found = time_found = false ;
        while ( (!param_found || !time_found) && (offset < max_offset)) {

                // read the type in
                fread( &temp , 4 , 1 , fp_ ) ;
                if ( ! strncmp( (char *)&temp , "MATL" , 4 )) {
                        fclose(fp_) ;
                        return ;
                }
                // byte swap it if it looks like we need to
                if ( temp & 0xFFFF0000 ) {
                        temp = trick_byteswap_int(temp) ;
                }

                div_result = div(temp , 1000) ;
                endian = div_result.quot ;
                temp = div_result.rem ;

                switch ( endian ) {
                        case 0:
                                swap_ = ( my_byte_order == TRICK_LITTLE_ENDIAN ) ? 0 : 1 ;
                                break ;
                        case 1:
                                swap_ = ( my_byte_order == TRICK_BIG_ENDIAN ) ? 0 : 1 ;
                                break ;
                        default:
                                fprintf(stderr,"Unknown endianness!\n") ;
                                fclose(fp_) ;
                                return ;
                                break ;
                }

                div_result = div( temp , 10 ) ;
                mat_size = div_result.quot ;
                mat_type = div_result.rem ;
                switch ( mat_size ) {
                        case 0:
                                type = TRICK_DOUBLE ;
                                size = 8 ;
                                break ;
                        case 1:
                                type = TRICK_FLOAT ;
                                size = 4 ;
                                break ;
                        case 2:
                                type = TRICK_INTEGER ;
                                size = 4 ;
                                break ;
                        case 3:
                                type = TRICK_SHORT ;
                                size = 2 ;
                                break ;
                        case 4:
                                type = TRICK_UNSIGNED_SHORT ;
                                size = 2 ;
                                break ;
                        case 5:
                                type = TRICK_CHARACTER ;
                                size = 1 ;
                                break ;
                }

                if ( mat_type != 0 ) {
                        fprintf(stderr,"Unknown matrix type!\n") ;
                        fclose(fp_) ;
                        return ;
                }

                fread( &row , 4 , 1 , fp_ ) ;
                if ( swap_ ) { row = trick_byteswap_int(row) ; }

                fread( &column , 4 , 1 , fp_ ) ;
                if ( swap_ ) { column = trick_byteswap_int(column) ; }

                fread( &imaginary , 4 , 1 , fp_ ) ;
                if ( swap_ ) { imaginary = trick_byteswap_int(imaginary) ; }

                fread( &len , 4 , 1 , fp_ ) ;
                if ( swap_ ) { len = trick_byteswap_int(len) ; }

                temp_ptr = new char[len +1] ;
                fread( temp_ptr , len , 1 , fp_ ) ;

                if ( ! strncmp( temp_ptr , param_name , len ) && y_value_.field_num_ < column ) {
                        y_value_.size_ = size ;
                        y_value_.type_ = type ;
                        y_value_.rows_ = row ;
                        y_value_.columns_ = column ;
                        y_value_.imaginary_ = imaginary ;
                        y_value_.data_offset_ = ftell(fp_) ;
                        param_found = true ;
                }
                if ( ! strncmp( temp_ptr , time_name , len ) && time_value_.field_num_ < column ) {
                        time_value_.size_ = size ;
                        time_value_.type_ = type ;
                        time_value_.rows_ = row ;
                        time_value_.columns_ = column ;
                        time_value_.imaginary_ = imaginary ;
                        time_value_.data_offset_ = ftell(fp_) ;
                        time_found = true ;
                }

                delete temp_ptr ;

                // skip to next parameter
                fseek( fp_ ,  row * column * size * ( 1 + imaginary ) , SEEK_CUR ) ;
                offset = ftell(fp_) ;
        }

        curr_row_ = 0 ;
}