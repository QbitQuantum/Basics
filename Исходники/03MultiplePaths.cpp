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

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        UInt32 SceneMask(1),
               NanobotMask(2),
               PathMask(4);

        BoostPath SceneFilePath(".//Data//CellParts.osb");

        if(argc >= 2)
        {
            SceneFilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(SceneFilePath))
            {
                SceneFilePath = BoostPath(".//Data//CellParts.osb");
            }
        }

        //Make Base Geometry Node
        NodeRecPtr SceneGeometryNode =
            SceneFileHandler::the()->read(SceneFilePath.string().c_str());
        SceneGeometryNode->setTravMask(SceneMask);
        if(SceneGeometryNode == NULL)
        {
            SceneGeometryNode = makeTorus(1.0, 10.0, 24, 24);
        }
        //Construct the Root Node
        NodeRecPtr RootNode = makeCoredNode<Group>();
        RootNode->addChild(SceneGeometryNode);

        commitChanges();

        //Create the Octree

        SLOG << "Started Building Octree" << std::endl;
        SLOG << "This may take some time ..." << std::endl;
        Time StartTime;
        StartTime = getSystemTime();
		OctreePtr TheOctree =
            Octree::buildTree(RootNode,SceneMask,6,0.5,true);

        SLOG << "Building Octree: " << getSystemTime() - StartTime << " s" << std::endl;
        Pnt3f Min,Max;
        TheOctree->getRoot()->getVolume();
        SLOG << "Octree: "<< std::endl
             << "    Depth: " << TheOctree->getDepth() << std::endl
             << "    Bounds: " << TheOctree->getRoot()->getVolume().getMin() << "  :  " << TheOctree->getRoot()->getVolume().getMax() << std::endl
             << "    NodeCount: " << TheOctree->getNodeCount() << std::endl
             << "    LeafNodeCount: " << TheOctree->getLeafNodeCount() << std::endl
             << "    BranchNodeCount: " << TheOctree->getBranchNodeCount() << std::endl
             << "    IntersectingNodeCount: " << TheOctree->getIntersectingNodeCount() << std::endl
             << "    IntersectingLeafNodeCount: " << TheOctree->getIntersectingLeafNodeCount() << std::endl;

        //Make the Nanobot Nodes
        BoostPath NanobotFilePath(".//Data//Nanobot.osb");
        NodeRecPtr NanobotGeoNode =
            SceneFileHandler::the()->read(NanobotFilePath.string().c_str());

        NanobotVector Nanobots;

        UInt32 NumNanobots(3);
        for(UInt32 i(0) ; i<NumNanobots ; ++i)
        {
            NanobotDetails TheDetails;

            //Get the Transform node for the Nanobot
            TheDetails._Transform = Transform::create();
            Matrix NanobotMatrix;
            
            Pnt3f Min,Max;
            SceneGeometryNode->getVolume().getBounds(Min,Max);
            Min = Min + ShrinkFactor;
            Max = Max - ShrinkFactor;
            NanobotMatrix.setTranslate(randomOpenPosition(Min,Max,TheOctree).subZero());
            NanobotMatrix.setScale(0.06f);
            TheDetails._Transform->setMatrix(NanobotMatrix);

            TheDetails._Node = makeNodeFor(TheDetails._Transform);
            TheDetails._Node->addChild(cloneTree(NanobotGeoNode));
            TheDetails._Node->setTravMask(NanobotMask);
            
            TheDetails._PathVisNode = Node::create();

            Nanobots.push_back(TheDetails);

            makeNanobotPath(Nanobots.back(), TheOctree, TutorialWindow, Min,Max);
        }

        for(UInt32 i(0) ; i<Nanobots.size() ; ++i)
        {
            RootNode->addChild(Nanobots[i]._Node);
            RootNode->addChild(Nanobots[i]._PathVisNode);
        }
        commitChanges();


        //NodeRecPtr StartNode = makeSphere(1.0, 2);
        //TransformRecPtr StartNodeTransform = Transform::create();
        //Matrix StartNodeMatrix;
        //StartNodeMatrix.setTranslate(Start);
        //StartNodeMatrix.setScale(0.1f);
        //StartNodeTransform->setMatrix(StartNodeMatrix);
        //NodeRecPtr StartNodeTransformNode = makeNodeFor(StartNodeTransform);
        //StartNodeTransformNode->addChild(StartNode);
        //StartNodeTransformNode->setTravMask(PathMask);
        //RootNode->addChild(StartNodeTransformNode);

        //NodeRecPtr GoalNode = makeSphere(1.0, 2);
        //TransformRecPtr GoalNodeTransform = Transform::create();
        //Matrix GoalNodeMatrix;
        //GoalNodeMatrix.setScale(0.1f);
        //GoalNodeMatrix.setTranslate(Goal);
        //GoalNodeTransform->setMatrix(GoalNodeMatrix);
        //NodeRecPtr GoalNodeTransformNode = makeNodeFor(GoalNodeTransform);
        //GoalNodeTransformNode->addChild(GoalNode);
        //GoalNodeTransformNode->setTravMask(PathMask);
        //RootNode->addChild(GoalNodeTransformNode);

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      TutorialWindow.get(),
                                                      SceneGeometryNode.get(),
                                                      TheOctree,
                                                      Nanobots));


        //Set the background
        SolidBackgroundRecPtr TheBackground = SolidBackground::create();
        TheBackground->setColor(Color3f(0.0f,0.0f,0.0f));

        // tell the manager what to manage
        sceneManager.setRoot  (RootNode);
        sceneManager.getWindow()->getPort(0)->setBackground(TheBackground);

        // show the whole RootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01AStarPathing");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}