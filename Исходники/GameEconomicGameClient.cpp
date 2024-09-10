/// Main program execution code
void GameEconomicGameClient::Start()
{
    /// Initialize
    Init(context_);

    /// Execute base class startup
    GameEconomicApp::Start();

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    FileSystem * filesystem = GetSubsystem<FileSystem>();
    GameStateHandlerComponent * gamestatehandlercomponent_ = GetSubsystem<GameStateHandlerComponent>();

    /// Set aApplication
    gamestatehandlercomponent_->SetApplication(applicationPtr);

    /// Get ui
    UI* ui = GetSubsystem<UI>();

    /// create variables (urho3d)
    String additionresourcePath;

    /// Append Resource path
    additionresourcePath.Append(filesystem->GetProgramDir().CString());
    additionresourcePath.Append("Resources/");

    /// add resource path to last
    cache -> AddResourceDir(additionresourcePath);

    /// Load COnfiguration
    GameConfig = new Configuration();

    LoadConfiguration(*GameConfig);

    /// Turn on networking
    if(LoadNetworkConfig(NetConfig)==false)
    {
        /// Set up network configuration
        NetConfig.hostport = 3632;
        NetConfig.hostserver = String("127.0.0.1");
        NetConfig.hostidentity = Unauthenticated;
    }

    /// Set up default network status
    NetOnline = NetDisconnected;
    NetStats = NetworkOffline;

    /// Set the loaded style as default style
    uiRoot_->SetDefaultStyle(style);

    CreateCursor();

    ui->GetCursor()->SetVisible(true);

    /// Initialize Console
    InitializeConsole();

    GetSubsystem<Input>()->Update();

    /// Enable OS cursor
    /// Configure rudimentary state handler
    gamestatehandlercomponent_ ->SetUIState(UI_NONE);

    GetSubsystem<Input>()->SetMouseVisible(true);

    /// load account
    ///LoadAccount();

    /// Create test value
    testvalue=121;

    /// Debug output context and testvalue
    cout << "Debug: ExistenceClient Class Test Value " << testvalue << " context_ " << &context_ << endl;

    /// Finally subscribe to the update event. Note that by subscribing events at this point we have already missed some events
    /// like the ScreenMode event sent by the Graphics subsystem when opening the application window. To catch those as well we
    /// could subscribe in the constructor instead.
    SubscribeToEvents();

    /// Randomize timer
    srand (time(NULL));

    cout << "Debig: Existence App Existence " << applicationPtr ->GetTestString()<< endl;

    /// Create test value

    cout << "Debig: Existence App Existence " << applicationPtr ->GetTestString()<< endl;

    touchenabled_=false;

    /// Network related
    SubscribeToEvent(E_NETWORKMESSAGE, HANDLER(GameEconomicGameClient, HandleNetworkMessage));
    SubscribeToEvent(E_SERVERCONNECTED, HANDLER(GameEconomicGameClient, HandlerServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, HANDLER(GameEconomicGameClient, HandlerServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, HANDLER(GameEconomicGameClient, HandlerServerConnectionFailed));

    ResourcesManager = new ResourceManager(context_);
    ActivitiesManager = new ActivityManager(context_);

    gamestatehandlercomponent_->Start();

    return;
}