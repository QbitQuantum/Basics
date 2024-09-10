//-------------------------------------------------------------------------------------
void ServerApp::handleTimeout(TimerHandle, void * arg)
{
    switch (reinterpret_cast<uintptr>(arg))
    {
    case TIMEOUT_ACTIVE_TICK:
    {
        int8 findComponentTypes[] = {BASEAPPMGR_TYPE, CELLAPPMGR_TYPE, DBMGR_TYPE, CELLAPP_TYPE,
                                     BASEAPP_TYPE, LOGINAPP_TYPE, MESSAGELOG_TYPE, RESOURCEMGR_TYPE, UNKNOWN_COMPONENT_TYPE
                                    };

        int ifind = 0;
        while(findComponentTypes[ifind] != UNKNOWN_COMPONENT_TYPE)
        {
            COMPONENT_TYPE componentType = (COMPONENT_TYPE)findComponentTypes[ifind];

            Components::COMPONENTS& components = Components::getSingleton().getComponents(componentType);
            Components::COMPONENTS::iterator iter = components.begin();
            for(; iter != components.end(); iter++)
            {
                Mercury::Bundle bundle;
                COMMON_MERCURY_MESSAGE(componentType, bundle, onAppActiveTick);

                bundle << g_componentType;
                bundle << componentID_;
                if((*iter).pChannel != NULL)
                    bundle.send(getNetworkInterface(), (*iter).pChannel);
            }

            ifind++;
        }
        break;
    }
    default:
        break;
    }
}