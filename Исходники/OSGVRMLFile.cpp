void VRMLFile::use(const Char8 *szName)
{
    SceneFileHandler::the()->updateReadProgress();
    Time beginUse = getSystemTime();

    FieldContainerUnrecPtr pUsedFC;

    // try to find a container with the given name attachment

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "VRMLFile::use : looking for "
          << szName
          << std::endl;

    VRMLNodeHelper::incIndent();
#endif

    pUsedFC = findReference(szName);

    if(pUsedFC == NULL)
    {
        PWARNING << "No fieldContainer with name found to use"
                 << szName
                 << std::endl;
    }
    else
    {
        // assign nodepointer to current sf|mf field

        if(_pCurrNodeHelper != NULL)
        {
            if(pUsedFC->getType().isNode())
            {
                Node *pRootNode = dynamic_pointer_cast<Node>(pUsedFC);
                
                pUsedFC = cloneTree(pRootNode);
            }
            
            _pCurrNodeHelper->setContainerFieldValue( pUsedFC,
                                                     _pCurrentFieldDesc,
                                                     _pCurrentFieldFC  );
        }
    }

#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::decIndent();
#endif

    useTime += (getSystemTime() - beginUse);
}