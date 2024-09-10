Node *
ColladaVisualScene::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaVisualScene::createInstance\n"));

    ColladaInstanceVisualSceneRefPtr colInstVisScene =
        dynamic_cast<ColladaInstanceVisualScene *>(colInstElem);

    domVisual_sceneRef   visScene = getDOMElementAs<domVisual_scene>();
    const domNode_Array &nodes    = visScene->getNode_array         ();

    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(nodes[i]);

        if(colNode == NULL)
        {
            colNode = dynamic_pointer_cast<ColladaNode>(
                ColladaElementFactory::the()->create(nodes[i], getGlobal()));

            colNode->setVisualScene(this);
            colNode->read();
        }

        if(nodes.getCount() > 1)
        {
            if(_RootN == NULL)
            {
                GroupUnrecPtr group = Group::create();
                _RootN = makeNodeFor(group);
            }

            Node *childN = colNode->getTopNode();

            if(childN->getParent() != NULL)
            {
                SWARNING << "ColladaVisualScene::createInstance: <node> [" << i
                         << "] already has a parent." << std::endl;
            }

            _RootN->addChild(childN);
        }
        else
        {
            Node *childN = colNode->getTopNode();

            if(childN->getParent() != NULL)
            {
                SWARNING << "ColladaVisualScene::createInstance: <node> [" << i
                         << "] already has a parent." << std::endl;
            }

            _RootN = childN;
        }
    }

    editInstStore().push_back(_RootN);

    return _RootN;
}