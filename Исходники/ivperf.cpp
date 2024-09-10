static SoSeparator *
setUpGraph(const SbViewportRegion &vpReg,
	   SoInput *sceneInput,
	   Options &options)
//
//////////////////////////////////////////////////////////////
{

    // Create a root separator to hold everything. Turn
    // caching off, since the transformation will blow
    // it anyway.
    SoSeparator *root = new SoSeparator;
    root->ref();
    root->renderCaching = SoSeparator::OFF;

    // Add a camera to view the scene
    SoPerspectiveCamera *camera = new SoPerspectiveCamera;
    root->addChild(camera);

    // Add a transform node to spin the scene
    SoTransform *sceneTransform = new SoTransform;
    sceneTransform->setName(SCENE_XFORM_NAME);
    root->addChild(sceneTransform);

    // Read and add input scene graph
    SoSeparator *inputRoot = SoDB::readAll(sceneInput);
    if (inputRoot == NULL) {
	fprintf(stderr, "Cannot read scene graph\n");
	root->unref();
	exit(1);
    }
    root->addChild(inputRoot);

    SoPath 	*path;
    SoGroup	*parent, *group;
    SoSearchAction	act;

    // expand out all File nodes and replace them with groups
    //    containing the children
    SoFile 	*fileNode;
    act.setType(SoFile::getClassTypeId());
    act.setInterest(SoSearchAction::FIRST);
    act.apply(inputRoot);
    while ((path = act.getPath()) != NULL) {
	fileNode = (SoFile *) path->getTail();
	path->pop();
	parent = (SoGroup *) path->getTail();
	group = fileNode->copyChildren();
	if (group) {
	    parent->replaceChild(fileNode, group);
	    // apply action again and continue
	    act.apply(inputRoot);
	}
    }

    // expand out all node kits and replace them with groups
    //    containing the children
    SoBaseKit	*kitNode;
    SoChildList	*childList;
    act.setType(SoBaseKit::getClassTypeId());
    act.setInterest(SoSearchAction::FIRST);
    act.apply(inputRoot);
    while ((path = act.getPath()) != NULL) {
	kitNode = (SoBaseKit *) path->getTail();
	path->pop();
	parent = (SoGroup *) path->getTail();
	group = new SoGroup;
	childList = kitNode->getChildren();
	for (int i=0; i<childList->getLength(); i++) 
	    group->addChild((*childList)[i]);
	parent->replaceChild(kitNode, group);
	act.apply(inputRoot);
    }

    // check to see if there are any lights
    // if no lights, add a directional light to the scene
    act.setType(SoLight::getClassTypeId());
    act.setInterest(SoSearchAction::FIRST);
    act.apply(inputRoot);
    if (act.getPath() == NULL) { // no lights
	SoDirectionalLight *light = new SoDirectionalLight;
	root->insertChild(light, 1);
    }
    else 
	options.hasLights = TRUE;

    // check to see if there are any texures in the scene
    act.setType(SoTexture2::getClassTypeId());
    act.setInterest(SoSearchAction::FIRST);
    act.apply(inputRoot);
    if (act.getPath() != NULL)
	options.hasTextures = TRUE;

    camera->viewAll(root, vpReg);

    // print out information about the scene graph

    int32_t numTris, numLines, numPoints, numNodes;
    countPrimitives( inputRoot, numTris, numLines, numPoints, numNodes );
    printf("Number of nodes in scene graph:     %d\n", numNodes );
    printf("Number of triangles in scene graph: %d\n", numTris );
    printf("Number of lines in scene graph:     %d\n", numLines );
    printf("Number of points in scene graph:    %d\n\n", numPoints );

    // Make the center of rotation the center of
    // the scene
    SoGetBoundingBoxAction	bba(vpReg);
    bba.apply(root);
    sceneTransform->center = bba.getBoundingBox().getCenter();

    return root;
}