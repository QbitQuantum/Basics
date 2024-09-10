CodecError CCodec_BC6H::CInitializeBC6HLibrary()
{
    if (!m_LibraryInitialized)
    {
        // This is shared between BC7 also
        // and checked for initialization based on static flag
        // See the function for details.
        Quant_Init();

        // One time initialisation for quantizer and shaker
        // check this is ok to remove for when we are encoding 
        // should have no effect on decoding
        BC6H_init_ramps();


        for(DWORD i=0; i < BC6H_MAX_THREADS; i++)
        {
            m_encoder[i] = NULL;
        }

        // Create threaded encoder instances
        m_LiveThreads = 0;
        m_LastThread  = 0;
        m_NumEncodingThreads = min(m_NumThreads, BC6H_MAX_THREADS);
        if (m_NumEncodingThreads == 0) m_NumEncodingThreads = 1; 
        m_Use_MultiThreading = m_NumEncodingThreads > 1;

        g_BC6EncodeParameterStorage = new BC6HEncodeThreadParam[m_NumEncodingThreads];
        if(!g_BC6EncodeParameterStorage)
        {
            return CE_Unknown;
        }

        for (int i=0; i<m_NumEncodingThreads; i++)
            g_BC6EncodeParameterStorage[i].run = false;

        m_EncodingThreadHandle = new HANDLE[m_NumEncodingThreads];
        if(!m_EncodingThreadHandle)
        {
            delete[] g_BC6EncodeParameterStorage;
            g_BC6EncodeParameterStorage = NULL;

            return CE_Unknown;
        }

        for(int i=0; i < m_NumEncodingThreads; i++)
        {
            // Create single encoder instance
            CMP_BC6H_BLOCK_PARAMETERS user_options;

            user_options.bIsSigned      = m_bIsSigned;
            user_options.fQuality       = m_Quality;
            user_options.dwMask         = m_ModeMask;
            user_options.fExposure      = m_Exposure;
            user_options.bUsePatternRec = m_UsePatternRec;

            m_encoder[i] = new BC6HBlockEncoder(user_options);
                        
            // Cleanup if problem!
            if(!m_encoder[i])
            {

                delete[] g_BC6EncodeParameterStorage;
                g_BC6EncodeParameterStorage = NULL;

                delete[] m_EncodingThreadHandle;
                m_EncodingThreadHandle = NULL;

                for(int j=0; j<i; j++)
                {
                    delete m_encoder[j];
                    m_encoder[j] = NULL;
                }

                return CE_Unknown;
            }
            
            #ifdef USE_DBGTRACE
                DbgTrace(("Encoder[%d]:ModeMask %X, Quality %f\n",i,m_ModeMask,m_Quality));
            #endif
        }

        // Create the encoding threads in the suspended state
        for(int i=0; i<m_NumEncodingThreads; i++)
        {
            m_EncodingThreadHandle[i] = (HANDLE)_beginthreadex(NULL,
                                               0,
                                               BC6HThreadProcEncode,
                                               (void*)&g_BC6EncodeParameterStorage[i],
                                               CREATE_SUSPENDED,
                                               NULL);
            if(m_EncodingThreadHandle[i])
            {
                g_BC6EncodeParameterStorage[i].encoder = m_encoder[i];
                // Inform the thread that at the moment it doesn't have any work to do
                // but that it should wait for some and not exit
                g_BC6EncodeParameterStorage[i].run = FALSE;
                g_BC6EncodeParameterStorage[i].exit = FALSE;
                // Start the thread and have it wait for work
                ResumeThread(m_EncodingThreadHandle[i]);
                m_LiveThreads++;
            }
         }


        // Create single decoder instance
        m_decoder = new BC6HBlockDecoder();
        if(!m_decoder)
        {
            for(DWORD j=0; j<m_NumEncodingThreads; j++)
            {
                delete m_encoder[j];
                m_encoder[j] = NULL;
            }
            return CE_Unknown;
        }

        m_LibraryInitialized = true;
    }
    return CE_OK;
}