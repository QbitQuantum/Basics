// Initialize GLUT & OpenSG and set up the rootNode
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Make Base Geometry Node
        NodeRecPtr TriGeometryBase = makeTorus(0.5, 1.0, 24, 24);

        //Make Main Scene Node
        NodeRecPtr scene = makeCoredNode<Group>();
        setName(scene, "scene");
        NodeRecPtr rootNode = Node::create();
        setName(rootNode, "rootNode");
        ComponentTransformRecPtr Trans;
        Trans = ComponentTransform::create();
        rootNode->setCore(Trans);

        // add the torus as a child
        rootNode->addChild(scene);

        //Make The Physics Characteristics Node
        PhysicsCharacteristicsDrawableRecPtr PhysDrawable = PhysicsCharacteristicsDrawable::create();
        PhysDrawable->setRoot(rootNode);

        NodeRecPtr PhysDrawableNode = Node::create();
        PhysDrawableNode->setCore(PhysDrawable);
        PhysDrawableNode->setTravMask(TypeTraits<UInt32>::getMin());

        rootNode->addChild(PhysDrawableNode);


        //Setup Physics Scene
        PhysicsWorldRecPtr physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

        PhysicsHashSpaceRecPtr physicsSpace = PhysicsHashSpace::create();

        PhysicsHandlerRecPtr physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
        physHandler->setUpdateNode(rootNode);

        physHandler->attachUpdateProducer(TutorialWindow);


        /************************************************************************/
        /* create spaces, geoms and bodys                                       */
        /************************************************************************/
        //create a group for our space
        GroupRecPtr spaceGroup;
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
        //create the ground plane
        GeometryRecPtr plane;
        NodeRecPtr planeNode = makeBox(30.0, 30.0, 1.0, 1, 1, 1);
        plane = dynamic_cast<Geometry*>(planeNode->getCore());
        //and its Material
        SimpleMaterialRecPtr plane_mat = SimpleMaterial::create();
        plane_mat->setAmbient(Color3f(0.7,0.7,0.7));
        plane_mat->setDiffuse(Color3f(0.9,0.6,1.0));

        plane->setMaterial(plane_mat);



        //create Physical Attachments
        PhysicsBoxGeomRecPtr planeGeom = PhysicsBoxGeom::create();
        planeGeom->setLengths(Vec3f(30.0, 30.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(physicsSpace);


        //add Attachments to nodes...
        spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addAttachment(physHandler);    
        spaceGroupNode->addAttachment(physicsWorld);
        spaceGroupNode->addChild(planeNode);


        planeNode->addAttachment(planeGeom);


        scene->addChild(spaceGroupNode);


        //Create Statistics Foreground
        SimpleStatisticsForegroundRecPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
        PhysicsStatForeground->setSize(25);
        PhysicsStatForeground->setColor(Color4f(0,1,0,0.7));
        PhysicsStatForeground->addElement(WindowEventProducer::statWindowLoopTime, "Draw FPS: %r.3f");
        PhysicsStatForeground->getCollector()->getElem(WindowEventProducer::statWindowLoopTime, true);
        PhysicsStatForeground->addElement(RenderAction::statNGeometries, 
                                         "%d Nodes drawn");
        PhysicsStatForeground->getCollector()->getElem(RenderAction::statNGeometries, true);
        PhysicsStatForeground->addElement(PhysicsHandler::statPhysicsTime, 
                                          "Physics time: %.3f s");
        PhysicsStatForeground->getCollector()->getElem(PhysicsHandler::statPhysicsTime, true);
        PhysicsStatForeground->addElement(PhysicsHandler::statCollisionTime, 
                                          "Collision time: %.3f s");
        PhysicsStatForeground->getCollector()->getElem(PhysicsHandler::statCollisionTime, true);
        PhysicsStatForeground->addElement(PhysicsHandler::statSimulationTime, 
                                          "Simulation time: %.3f s");
        PhysicsStatForeground->getCollector()->getElem(PhysicsHandler::statSimulationTime, true);
        PhysicsStatForeground->addElement(PhysicsHandler::statNCollisions, 
                                          "%d collisions");
        PhysicsStatForeground->getCollector()->getElem(PhysicsHandler::statNCollisions, true);
        PhysicsStatForeground->addElement(PhysicsHandler::statNCollisionTests, 
                                          "%d collision tests");
        PhysicsStatForeground->getCollector()->getElem(PhysicsHandler::statNCollisionTests, true);
        PhysicsStatForeground->addElement(PhysicsHandler::statNPhysicsSteps, 
                                          "%d simulation steps per frame");
        PhysicsStatForeground->getCollector()->getElem(PhysicsHandler::statNPhysicsSteps, true);
        TutorialWindow->connectUpdate(boost::bind(handleStatisticsReset, _1), boost::signals2::at_front);
        StatCollector::setGlobalCollector(PhysicsStatForeground->getCollector());


        SimpleStatisticsForegroundRecPtr RenderStatForeground = SimpleStatisticsForeground::create();
        RenderStatForeground->setSize(25);
        RenderStatForeground->setColor(Color4f(0,1,0,0.7));





        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        sceneManager.getWindow()->getPort(0)->addForeground(PhysicsStatForeground);
        sceneManager.getWindow()->getPort(0)->addForeground(RenderStatForeground);

        
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
            TriGeometryBase.get(),
            spaceGroupNode.get(),
            PhysDrawableNode.get(),
            physicsWorld.get(),
            physicsSpace.get()));

        // show the whole rootNode
        sceneManager.getNavigator()->set(Pnt3f(20.0,20.0,10.0), Pnt3f(0.0,0.0,0.0), Vec3f(0.0,0.0,1.0));
        sceneManager.getNavigator()->setMotionFactor(1.0f);
        sceneManager.getCamera()->setFar(10000.0f);
        sceneManager.getCamera()->setNear(0.1f);

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01SimplePhysics");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}