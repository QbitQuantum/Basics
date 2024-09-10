void CCutScene::clipPoly(PhysicsShapePolygon* shape, Point normal, float distance)
{
    PhysicsBody* body = shape->getBody();
    int count = shape->getPointsCount();
    int pointsCount = 0;
    Point* points = new Point[count + 1];
    
    Vector2dVector vcPoints;
    vcPoints.clear();
    Vector2d v2Point(0, 0);
    
    for (int i=0, j=count-1; i<count; j=i, ++i)
    {
        Point a = body->local2World(shape->getPoint(j));
        float aDist = a.dot(normal) - distance;
        
        if (aDist < 0.0f)
        {
            points[pointsCount] = a;
            ++pointsCount;
        }
        
        Point b = body->local2World(shape->getPoint(i));
        float bDist = b.dot(normal) - distance;
        
        if (aDist*bDist < 0.0f)
        {
            float t = std::fabs(aDist)/(std::fabs(aDist) + std::fabs(bDist));
            Vec2 v2Tmp = a.lerp(b, t);
            points[pointsCount] = v2Tmp;
            ++pointsCount;
        }
    }
    
    Point center = PhysicsShape::getPolyonCenter(points, pointsCount);
    
    for (int i = 0; i < pointsCount; i++)
    {
        points[i] = body->world2Local(points[i]);
        vcPoints.push_back(Vector2d(points[i].x, points[i].y));
    }
    
    PhysicsBody* polyon = PhysicsBody::createPolygon(points, pointsCount);
    
    CFoodCut* pNode = (CFoodCut*)(body->getNode());
    std::vector<int> vMaterials;
    vMaterials.clear();
    vMaterials = pNode->getMaterials();
    MATERIAL_ID eId = MI_MAX;
    if (vMaterials.size() != 0)
    {
        eId = (MATERIAL_ID)vMaterials[0];
    }
    
    CFoodCut *filledPolygon = CFoodCut::create(eId, vcPoints, pNode->getPanziIndex(), pNode->getTouchedIndex());
    filledPolygon->setPhysicsBody(polyon);
    int nTmp = rand() % 50 + 50;
    int nTmpRotate = rand() % 30 - 60;
    filledPolygon->setPosition(body->getPosition());
    //filledPolygon->setRotation(filledPolygon->getRotation() + nTmpRotate);
    filledPolygon->getPhysicsBody()->setTag(_sliceTag);
    filledPolygon->getPhysicsBody()->setGravityEnable(false);
    
    
    polyon->setVelocity(body->getVelocityAtWorldPoint(center));
    //polyon->setAngularVelocity(body->getAngularVelocity());
    polyon->setTag(_sliceTag);
    
    float fMass = polyon->getMass();
    float fV = 80;
    float fImpulse = fMass * fV;
    float fTmpX = (float)(Random() % 30) / 100.0f - 0.15f;
    float fTmpY = (float)(rand() % 30) / 100.0f - 0.15f;
    polyon->applyImpulse((normal + Vec2(fTmpX, fTmpY)) * -fImpulse);
    polyon->setLinearDamping(0.8f);
    addChild(filledPolygon, 80);
    filledPolygon->setBirthTime(getCurTime());
    m_vCutFoods.push_back(filledPolygon);
    m_nSliceCount ++;
    delete[] points;
}