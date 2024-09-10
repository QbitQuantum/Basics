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
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed,_1));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        UInt32 SceneMask(1),
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
            Octree::buildTree(RootNode,SceneMask,6,1.5,true);

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

        //Create the Path Geometry
        //Generate the Path
        OctreeAStarAlgorithm AlgorithmObj;
        SLOG << "Started AStar Search" << std::endl;
        StartTime = getSystemTime();
        Pnt3f Start(-4.01f,1.01f,10.01f),Goal(-4.01f,-0.01f,-7.01f);
        std::vector<Pnt3f> Path =
            AlgorithmObj.search(TheOctree,Start,Goal);
        Path.front() = Start;
        Path.back() = Goal;
        SLOG << "Finished AStar Search: " << getSystemTime() - StartTime << " s" << std::endl;

        NodeRecPtr PathNode = createPathGeometry(Path);
        PathNode->setTravMask(PathMask);
        RootNode->addChild(PathNode);

        NodeRecPtr StartNode = makeSphere(1.0, 2);
        TransformRecPtr StartNodeTransform = Transform::create();
        Matrix StartNodeMatrix;
        StartNodeMatrix.setTranslate(Start);
        StartNodeMatrix.setScale(0.1f);
        StartNodeTransform->setMatrix(StartNodeMatrix);
        NodeRecPtr StartNodeTransformNode = makeNodeFor(StartNodeTransform);
        StartNodeTransformNode->addChild(StartNode);
        StartNodeTransformNode->setTravMask(PathMask);
        RootNode->addChild(StartNodeTransformNode);

        NodeRecPtr GoalNode = makeSphere(1.0, 2);
        TransformRecPtr GoalNodeTransform = Transform::create();
        Matrix GoalNodeMatrix;
        GoalNodeMatrix.setScale(0.1f);
        GoalNodeMatrix.setTranslate(Goal);
        GoalNodeTransform->setMatrix(GoalNodeMatrix);
        NodeRecPtr GoalNodeTransformNode = makeNodeFor(GoalNodeTransform);
        GoalNodeTransformNode->addChild(GoalNode);
        GoalNodeTransformNode->setTravMask(PathMask);
        RootNode->addChild(GoalNodeTransformNode);


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