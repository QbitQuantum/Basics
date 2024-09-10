        /**
          *   Generate 2 blocks of open info and create secret key.
         **/
        void generate_key_infos( const std::string &key,
                                 std::string &s1, std::string &s2,
                                 std::string &result )
        {
            random_device rd( false );

            std::string ts1( rd.generate_block( 256 ) );
            std::string ts2( rd.generate_block( 256 ) );

            create_key( key, ts1, ts2, result );

            s1.swap( ts1 );
            s2.swap( ts2 );
        }