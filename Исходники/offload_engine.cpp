    ~Thread() {
#ifndef TARGET_WINNT
        __sync_sub_and_fetch(m_addr_coipipe_counter, 1);
#else // TARGET_WINNT
        _InterlockedDecrement(m_addr_coipipe_counter);
#endif // TARGET_WINNT
        for (int i = 0; i < mic_engines_total; i++) {
            if (m_pipelines[i] != 0) {
                COI::PipelineDestroy(m_pipelines[i]);
            }
        }
    }