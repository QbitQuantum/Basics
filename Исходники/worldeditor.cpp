bool WorldEditor::Init()
{
    pslog::Initialize(objectReg);

    csRef<iVFS> vfs = csQueryRegistry<iVFS> (objectReg);
    if (!vfs)
    {
        printf("vfs failed to Init!\n");
        return false;
    }

    csRef<iConfigManager> configManager = csQueryRegistry<iConfigManager> (objectReg);
    if (!configManager)
    {
        printf("configManager failed to Init!\n");
        return false;
    }

    csRef<iEventQueue> queue = csQueryRegistry<iEventQueue> (objectReg);
    if (!queue)
    {
        printf("No iEventQueue plugin!\n");
        return false;
    }

    g3d = csQueryRegistry<iGraphics3D> (objectReg);
    if (!g3d)
    {
        printf("iGraphics3D failed to Init!\n");
        return false;
    }

    csRef<iGraphics2D> g2d = g3d->GetDriver2D();
    if (!g2d)
    {
        printf("GetDriver2D failed to Init!\n");
        return false;
    }

    engine = csQueryRegistry<iEngine> (objectReg);
    if (!engine)
    {
        printf("iEngine failed to Init!\n");
        return false;
    }

    kbd = csQueryRegistry<iKeyboardDriver> (objectReg);
    if (!kbd)
    {
        printf("iKeyboardDriver failed to Init!\n");
        return false;
    }

    vc = csQueryRegistry<iVirtualClock> (objectReg);
    if (!vc)
    {
        printf("iVirtualClock failed to Init!\n");
        return false;
    }

    csRef<iThreadManager> threadman = csQueryRegistry<iThreadManager> (objectReg);
    if (!threadman)
    {
        printf("iThreadManager failed to Init!\n");
        return false;
    }

    csRef<iBgLoader> loader = csQueryRegistry<iBgLoader>(objectReg);
    if(!loader.IsValid())
    {
        printf("Failed to load iBgLoader!\n");
        return false;
    }

    loader->SetLoadRange(1000);
    sceneManipulator = scfQueryInterface<iSceneManipulate>(loader);

    if(!csInitializer::OpenApplication(objectReg))
    {
        printf("Error initialising app (CRYSTAL not set?)\n");
        return false;
    }

    iNativeWindow *nw = g2d->GetNativeWindow();
    if (nw)
      nw->SetTitle(APPNAME);

    // Paws initialization
    vfs->Mount("/planeshift/", "$^");
    csString skinPath = configManager->GetStr("PlaneShift.GUI.Skin.Base","/planeshift/art/skins/base/client_base.zip");
    paws = new PawsManager(objectReg, skinPath);
    if (!paws)
    {
        printf("Failed to init PAWS!\n");
        return false;
    }

    mainWidget = new pawsMainWidget();
    paws->SetMainWidget(mainWidget);

    // Load and assign a default button click sound for pawsbutton
    //paws->LoadSound("/planeshift/art/sounds/gui/next.wav","sound.standardButtonClick");

    // Set mouse image.
    paws->GetMouse()->ChangeImage("Standard Mouse Pointer");

    // Register our event handler
    csRef<EventHandler> event_handler = csPtr<EventHandler> (new EventHandler (this));
    csEventID esub[] = 
    {
        csevFrame (objectReg),
        csevMouseEvent (objectReg),
        csevKeyboardEvent (objectReg),
        csevQuit (objectReg),
        CS_EVENTLIST_END
    };
    queue->RegisterListener(event_handler, esub);

    // Set up view.
    view.AttachNew(new csView(engine, g3d));
    view->SetRectangle(0, 0, g2d->GetWidth(), g2d->GetHeight());
    view->GetPerspectiveCamera()->SetPerspectiveCenter(0.5, 0.5);

    // Create blackbox world.
    iSector* blackbox = engine->CreateSector("BlackBox");
    blackbox->SetDynamicAmbientLight(csColor(1.0f, 1.0f, 1.0f));
    view->GetCamera()->SetSector(blackbox);
    view->GetCamera()->GetTransform().SetOrigin(csVector3(0.0f, 1.0f, 0.0f));

    // Create the base geometry.
    using namespace CS::Geometry;
    TesselatedBox box (csVector3 (-CS_BOUNDINGBOX_MAXVALUE, 0, -CS_BOUNDINGBOX_MAXVALUE),
                       csVector3 (CS_BOUNDINGBOX_MAXVALUE, CS_BOUNDINGBOX_MAXVALUE, CS_BOUNDINGBOX_MAXVALUE));
    box.SetFlags (Primitives::CS_PRIMBOX_INSIDE);

    // Now we make a factory and a mesh at once.
    csRef<iMeshWrapper> bbox = GeneralMeshBuilder::CreateFactoryAndMesh (
        engine, blackbox, "blackbox", "blackbox_factory", &box);

    // Create and set material.
    bbox->GetMeshObject ()->SetMaterialWrapper(engine->CreateMaterial("black", engine->CreateBlackTexture("black", 2, 2, 0, 0)));
    bbox->GetFlags().Set(CS_ENTITY_NOHITBEAM);

    // Check for world to load (will be done via gui in future).
    csRef<iCommandLineParser> cmdLine = csQueryRegistry<iCommandLineParser> (objectReg);
    const char* mapPath = cmdLine->GetOption("map");
    if(mapPath)
    {
        loader->PrecacheDataWait(mapPath);
        csRef<StartPosition> startPos = loader->GetStartPositions().Get(0);
        loader->UpdatePosition(startPos->position, startPos->sector, true);
        while(loader->GetLoadingCount() != 0)
        {
            threadman->Process(10);
            loader->ContinueLoading(true);
        }
        view->GetCamera()->SetSector(engine->GetSectors()->FindByName(startPos->sector));
        view->GetCamera()->GetTransform().SetOrigin(startPos->position);
    }

    // Prepare engine.
    engine->Prepare();
    engine->PrecacheDraw();

    return true;
}