    //---------------------------------------------------------------------
    void XMLSkeletonSerializer::writeSkeleton(const Skeleton* pSkel)
    {
        TiXmlElement* rootNode = mXMLDoc->RootElement();

        TiXmlElement* bonesElem = 
            rootNode->InsertEndChild(TiXmlElement("bones"))->ToElement();

        unsigned short numBones = pSkel->getNumBones();
		LogManager::getSingleton().logMessage("There are " + StringConverter::toString(numBones) + " bones.");
        unsigned short i;
        for (i = 0; i < numBones; ++i)
        {
			LogManager::getSingleton().logMessage("   Exporting Bone number " + StringConverter::toString(i));
            Bone* pBone = pSkel->getBone(i);
            writeBone(bonesElem, pBone);
        }

        // Write parents
        TiXmlElement* hierElem = 
            rootNode->InsertEndChild(TiXmlElement("bonehierarchy"))->ToElement();
        for (i = 0; i < numBones; ++i)
        {
            Bone* pBone = pSkel->getBone(i);
			String name = pBone->getName() ;

			if ((pBone->getParent())!=NULL) // root bone
            {
                Bone* pParent = (Bone*)pBone->getParent();
                writeBoneParent(hierElem, name, pParent->getName());
            }
        }


    }