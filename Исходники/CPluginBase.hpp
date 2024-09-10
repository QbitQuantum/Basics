            virtual const char* ListNodes() const
            {
                static char sNodes[8192];
                char* sBeginPtr = sNodes;

                // List all flownodes of this plugin
                for ( CG2AutoRegFlowNodeBase* pFactory = CG2AutoRegFlowNodeBase::m_pFirst; pFactory; pFactory = pFactory->m_pNext )
                {
                    if ( pFactory->m_sClassName )
                    {
                        sBeginPtr += _snprintf_c( sBeginPtr, sizeof( sNodes ) - ( sBeginPtr - sNodes ), "%s,\n", pFactory->m_sClassName );
                    }
                }

                return sNodes;
            };