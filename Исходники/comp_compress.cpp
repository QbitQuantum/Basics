void CompCompressor::Compress(PicArray& pic_data)
{

    //need to transform, select quantisers for each band, and then compress each component in turn
    m_csort=pic_data.CSort();
    const int depth=4;
    unsigned int num_band_bits;

    // A pointer to an object  for coding the subband data
    BandCodec* bcoder;

    // A pointer to an object for outputting the subband data
    UnitOutputManager* band_op;

    const size_t CONTEXTS_REQUIRED = 24;

    Subband node;

    //set up Lagrangian params    
    if (m_fsort == I_frame) 
        m_lambda= m_encparams.ILambda();
    else if (m_fsort == L1_frame) 
        m_lambda= m_encparams.L1Lambda();
    else 
        m_lambda= m_encparams.L2Lambda();

     if (m_csort == U_COMP) 
         m_lambda*= m_encparams.UFactor();
     if (m_csort == V_COMP) 
         m_lambda*= m_encparams.VFactor();

    WaveletTransform wtransform(depth);

    wtransform.Transform( FORWARD , pic_data );
    wtransform.SetBandWeights( m_encparams.CPD() , m_fparams.FSort() , m_fparams.CFormat(), m_csort);

    SubbandList& bands=wtransform.BandList();

    // Generate all the quantisation data
    GenQuantList();

    // Choose all the quantisers
    OneDArray<unsigned int> estimated_bits( Range( 1 , bands.Length() ) );
    SelectQuantisers( pic_data , bands , estimated_bits );  

    // Loop over all the bands (from DC to HF) quantising and coding them
    for (int b=bands.Length() ; b>=1 ; --b )
    {
        band_op = & m_encparams.BitsOut().FrameOutput().BandOutput( m_csort , b );

        GolombCode( band_op->Header() , bands(b).Qf(0) );

        if (bands(b).Qf(0) != -1)
        {   // If not skipped ...

            bands(b).SetQf( 0 , m_qflist[bands(b).Qf(0)] );

             // Pick the right codec according to the frame type and subband
            if (b >= bands.Length())
            {
                if ( m_fsort == I_frame && b == bands.Length() )
                    bcoder=new IntraDCBandCodec( &( band_op->Data() ) , CONTEXTS_REQUIRED , bands);
                else
                    bcoder=new LFBandCodec( &( band_op->Data() ) ,CONTEXTS_REQUIRED, bands , b);
            }
            else
                bcoder=new BandCodec( &( band_op->Data() ) , CONTEXTS_REQUIRED , bands , b);

            num_band_bits = bcoder->Compress(pic_data);

             // Update the entropy correction factors
            m_encparams.EntropyFactors().Update(b , m_fsort , m_csort , estimated_bits[b] , num_band_bits);

            // Write the length of the data chunk into the header, and flush everything out to file
            UnsignedGolombCode( band_op->Header() , num_band_bits);

            delete bcoder;            
        }
        else
        {   // ... skipped

            if (b == bands.Length() && m_fsort == I_frame)
                SetToVal( pic_data , bands(b) , 2692 );
            else
                SetToVal( pic_data , bands(b) , 0 );
        }        
    }//b

    // Transform back into the picture domain
    wtransform.Transform( BACKWARD , pic_data );

}