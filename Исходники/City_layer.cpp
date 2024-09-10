// on "init" you need to initialize your instance
bool City_layer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    selected=nullptr;
    horizontalPlane=Plane(Vec3(0,1,0),Vec3(0,0,0));
    _rotation=0.f;
    //_firstrotation=0.f;
    
    Size size=Director::getInstance()->getWinSize();
    pCamera=Camera::createPerspective(60.0,size.width/size.height,0.1f,2000);
    pCamera->setCameraFlag(CameraFlag::USER1);
    pCamera->setPosition3D(Vec3(0,250,500));
    pCamera->lookAt(Vec3(0,0,0));
    addChild(pCamera);
    //sdsdsdsd
    
        node1=DrawNode3D::create();
        node1->clear();
        node1->setCameraMask(2);
        addChild(node1);
    
   // 天空盒
//    Skybox*sky=Skybox::create("Default/desert_left.jpg", "Default/desert_right.jpg", "Default/desert_top.jpg", "Default/desert_top.jpg", "Default/desert_front.jpg", "Default/desert_back.jpg");
//    sky->setCameraMask(2);
//    addChild(sky);

    
    
//    Terrain::DetailMap r("TerrainTest/dirt.jpg"),g("TerrainTest/Grass2.jpg"),b("TerrainTest/road.jpg"),a("TerrainTest/GreenSkin.jpg");
//    
//    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);
//    
//    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
//    _terrain->setLODDistance(3.2f,6.4f,9.6f);
//    _terrain->setMaxDetailMapAmount(4);
//    addChild(_terrain);
//    _terrain->setCameraMask(2);
//    _terrain->setDrawWire(false);
    
    
    Terrain::DetailMap r("TerrainTest/dirt.jpg"),g("TerrainTest/Grass2.jpg"),b("TerrainTest/road.jpg"),a("TerrainTest/GreenSkin.jpg");
    
    //Terrain::TerrainData data("TerrainTest/heightmap0.jpg","TerrainTest/alphamapyellow.png",r,g,b,a);
   
    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);
   
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    //_terrain->setLightMap("TerrainTest/Lightmap.png");
  
    _terrain->setLODDistance(3.2f,6.4f,9.6f);
    _terrain->setMaxDetailMapAmount(4);
    addChild(_terrain);
   
    _terrain->setScale(20.f, 1.f);
    _terrain->setScaleZ(20.f);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);

    // create_house("garbageTruck", Vec3(-50,0,100), Vec3(0,0,0),0.3);
    create_house("fanceWooden", Vec3(100,0,-100), Vec3(0,0,0),0.3);
    
    create_human1(Vec3(-50,0,100),1);
    create_human2(Vec3(50,0,100),1);
    
    create_house("houseBig", Vec3(-100,0,-100), Vec3(0,0,0),0.3);
    
//    auto floor=Sprite3D::create("plane.c3t","plane.png");
//    floor->setPosition3D(Vec3(480,0,0));
//    floor->setScaleX(100);
//    floor->setScaleY(100);
//    floor->setRotation3D(Vec3(90,0,0));
//    floor->setCameraMask(2);
//    addChild(floor);
//    
//    
//    Charecter1*player=Charecter1::create();
//    player->setPosition3D(Vec3(480,10,0));
//    player->setRotation3D(Vec3(0,0,0));
//    player->stand();
//    player->setCameraMask(2);
//    addChild(player,0,9);
//    
//    create_monster(Vec3(300,10,200));
//    create_monster(Vec3(500,10,-100));
//    create_monster(Vec3(-100,10,-400));
//    create_monster(Vec3(-100,10,300));
//    create_monster(Vec3(-900,10,1300));
//    create_monster(Vec3(-900,10,-1300));
//     create_monster(Vec3(1500,10,1300));
//     create_monster(Vec3(1500,10,-1300));
    auto touchEvt=EventListenerTouchOneByOne::create();
    touchEvt->onTouchBegan=[=](Touch*ptouch,Event*pevent){
        
        
            auto location = ptouch->getLocationInView();
            auto obbSize = vecObj.size();
            if(obbSize)
            {
                CCLOG("size:%lu",obbSize);
                Ray ray;
                calculateRayByLocationInView(&ray,location);
                bool touchOne=false;
                for(decltype(obbSize) i = 0; i < obbSize; i++)
                {
//                    Vec3 des = ray.intersects(horizontalPlane);
//                    CCLOG("X:%f,Y:%f,Z:%f",des.x,des.y,des.z);
//                    CCLOG("i:%lu",i);
                    if(ray.intersects(vecObj.at(i)->getAABB()))
                    {
                        touchOne=true;
                        if(dynamic_cast<CharecterBase*>(selected)){
                            auto pp = static_cast<CharecterBase*>(selected);
                            pp->mainLogic();
                            pp->scheduleUpdate();
                            
                        }
                        selected=vecObj.at(i);
//                        Vec3 corners[8]={};
//                        AABB aabbsp1=_aabb[i];
//                        aabbsp1.getCorners(corners);
//                        node1->drawCube(corners, Color4F(1,0,0,1));

                    }
                }
            
                if(!touchOne){
                        if(selected){
                            auto location = ptouch->getLocationInView();
                            Ray ray;
                            calculateRayByLocationInView(&ray,location);
                            Vec3 des = ray.intersects(horizontalPlane);
                    
                            if(dynamic_cast<CharecterBase*>(selected)){
                                //旋转
                                selected->unscheduleAllCallbacks();
                    
                                Vec3 delta=des-selected->getPosition3D();
                    
                                float angle =  Vec2(0,1).getAngle(Vec2(delta.x,delta.z));
                                if(delta.x!=0||delta.z!=0){
                                    Quaternion tt(Vec3(0,-1,0),angle);
                                    selected->setRotationQuat(tt);
                                }
                                //移动
                                auto pp = static_cast<CharecterBase*>(selected);
                                pp->speedDirection=Vec3(0,0,0);//自由移动失效
                                pp->walk();
                                
                                auto time =delta.length()/pp->walk_speed/30;
                                
                                CCLOG("%f->length,%f->time",delta.length(),time);
                                pp->runAction(Sequence::create(MoveTo::create(time, des),CallFuncN::create([=](Ref*pSender){
                                    pp->stand();
                                }),NULL));
                                
                            }else{
                                selected=nullptr;
                            }
                }
                }
            }
        

        
        return true;
    };
    touchEvt->onTouchMoved=[=](Touch*ptouch,Event*pevent){
           // 圆面相机 第3人称相机的移动
//            auto location=ptouch->getLocation();
//            Vec2 newPos=ptouch->getPreviousLocation()-location;
//            _rotation+=newPos.x/1000; //算出角度
//       
//            float deltax=100*sin(_rotation);//x增量
//            float deltaz=100*cos(_rotation);//z增量
//            pCamera->setPosition3D(Vec3(deltax,50,deltaz));
//            pCamera->lookAt(Vec3(0,0,0));
        auto location = ptouch->getLocation();
        auto delta=ptouch->getDelta();
        pCamera->setPosition3D(pCamera->getPosition3D()+Vec3(-delta.x,0,delta.y));
       // pCamera->lookAt(Vec3(0,0,0));
   
           };
  //    touchEvt->onTouchEnded=[=](Touch*ptouch,Event*pevent){
//    if(selected){
//        auto location = ptouch->getLocationInView();
//        Ray ray;
//        calculateRayByLocationInView(&ray,location);
//        Vec3 des = ray.intersects(horizontalPlane);
//        
//        if(dynamic_cast<CharecterBase*>(selected)){
//            //旋转
//            selected->unscheduleAllCallbacks();
//            
//            Vec3 delta=des-selected->getPosition3D();
//            
//            float angle =  Vec2(0,1).getAngle(Vec2(delta.x,delta.z));
//            if(delta.x!=0||delta.z!=0){
//                Quaternion tt(Vec3(0,-1,0),angle);
//                selected->setRotationQuat(tt);
//            }
//            //移动
//            auto pp = static_cast<CharecterBase*>(selected);
//            pp->speedDirection=Vec3(0,0,0);//自由移动失效
//            pp->walk();
//            
//            auto time =delta.length()/pp->walk_speed/30;
//            
//            CCLOG("%f->length,%f->time",delta.length(),time);
//            pp->runAction(Sequence::create(MoveTo::create(time, des),CallFuncN::create([=](Ref*pSender){
//                pp->stand();
//            }),NULL));
//            
//        }else{
//            selected=nullptr;
//        }
//        
//    }
     // };

    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt,this);
//
    scheduleUpdate();
    
    
    
    
    //地图缩放
    auto listener=EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan=[&](const std::vector<Touch*>&touches,Event *pevent)
    {
        Director*director=Director::getInstance();
        if (touches.size()>=2) {
            auto point1=director->convertToGL(touches.at(0)->getLocation());
            auto point2=director->convertToGL(touches.at(1)->getLocation());
            _distance=point1.getDistance(point2);
        }
    };
    listener->onTouchesMoved=[&](const std::vector<Touch*>&touches,Event *pevent)
    {
        
        Director*director=Director::getInstance();
        if (touches.size()>=2) {
            auto point1=director->convertToGL(touches.at(0)->getLocation());
            auto point2=director->convertToGL(touches.at(1)->getLocation());
            
            float new_distance=point1.getDistance(point2);
            float delta=new_distance-_distance;
            pCamera->setPosition3D(pCamera->getPosition3D()+Vec3(0,delta,delta));
            _distance=new_distance;
            
                   }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    return true;
}