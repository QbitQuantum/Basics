        void gInitStructuredExceptionHandler()
        {
            // TODO LPP: Should we use a thread local variable to ensure we only call
            // _set_se_translator() once per thread?  Does _set_se_translator() already do this?

            static bool shouldSetSeTranslator = RunParams::getInstance().isSet(RPARAM_DEBUGLOGSTACKTRACE);
            if (shouldSetSeTranslator)
            {
                LOG0(SourceInfo, DebugUtil::DebugDebug, "gInitStructuredExceptionHandler(): calling _set_se_translator()");
                _set_se_translator( translator_func );
            }
            else
            {
                LOG0(SourceInfo, DebugUtil::DebugDebug, "gInitStructuredExceptionHandler(): NOT calling _set_se_translator()");
            }
        }