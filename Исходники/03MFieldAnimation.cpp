// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        //Initialize Window
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TutorialWindow.get()));

        //Torus Node
        NodeUnrecPtr TorusGeometryNode = makeTorus(.5, 2, 32, 32);

        //Make Torus Node
        NodeUnrecPtr TorusNode = Node::create();
        TransformUnrecPtr TorusNodeTrans;
        TorusNodeTrans = Transform::create();

        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);

        //Make Main Scene Node
        NodeUnrecPtr scene = Node::create();
        ComponentTransformUnrecPtr Trans;
        Trans = ComponentTransform::create();
        scene->setCore(Trans);

        // add the torus as a child
        scene->addChild(TorusNode);

        //Make a gradient Background
        GradientBackgroundUnrecPtr TutorialBackground = GradientBackground::create();
        TutorialBackground->addLine(Color3f(1.0,0.0,0.0),0.0);
        TutorialBackground->addLine(Color3f(0.0,1.0,0.0),0.5);
        TutorialBackground->addLine(Color3f(0.0,0.0,1.0),1.0);
        setName(TutorialBackground, std::string("TutorialGradientBackground"));

        AnimationUnrecPtr TheAnimation = setupAnimation(TutorialBackground);
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        // tell the manager what to manage
        sceneManager.setRoot  (scene);
        sceneManager.getWindow()->getPort(0)->setBackground(TutorialBackground);

        //Create the Documentation
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // show the whole scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "03MFieldAnimation");

        //Main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}