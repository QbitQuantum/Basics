    //-----------------------------------------------------------------------
    void RenderQueue::addRenderable(Renderable* pRend, uint8 groupID, ushort priority)
    {
        // Find group
        RenderQueueGroup* pGroup = getQueueGroup(groupID);

        Technique* pTech;

        // tell material it's been used
        if (pRend->getMaterial())
            pRend->getMaterial()->touch();

        // Check material & technique supplied (the former since the default implementation
        // of getTechnique is based on it for backwards compatibility
        if(!pRend->getMaterial() || !pRend->getTechnique())
        {
            // Use default base white, with lighting only if vertices has normals
            RenderOperation op;
            pRend->getRenderOperation(op);
            bool useLighting = (NULL != op.vertexData->vertexDeclaration->findElementBySemantic(VES_NORMAL));
            MaterialPtr defaultMat = MaterialManager::getSingleton().getDefaultMaterial(useLighting);
            defaultMat->load();
            pTech = defaultMat->getBestTechnique();
        }
        else
            pTech = pRend->getTechnique();

        if (mRenderableListener)
        {
            // Allow listener to override technique and to abort
            if (!mRenderableListener->renderableQueued(pRend, groupID, priority, 
                &pTech, this))
                return; // rejected

            // tell material it's been used (incase changed)
            pTech->getParent()->touch();
        }
        
        pGroup->addRenderable(pRend, pTech, priority);

    }