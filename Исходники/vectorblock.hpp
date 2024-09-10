    /**
     * copy subblock from global vector
     */
    void localize( vector_ptrtype const& vb )
    {
        vb->close();

        size_type _start_i=0;
        for ( uint16_type i=0; i<this->nRow(); ++i )
        {
            size_type nBlockRow = this->operator()( i,0 )->localSize();

            for ( size_type k=0; k<nBlockRow; ++k )
            {
                this->operator()( i,0 )->set( k, vb->operator()( _start_i+k ) );
            }

            this->operator()( i,0 )->close();
            _start_i += nBlockRow;
        }
    }