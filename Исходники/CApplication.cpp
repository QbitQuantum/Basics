    //-------------------------------------------------------------------------
    //                                   i n i t
    //-------------------------------------------------------------------------
    int CApplication::init()
    {
        SIrrlichtCreationParameters cp;
        static SKeyMap keyMap[5];
        keyMap[0].Action = EKA_MOVE_FORWARD;
        keyMap[0].KeyCode = KEY_KEY_W;
        keyMap[1].Action = EKA_STRAFE_LEFT;
        keyMap[1].KeyCode = KEY_KEY_A;
        keyMap[2].Action = EKA_MOVE_BACKWARD;
        keyMap[2].KeyCode = KEY_KEY_S;
        keyMap[3].Action = EKA_STRAFE_RIGHT;
        keyMap[3].KeyCode = KEY_KEY_D;
        keyMap[4].Action = EKA_JUMP_UP;
        keyMap[4].KeyCode = KEY_SPACE;

        int result=0;
        stringc msg;


        // use null device for early file system access
        IrrlichtDevice* m_nullDevice = createDevice(EDT_NULL);
        IFileSystem* fileSystem = m_nullDevice->getFileSystem();

        m_currentDirectory = fileSystem->getWorkingDirectory();
        m_currentDirectory = fileSystem->flattenFilename(m_currentDirectory);
        if(m_argv)
        {
            m_appExecutable = m_argv[0];
        }
        else
        {
            m_appExecutable = "irrlicht.exe";
        }


        stringc appBaseName;
        appBaseName = fileSystem->getAbsolutePath(m_appExecutable);
        appBaseName = fileSystem->getFileBasename(appBaseName, false);

        //
        // create log writer
        //
        m_logName = appBaseName;
        m_logName += ".log";

        m_logFile = fileSystem->createAndWriteFile(m_logName);

        msg = "Created log file: ";
        msg += m_logName;
        logMessage(msg);

        //
        // configuration system
        //
        // locate the data directory - underneath our executable or outside of it.
        stringc temp("data/");
        if(!fileSystem->existFile(temp))
        {
            temp = "../data/";
            // todo - look for "data.zip"...
        }
        m_dataRoot = fileSystem->getAbsolutePath(temp);
        m_configName = m_dataRoot;
        m_configName += "/cfg/";
        m_configName += appBaseName;
        m_configName += ".xml";


        if(!fileSystem->existFile(m_configName))
        {
            // not in data/cfg or ../data/cfg so look in the working directory.
            m_configName = appBaseName;
            m_configName += ".xml";
            if(!fileSystem->existFile(m_configName))
            {
                return -1;
            }
        }

        // load the config file
        m_config = new CXMLConfig();
        if(!m_config->load(m_configName))
        {
            return -1;
        }

        // setup the device based on config settings
        stringc sdriver = m_config->getString("driver","video","EDT_OPENGL");
        cp.DriverType = EDT_OPENGL;
        if(sdriver == "EDT_DIRECT3D9")
            cp.DriverType = EDT_DIRECT3D9;        
        cp.WindowSize = m_config->getDimension("resolution","video",dimension2di(800, 600));
        cp.Bits = m_config->getInt("colordepth","video",32);
        cp.Fullscreen = m_config->getBool("fullscreen","video",false);
        cp.Vsync = m_config->getBool("vsync","video",true);
        cp.Stencilbuffer = m_config->getBool("stencilbuffer","video",false);
        cp.AntiAlias = m_config->getInt("antialias","video",0);
        cp.EventReceiver = this;
        cp.WindowId = 0;

        m_device =  createDeviceEx(cp);
        if(!m_device)
            return -1;

        m_fileSystem = m_device->getFileSystem();
        m_videoDriver = m_device->getVideoDriver();
        m_sceneManager = m_device->getSceneManager();
        m_gui = m_device->getGUIEnvironment();

        m_device->getCursorControl()->setVisible(m_config->getBool("HWCursorVisible","video",true));
        m_device->setWindowCaption(stringw(m_title).c_str());


        //
        // add configured file systems
        //
        if(_initFileSystems())
            return -1;

        //
        // set up the default font
        //        
        stringc fontFolder = "fnt/";
        stringc defFonts = fontFolder + "defaults.zip";
        if(m_fileSystem->existFile(defFonts.c_str()))
        {
            m_fileSystem->addZipFileArchive(defFonts.c_str());
            m_defaultFont = m_gui->getFont("tdeffont.xml");
            if(m_defaultFont)
            {
                m_defaultFont->grab();
                m_gui->getSkin()->setFont(m_defaultFont);
            }
            m_monoFont = m_gui->getFont("monospace.xml");
            if(m_monoFont)
            {
                m_monoFont->grab();
            }
        }

        m_world = m_sceneManager->createMetaTriangleSelector();

        // camera setup
        f32 rotateSpeed = m_config->getFloat("rotateSpeed","options",100.f);
        m_orgMoveSpeed = m_config->getFloat("moveSpeed","options",0.001f);
        f32 jumpSpeed = m_config->getFloat("jumpSpeed","options",0.05f);
        m_camera = m_sceneManager->addCameraSceneNodeFPS(0, rotateSpeed, m_orgMoveSpeed, -1,keyMap,5,true, jumpSpeed);

        vector3df v = m_config->getVector3("campos","options");
        m_camera->setPosition(v);

        v = m_config->getVector3("camtarget","options");
        m_camera->setTarget(v);

        bool collisionEnabled = m_config->getBool("collision","options");
        if(collisionEnabled)
        {
            vector3df gravity,ellipsoid;
            gravity = m_config->getVector3("gravity","options",vector3df(0,-0.1f,0));
            ellipsoid = m_config->getVector3("ellipsoid","options",vector3df(2,5,2));
            m_collisionResponse = m_sceneManager->createCollisionResponseAnimator(m_world,m_camera,
                ellipsoid, gravity);
            m_camera->addAnimator(m_collisionResponse);
        }
        
        // debug & help panels setup
        m_debugPanel = new gui::CGUITextPanel(m_gui, "debugPanel", rectf(0.25f,0.005f,0.75f,0.05f));
        m_debugPanel->addItem("Node: Pos(x,y,z) Hpr(x,y,z) Dir(x,y,z)", EGUIA_CENTER);
        m_debugPanel->addItem("Frame: Avg(0.0) Min(0.0) Max(0.0)", EGUIA_CENTER);
        m_debugPanel->setVisible(true);

        m_helpPanel = new gui::CGUITextPanel(m_gui, "helpPanel", rectf(0.005f,0.005f,0.245f,0.05f));
        m_helpPanel->addItem(" wasd - Movement");
        m_helpPanel->addItem("   F1 - Toggle Help");
        m_helpPanel->addItem("   F2 - Toggle Debug");

        createScene();

        return result;
    }