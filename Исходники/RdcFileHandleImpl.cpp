/*---------------------------------------------------------------------------
Name:     RdcGeneratorJob::AllocateGenerator

Allocate the resources necessary for signature generation.
This includes connecting to the RDC SDK, allocating buffers, and parameters

Arguments:
   fileSize            - used to compute RDC recursion depth.
   requestedDepth      - the preferred recursion depth, if 0, a default is calculated

----------------------------------------------------------------------------*/
DebugHresult RdcGeneratorJob::AllocateGenerator (
    ULONGLONG fileSize,
    ULONG requestedDepth )
{
    DebugHresult hr = S_OK;

    RDCAssert ( requestedDepth <= MSRDC_MAXIMUM_DEPTH );
    RDCAssert ( !m_Failed );

    m_Depth = 0;

    BYTE *buffer = m_InputBuffer.AppendItems ( g_InputBufferSize );
    if ( !buffer )
    {
        hr = E_OUTOFMEMORY;
    }

    if ( SUCCEEDED ( hr ) )
    {
        hr = m_RdcLibrary.CoCreateInstance ( __uuidof ( RdcLibrary ) );
    }

    if ( SUCCEEDED ( hr ) )
    {
        if ( requestedDepth == 0 )
        {
            hr = m_RdcLibrary->ComputeDefaultRecursionDepth ( fileSize, &m_Depth );
        }
        else
        {
            m_Depth = requestedDepth;
        }
    }

    if ( SUCCEEDED ( hr ) )
    {
        if ( m_Depth == 0 )
        {
            m_Depth = 1;
        }
        if ( m_Depth > MSRDC_MAXIMUM_DEPTH )
        {
            m_Depth = MSRDC_MAXIMUM_DEPTH;
        }
    }

    for ( ULONG i = 0; SUCCEEDED ( hr ) && i < m_Depth; ++i )
    {
        hr = m_RdcLibrary->CreateGeneratorParameters ( RDCGENTYPE_FilterMax, i + 1, &m_RdcGeneratorParameters[i] );
        m_GeneratorParameters[i] = m_RdcGeneratorParameters[i];
        if ( SUCCEEDED ( hr ) )
        {
            IRdcGeneratorFilterMaxParameters * q = 0;
            if ( i == 0 )
            {
                hr = m_RdcGeneratorParameters[0].QueryInterface ( &q );
                if ( SUCCEEDED ( hr ) )
                {
                    hr = q->SetHashWindowSize ( m_HashWindowSize1 );
                }
                if ( SUCCEEDED ( hr ) )
                {
                    hr = q->SetHorizonSize ( m_HorizonSize1 );
                }
            }
            else
            {
                hr = m_RdcGeneratorParameters[i].QueryInterface ( &q );
                if ( SUCCEEDED ( hr ) )
                {
                    hr = q->SetHashWindowSize ( m_HashWindowSizeN );
                }
                if ( SUCCEEDED ( hr ) )
                {
                    hr = q->SetHorizonSize ( m_HorizonSizeN );
                }
            }
            if ( q )
            {
                q->Release();
            }
        }
    }

    if ( SUCCEEDED ( hr ) )
    {
        hr = m_RdcLibrary->CreateGenerator ( m_Depth, &m_GeneratorParameters[0], &m_RdcGenerator );
    }

    if ( SUCCEEDED ( hr ) )
    {
        hr = m_RdcGenerator.QueryInterface ( &m_RdcSimilarityGenerator );
    }
    if ( SUCCEEDED ( hr ) )
    {
        m_SimilarityEnabled = true;
        hr = m_RdcSimilarityGenerator->EnableSimilarity();
    }
    for ( ULONG i = 0; SUCCEEDED ( hr ) && i < m_Depth; ++i )
    {
        if ( !m_OutputBuffer[i].AppendItems ( g_OutputBufferSize ) )
        {
            hr = E_OUTOFMEMORY;
        }
    }
    if ( FAILED ( hr ) )
    {
        m_Failed = true;
    }

    return hr;
}