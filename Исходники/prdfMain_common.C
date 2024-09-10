errlHndl_t noLock_initialize()
{
    #define PRDF_FUNC "PRDF::noLock_initialize() "

    PRDF_ENTER( PRDF_FUNC );

    g_prd_errlHndl = NULL; // This forces any previous errls to be committed

    // Synchronize SCOM access to hardware
    // Start un-synchronized so hardware is accessed
    RegDataCache::getCachedRegisters().flush();

    if(g_initialized == true && systemPtr != NULL)
    {
        // This means we are being re-initialized (and we were in a good state)
        // so Clean up in preparation for re-build
        unInitialize();
    }

    if(g_initialized == false)
    {
        // Initialize the Service Generator
        ServiceGeneratorClass & serviceGenerator =
                    ServiceGeneratorClass::ThisServiceGenerator();
        serviceGenerator.Initialize();

        // Perform platform specific initialization.
        initPlatSpecific();

        CcAutoDeletePointer<Configurator> configuratorPtr
            (SystemSpecific::getConfiguratorPtr());

        errlHndl_t l_errBuild = configuratorPtr->build();//build object model
        if( NULL != l_errBuild )
        {
            //there is some problem in building RuleMetaData object
            g_prd_errlHndl = l_errBuild;

            //object model is either not build or at best incomplete.We must
            // clean this up .The easiest way is to delete the system which in
            //in turn shall clean up the constituents.
            delete systemPtr;
            systemPtr = NULL;
            g_initialized = false;
            PRDF_ERR(PRDF_FUNC"failed to buid object model");
        }
        //systemPtr is populated in configurator
        else if( systemPtr != NULL )
        {
            systemPtr->Initialize(); // Hardware initialization
            g_initialized = true;
        }

        // Flush rule table cache since objects are all built.
        Prdr::LoadChipCache::flushCache();
    }

    PRDF_EXIT( PRDF_FUNC );

    return (g_prd_errlHndl.release());

    #undef PRDF_FUNC
}