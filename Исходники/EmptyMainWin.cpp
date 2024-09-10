int main( int argc, const char* argv[] )
#endif
{
    HELIUM_TRACE_SET_LEVEL( TraceLevels::Debug );

    Helium::GetComponentsDefaultHeap();
    Helium::GetBulletDefaultHeap();

#if HELIUM_TOOLS
    Helium::GetEditorSupportDefaultHeap();
#endif

    int32_t result = 0;

    {
        // Initialize a GameSystem instance.
        CommandLineInitializationImpl commandLineInitialization;
        MemoryHeapPreInitializationImpl memoryHeapPreInitialization;
        AssetLoaderInitializationImpl assetLoaderInitialization;
        ConfigInitializationImpl configInitialization;
#if HELIUM_DIRECT3D
        WindowManagerInitializationImpl windowManagerInitialization( hInstance, nCmdShow );
#else
        WindowManagerInitializationImpl windowManagerInitialization;
#endif
        RendererInitializationImpl rendererInitialization;
        AssetPath systemDefinitionPath( "/ExampleGames/Empty:System" );
        //NullRendererInitialization rendererInitialization;

        GameSystem* pGameSystem = GameSystem::CreateStaticInstance();
        HELIUM_ASSERT( pGameSystem );
        bool bSystemInitSuccess = pGameSystem->Initialize(
                                      commandLineInitialization,
                                      memoryHeapPreInitialization,
                                      assetLoaderInitialization,
                                      configInitialization,
                                      windowManagerInitialization,
                                      rendererInitialization,
                                      systemDefinitionPath);

        {
            Helium::AssetLoader *pAssetLoader = AssetLoader::GetStaticInstance();
            Helium::SceneDefinitionPtr spSceneDefinition;

            AssetPath scenePath( TXT( "/ExampleGames/Empty/Scenes/TestScene:SceneDefinition" ) );
            pAssetLoader->LoadObject(scenePath, spSceneDefinition );

            pGameSystem->LoadScene(spSceneDefinition.Get());
        }

        if( bSystemInitSuccess )
        {
            Window::NativeHandle windowHandle = rendererInitialization.GetMainWindow()->GetNativeHandle();
            Input::Initialize(windowHandle, false);

            // Run the application.
            result = pGameSystem->Run();
        }

        // Shut down and destroy the system.
        pGameSystem->Shutdown();
        System::DestroyStaticInstance();
    }

    // Perform final cleanup.
    ThreadLocalStackAllocator::ReleaseMemoryHeap();

#if HELIUM_ENABLE_MEMORY_TRACKING
    DynamicMemoryHeap::LogMemoryStats();
    ThreadLocalStackAllocator::ReleaseMemoryHeap();
#endif

    return result;
}