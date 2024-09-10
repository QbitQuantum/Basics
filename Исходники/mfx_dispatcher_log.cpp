    virtual void Write(int level, int opcode, char * msg, va_list argptr)
    {
        //event not registered
        if (0==m_EventHandle)
        {
            return;
        }
        if (!m_bProviderEnable)
        {
            return;
        }
        if (level == DL_LOADED_LIBRARY)
        {
            return;
        }

        char msg_formated[1024];
        EVENT_DESCRIPTOR descriptor;
        EVENT_DATA_DESCRIPTOR data_descriptor;

        EventDescZero(&descriptor);
        
        descriptor.Opcode = (UCHAR)opcode; 
        descriptor.Level  = (UCHAR)level;
        
        if (m_bUseFormatter)
        {
            if (NULL != msg)
            {
#if _MSC_VER >= 1400
                vsprintf_s(msg_formated, sizeof (msg_formated) / sizeof (msg_formated[0]), msg, argptr);
#else
                vsnprintf(msg_formated, sizeof (msg_formated) / sizeof (msg_formated[0]), msg, argptr);
#endif
                EventDataDescCreate(&data_descriptor, msg_formated, (ULONG)(strlen(msg_formated) + 1));
            }else
            {
                EventDataDescCreate(&data_descriptor, NULL, 0);
            }
        }else
        {
            //TODO: non formated events supports under zbb 
        }

        EventWrite(m_EventHandle, &descriptor, 1, &data_descriptor);
    }