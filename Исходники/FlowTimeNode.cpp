    virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
    {
        switch (event)
        {
        case eFE_Initialize:
            break;
        case eFE_Activate:
        {
            if(!IsPortActive(pActInfo, EIP_Load))
                return;

            // get the file name
            string pathAndfileName;
            const string fileName = GetPortString(pActInfo, EIP_FileName);
            if (fileName.empty())
                return;

            ILevelInfo* pCurrentLevel = gEnv->pGame->GetIGameFramework()->GetILevelSystem()->GetCurrentLevel();
            string path = pCurrentLevel ? pCurrentLevel->GetPath() : "";
            pathAndfileName.Format("%s/%s", path.c_str(), fileName.c_str());

            // try to load it
            XmlNodeRef root = GetISystem()->LoadXmlFromFile( pathAndfileName );
            if (root == NULL)
            {
                CryWarning(VALIDATOR_MODULE_SYSTEM, VALIDATOR_WARNING, "FlowGraph: TimeOfDay Loading Node: Could not load tod file %s. Aborting.", pathAndfileName.c_str());
                ActivateOutput(pActInfo, EOP_Fail, true);
                return;
            }

            // get the TimeofDay interface
            ITimeOfDay *pTimeOfDay = gEnv->p3DEngine->GetTimeOfDay();
            if (pTimeOfDay == NULL)
            {
                CryWarning(VALIDATOR_MODULE_SYSTEM, VALIDATOR_WARNING, "FlowGraph: TimeOfDay Loading Node: Could not obtain ITimeOfDay interface from engine. Aborting.");
                ActivateOutput(pActInfo, EOP_Fail, true);
                return;
            }

            // try to serialize from that file
            pTimeOfDay->Serialize( root,true );
            pTimeOfDay->Update(true, true);

            ActivateOutput(pActInfo, EOP_Success, true);
        }
        break;
        }
    }