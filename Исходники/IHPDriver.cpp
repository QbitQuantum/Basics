void IHPDriver::handleEvent(core::objectmodel::Event *event)
{
    //std::cout<<"IHPDriver::handleEvent() called:"<<std::endl;//////////////////////////////////////////////////////
    static double time_prev;

    if (firstDevice && dynamic_cast<sofa::simulation::AnimateEndEvent *> (event))
    {
        // force the simulation to be "real-time"
        CTime *timer;
        timer = new CTime();
        double time = 0.001*timer->getRefTime()* PaceMaker::time_scale; // in sec

        // if the computation time is shorter than the Dt set in the simulation... it waits !
        if ((time- time_prev) < getContext()->getDt() )
        {
            double wait_time = getContext()->getDt() - time + time_prev;
            timer->sleep(wait_time);
        }

        time_prev=time;
    }

    if (dynamic_cast<sofa::simulation::AnimateBeginEvent *>(event))
    {
        //turnOn xitactVisu
        if(!visuActif && xitactVisu.getValue() && initVisu)
        {
            simulation::Node *parent = dynamic_cast<simulation::Node *>(this->getContext());
            parent->addChild(nodeXitactVisual);
            nodeXitactVisual->updateContext();
            visuActif = true;
        }
        //turnOff xitactVisu
        else if(initVisu && visuActif && !xitactVisu.getValue())
        {
            simulation::Node *parent = dynamic_cast<simulation::Node *>(this->getContext());
            parent->removeChild(nodeXitactVisual);
            nodeXitactVisual->updateContext();
            visuActif=false;
        }


        // calcul des angles à partir de la direction proposée par l'interface...
        // cos(ThetaX) = cx   sin(ThetaX) = sx  cos(ThetaZ) = cz   sin(ThetaZ) = sz .
        // au repos (si cx=1 et cz=1) on a  Axe y
        // on commence par tourner autour de x   puis autour de z
        //   [cz  -sz   0] [1   0   0 ] [0]   [ -sz*cx]
        //   [sz   cz   0]*[0   cx -sx]*[1] = [ cx*cz ]
        //   [0    0    1] [0   sx  cx] [0]   [ sx    ]

        xiTrocarAcquire();
        XiToolState state;

        xiTrocarQueryStates();
        xiTrocarGetState(indexTool.getValue(), &state);

        // saving informations in class structure.
        data.simuState = state;

        Vector3 dir;

        dir[0] = -(double)state.trocarDir[0];
        dir[1] = (double)state.trocarDir[2];
        dir[2] = -(double)state.trocarDir[1];

        double pi = 3.1415926535;

        double thetaY;
        double thetaX;

        thetaY = (atan2(dir[0],-sqrt(1-dir[0]*dir[0])));
        thetaX = (pi-acos(dir[2]*sqrt(1-dir[0]*dir[0])/(dir[0]*dir[0]-1)));

        //look if thetaX and thetaY are NaN
        if(!(thetaX == thetaX))
        {
            cout<<"ratrapage X"<<endl;
            thetaX=pi;
        }
        if(!(thetaY == thetaY))
        {
            cout<<"ratrapage Y"<<endl;
            thetaY=pi;
        }

        if(dir[1]>=0)
            thetaX*=-1;

        while(thetaY<=0)
            thetaY+=2*pi;
        while(thetaX<=0)
            thetaX+=2*pi;
        while(thetaY>2*pi)
            thetaY-=2*pi;
        while(thetaX>2*pi)
            thetaX-=2*pi;



        if (showToolStates.getValue()) // print tool state
            this->displayState();

        if (testFF.getValue()) // try FF when closing handle
            this->updateForce();

        // Button and grasp handling event
        XiStateFlags stateFlag;
        stateFlag = state.flags - data.restState.flags;
        if (stateFlag == XI_ToolButtonLeft)
            this->leftButtonPushed();
        else if (stateFlag == XI_ToolButtonRight)
            this->rightButtonPushed();

        if (state.opening < graspThreshold.getValue())
        {
            this->graspClosed();
        }

        //XitactVisu
        VecCoord& posD =(*visualXitactDOF->x.beginEdit());
        posD.resize(4);
        VecCoord& posA =(*visualAxesDOF->x.beginEdit());
        posA.resize(3);

        VecCoord& posB =(*positionBase.beginEdit());
        //data.positionBaseGlobal[0]=posB[0];
        data.posBase=posB[0].getCenter();
        data.quatBase=posB[0].getOrientation();
        SolidTypes<double>::Transform tampon(posB[0].getCenter(),posB[0].getOrientation());
        positionBase.endEdit();
        posD[0].getCenter() =  tampon.getOrigin();
        posD[0].getOrientation() =  tampon.getOrientation();

        sofa::helper::Quater<double> qRotX(Vec3d(1,0,0),pi/2);
        sofa::helper::Quater<double> qRotY(Vec3d(0,0,-1),pi/2);
        SolidTypes<double>::Transform transformRotX(Vec3d(0.0,0.0,0.0),qRotX);
        SolidTypes<double>::Transform transformRotY(Vec3d(0.0,0.0,0.0),qRotY);
        SolidTypes<double>::Transform tamponAxes=tampon;
        posA[0].getCenter() =  tamponAxes.getOrigin();
        posA[0].getOrientation() =  tamponAxes.getOrientation();
        tamponAxes*=transformRotX;
        posA[1].getCenter() =  tamponAxes.getOrigin();
        posA[1].getOrientation() =  tamponAxes.getOrientation();
        tamponAxes*=transformRotY;
        posA[2].getCenter() =  tamponAxes.getOrigin();
        posA[2].getOrientation() =  tamponAxes.getOrientation();

        sofa::helper::Quater<double> qy(Vec3d(0,1,0),thetaY);
        sofa::helper::Quater<double> qx(Vec3d(1,0,0),thetaX);
        SolidTypes<double>::Transform transform2(Vec3d(0.0,0.0,0.0),qx*qy);
        tampon*=transform2;
        posD[1].getCenter() =  tampon.getOrigin();
        posD[1].getOrientation() =  tampon.getOrientation();

        sofa::helper::Quater<float> quarter3(Vec3d(0.0,0.0,1.0),-state.toolRoll);
        SolidTypes<double>::Transform transform3(Vec3d(0.0,0.0,-state.toolDepth*Scale.getValue()),quarter3);
        tampon*=transform3;
        posD[2].getCenter() =  tampon.getOrigin();
        posD[2].getOrientation() =  tampon.getOrientation();

        if(posTool)
        {
            VecCoord& posT = *(posTool->x0.beginEdit());
            //cout<<"xitact "<<deviceIndex.getValue()<<" "<<posD[2]<<endl;
            posT[deviceIndex.getValue()]=posD[2];
            posTool->x0.endEdit();
        }

        sofa::helper::Quater<float> quarter4(Vec3d(0.0,1.0,0.0),-data.simuState.opening/(float)2.0);
        SolidTypes<double>::Transform transform4(Vec3d(0.0,0.0,0.44*Scale.getValue()),quarter4);
        tampon*=transform4;
        posD[3].getCenter() =  tampon.getOrigin();
        posD[3].getOrientation() =  tampon.getOrientation();
        visualXitactDOF->x.endEdit();

        Vec1d& openT = (*openTool.beginEdit());
        openT[0]=(data.simuState.opening)*(maxTool.getValue()-minTool.getValue())+minTool.getValue();
        openTool.endEdit();

        if(changeScale)
        {
            float rapport=((float)Scale.getValue())/oldScale;
            for(int j = 0; j<4 ; j++)
            {
                sofa::defaulttype::ResizableExtVector<sofa::defaulttype::Vec<3,float>> &scaleMapping = *(visualNode[j].mapping->points.beginEdit());
                for(unsigned int i=0; i<scaleMapping.size(); i++)
                {
                    for(int p=0; p<3; p++)
                        scaleMapping[i].at(p)*=rapport;
                }
                visualNode[j].mapping->points.endEdit();
            }
            oldScale=(float)Scale.getValue();
            changeScale=false;
        }


    }
    if (dynamic_cast<core::objectmodel::KeypressedEvent *>(event))
    {
        core::objectmodel::KeypressedEvent *kpe = dynamic_cast<core::objectmodel::KeypressedEvent *>(event);
        onKeyPressedEvent(kpe);
    }
    else if (dynamic_cast<core::objectmodel::KeyreleasedEvent *>(event))
    {
        core::objectmodel::KeyreleasedEvent *kre = dynamic_cast<core::objectmodel::KeyreleasedEvent *>(event);
        onKeyReleasedEvent(kre);
    }


    //std::cout<<"IHPDriver::handleEvent() ended:"<<std::endl;
}