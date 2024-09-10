osgDB::ReaderWriter::ReadResult
ReaderWriterFBX::readNode(const std::string& filenameInit,
                          const Options* options) const
{
    try
    {
        std::string ext(osgDB::getLowerCaseFileExtension(filenameInit));
        if (!acceptsExtension(ext)) return ReadResult::FILE_NOT_HANDLED;

        std::string filename(osgDB::findDataFile(filenameInit, options));
        if (filename.empty()) return ReadResult::FILE_NOT_FOUND;

        KFbxSdkManager* pSdkManager = KFbxSdkManager::Create();

        if (!pSdkManager)
        {
            return ReadResult::ERROR_IN_READING_FILE;
        }

        CleanUpFbx cleanUpFbx(pSdkManager);

        pSdkManager->SetIOSettings(KFbxIOSettings::Create(pSdkManager, IOSROOT));

        KFbxScene* pScene = KFbxScene::Create(pSdkManager, "");

        // The FBX SDK interprets the filename as UTF-8
#ifdef OSG_USE_UTF8_FILENAME
        const std::string& utf8filename(filename);
#else
        std::string utf8filename(osgDB::convertStringFromCurrentCodePageToUTF8(filename));
#endif

        KFbxImporter* lImporter = KFbxImporter::Create(pSdkManager, "");

        if (!lImporter->Initialize(utf8filename.c_str(), -1, pSdkManager->GetIOSettings()))
        {
            return std::string(lImporter->GetLastErrorString());
        }

        if (!lImporter->IsFBX())
        {
            return ReadResult::ERROR_IN_READING_FILE;
        }

        for (int i = 0; i < lImporter->GetTakeCount(); i++)
        {
            KFbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

            lTakeInfo->mSelect = true;
        }

        if (!lImporter->Import(pScene))
        {
            return std::string(lImporter->GetLastErrorString());
        }

        //KFbxAxisSystem::OpenGL.ConvertScene(pScene);        // Doesn't work as expected. Still need to transform vertices.

        if (KFbxNode* pNode = pScene->GetRootNode())
        {
            pScene->SetCurrentTake(pScene->GetCurrentTakeName());

            bool useFbxRoot = false;
            if (options)
            {
                std::istringstream iss(options->getOptionString());
                std::string opt;
                while (iss >> opt)
                {
                    if (opt == "UseFbxRoot")
                    {
                        useFbxRoot = true;
                    }
                }
            }

            osg::ref_ptr<osgAnimation::AnimationManagerBase> pAnimationManager;
            bool bIsBone = false;
            int nLightCount = 0;
            osg::ref_ptr<Options> localOptions = NULL;
            if (options)
                localOptions = options->cloneOptions();
            else
                localOptions = new osgDB::Options();
            localOptions->setObjectCacheHint(osgDB::ReaderWriter::Options::CACHE_IMAGES);

            std::string filePath = osgDB::getFilePath(filename);
            FbxMaterialToOsgStateSet fbxMaterialToOsgStateSet(filePath, localOptions.get());

            std::set<const KFbxNode*> fbxSkeletons;
            findLinkedFbxSkeletonNodes(pNode, fbxSkeletons);

            std::map<KFbxNode*, osg::Node*> nodeMap;
            BindMatrixMap boneBindMatrices;
            std::map<KFbxNode*, osgAnimation::Skeleton*> skeletonMap;
            ReadResult res = readFbxNode(*pSdkManager, *pScene, pNode, pAnimationManager,
                bIsBone, nLightCount, fbxMaterialToOsgStateSet, nodeMap,
                boneBindMatrices, fbxSkeletons, skeletonMap, *localOptions);

            if (res.success())
            {
                fbxMaterialToOsgStateSet.checkInvertTransparency();

                resolveBindMatrices(*res.getNode(), boneBindMatrices, nodeMap);

                osg::Node* osgNode = res.getNode();
                osgNode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL,osg::StateAttribute::ON);
                osgNode->getOrCreateStateSet()->setMode(GL_NORMALIZE,osg::StateAttribute::ON);

                if (pAnimationManager.valid())
                {
                    if (osgNode->getUpdateCallback())
                    {
                        osg::Group* osgGroup = new osg::Group;
                        osgGroup->addChild(osgNode);
                        osgNode = osgGroup;
                    }

                    //because the animations may be altered after registering
                    pAnimationManager->buildTargetReference();
                    osgNode->setUpdateCallback(pAnimationManager.get());
                }

                KFbxAxisSystem fbxAxis = pScene->GetGlobalSettings().GetAxisSystem();

                if (fbxAxis != KFbxAxisSystem::OpenGL)
                {
                    int upSign;
                    KFbxAxisSystem::eUpVector eUp = fbxAxis.GetUpVector(upSign);
                    bool bLeftHanded = fbxAxis.GetCoorSystem() == KFbxAxisSystem::LeftHanded;
                    float fSign = upSign < 0 ? -1.0f : 1.0f;
                    float zScale = bLeftHanded ? -1.0f : 1.0f;

                    osg::Matrix mat;
                    switch (eUp)
                    {
                    case KFbxAxisSystem::XAxis:
                        mat.set(0,fSign,0,0,-fSign,0,0,0,0,0,zScale,0,0,0,0,1);
                        break;
                    case KFbxAxisSystem::YAxis:
                        mat.set(1,0,0,0,0,fSign,0,0,0,0,fSign*zScale,0,0,0,0,1);
                        break;
                    case KFbxAxisSystem::ZAxis:
                        mat.set(1,0,0,0,0,0,-fSign*zScale,0,0,fSign,0,0,0,0,0,1);
                        break;
                    }

                    osg::Transform* pTransformTemp = osgNode->asTransform();
                    osg::MatrixTransform* pMatrixTransform = pTransformTemp ?
                        pTransformTemp->asMatrixTransform() : NULL;
                    if (pMatrixTransform)
                    {
                        pMatrixTransform->setMatrix(pMatrixTransform->getMatrix() * mat);
                    }
                    else
                    {
                        pMatrixTransform = new osg::MatrixTransform(mat);
                        if (useFbxRoot && isBasicRootNode(*osgNode))
                        {
                            // If root node is a simple group, put all FBX elements under the OSG root
                            osg::Group* osgGroup = osgNode->asGroup();
                            for(unsigned int i = 0; i < osgGroup->getNumChildren(); ++i)
                            {
                                pMatrixTransform->addChild(osgGroup->getChild(i));
                            }
                            pMatrixTransform->setName(osgGroup->getName());
                        }
                        else
                        {
                            pMatrixTransform->addChild(osgNode);
                        }
                    }
                    osgNode = pMatrixTransform;
                }

                osgNode->setName(filenameInit);
                return osgNode;
            }
        }
    }
    catch (...)
    {
        OSG_WARN << "Exception thrown while importing \"" << filenameInit << '\"' << std::endl;
    }

    return ReadResult::ERROR_IN_READING_FILE;
}