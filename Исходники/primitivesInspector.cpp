void PrimitivesInspector::NodeTab::assembleList(){


    for (int i=0;i<(int)mine->listButton.size();i++){
        mine->listButton[i]->remove();
    }
    mine->listButton.clear();
    mine->listName.clear();
    mine->listProp.clear();
    mine->listIcon.clear();

    if (mine->scrollBar){
        mine->scrollBar->remove();
        mine->scrollBar=NULL;
    }

        cout << "creating list..." << endl;

    mine->listName.push_back("RootNode");
    mine->listName.push_back("WaitTime");
    mine->listName.push_back("WalkTo");
    mine->listName.push_back("KeyInput");
    mine->listName.push_back("SwitchCamera");
    mine->listName.push_back("SetAnimation");
    mine->listName.push_back("StopAnim");
    mine->listName.push_back("WaitForEvent");
    mine->listName.push_back("TriggerEvent");
    mine->listName.push_back("ConsoleCommand");
    mine->listName.push_back("Interpolate");
    mine->listName.push_back("SetWalkTarget");
    mine->listName.push_back("SetHidden");
    mine->listName.push_back("TriggerActor");
    mine->listName.push_back("AttachTo");
    mine->listName.push_back("PerformAction");
    mine->listName.push_back("SetProperty");
    mine->listName.push_back("SetBackground");
    mine->listName.push_back("MorphSpriteMesh");
    mine->listName.push_back("load new");

    mine->listProp.push_back("8RootNode");
    mine->listProp.push_back("16WaitForTimerNode");
    mine->listProp.push_back("10WalkToNode");
    mine->listProp.push_back("12KeyInputNode");
    mine->listProp.push_back("16SwitchCameraNode");
    mine->listProp.push_back("16SetAnimationNode");
    mine->listProp.push_back("12StopAnimNode");
    mine->listProp.push_back("16WaitForEventNode");
    mine->listProp.push_back("16TriggerEventNode");
    mine->listProp.push_back("18ConsoleCommandNode");
    mine->listProp.push_back("15InterpolateNode");
    mine->listProp.push_back("17SetWalkTargetNode");
    mine->listProp.push_back("13SetHiddenNode");
    mine->listProp.push_back("16TriggerActorNode");
    mine->listProp.push_back("12AttachToNode");
    mine->listProp.push_back("17PerformActionNode");
    mine->listProp.push_back("15SetPropertyNode");
    mine->listProp.push_back("17SetBackgroundNode");
    mine->listProp.push_back("19MorphSpriteMeshNode");
    mine->listProp.push_back("8LoadNode");

    int i;
    for (i=0; i<(int)mine->listProp.size(); i++){
        mine->sceneData->actorInfo["16CreateNodeButton"].actorReference->create();
        mine->listButton.push_back(mine->sceneData->buttonList.back());


        mine->listButton[i]->name=mine->listName[i];
        mine->listButton[i]->buttonProperty=mine->listProp[i];
        mine->listButton[i]->setTextureID("icon_nodeMenu");

        mine->listButton[i]->level=mine->level+1;
        mine->listButton[i]->bDrawName=true;
        mine->listButton[i]->tooltip=mine->listName[i];
        mine->listButton[i]->color=Vector4f(1,1,1,1.0);
        mine->listButton[i]->bPermanent=true;
        mine->listButton[i]->bDragable=true;

            mine->listButton[i]->drawNameOffset.y=mine->listHeight/2.0;
            if (mine->listWidth>0)
                mine->listButton[i]->scale.x=mine->listWidth;

            //leave room for name beneath icon
            if (mine->listHeight>0)
                mine->listButton[i]->scale.y=mine->listHeight-16.0;

        mine->listButton[i]->setup();
        mine->placeButton(i,i);
        //set this because we want to drag buttons around!
        mine->listButton[i]->initialLocation=mine->listButton[i]->location;

    }

    //add udpInput as non-node at the end
    mine->listName.push_back("UDPInput");
    mine->listProp.push_back("8UdpInput");
    mine->sceneData->actorInfo["17CreateActorButton"].actorReference->create();
    mine->listButton.push_back(mine->sceneData->buttonList.back());


        mine->listButton[i]->name=mine->listName[i];
        mine->listButton[i]->buttonProperty=mine->listProp[i];
        mine->listButton[i]->setTextureID("icon_base");

        mine->listButton[i]->level=mine->level+1;
        mine->listButton[i]->bDrawName=true;
        mine->listButton[i]->color=Vector4f(1,1,1,1.0);
        mine->listButton[i]->bPermanent=true;
        mine->listButton[i]->bDragable=true;

            mine->listButton[i]->drawNameOffset.y=mine->listHeight/2.0;
            if (mine->listWidth>0)
                mine->listButton[i]->scale.x=mine->listWidth;

            //leave room for name beneath icon
            if (mine->listHeight>0)
                mine->listButton[i]->scale.y=mine->listHeight-16.0;

        mine->listButton[i]->setup();
        mine->placeButton(i,i);
        //set this because we want to drag buttons around!
        mine->listButton[i]->initialLocation=mine->listButton[i]->location;



    cout << "NodeInspector: our Button list is: "<< mine->listButton.size() <<" elements long..." << endl;

    if (mine->listButton.size()>0)
        mine->listSize.y=mine->listButton[mine->listButton.size()-1]->location.y+mine->listButton[mine->listButton.size()-1]->scale.y - mine->location.y;
    else
        mine->listSize.y=0;

}