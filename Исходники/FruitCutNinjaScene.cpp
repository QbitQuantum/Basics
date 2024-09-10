void FruitCutNinjaScene::clipPoly(PhysicsShapePolygon* shape, Point normal, float distance)
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
    
    PRFilledPolygon* pNode = (PRFilledPolygon*)(body->getNode());
    std::string sName = pNode->getTextureName();
    //auto texture = Director::getInstance()->getTextureCache()->addImage("pineapple.png");
    PRFilledPolygon *filledPolygon = PRFilledPolygon::filledPolygonWithPointsAndTexture(vcPoints, sName.c_str());
    filledPolygon->setPhysicsBody(polyon);
    filledPolygon->setPosition(body->getPosition() + normal * -40);
    filledPolygon->getPhysicsBody()->setTag(_sliceTag);
    filledPolygon->getPhysicsBody()->setGravityEnable(false);
    
    polyon->setVelocity(body->getVelocityAtWorldPoint(center));
    polyon->setAngularVelocity(body->getAngularVelocity());
    polyon->setTag(_sliceTag);
    //polyon->applyImpulse(normal * -100);
    addChild(filledPolygon, 80);
    
    /*
    CPolygonSprite* pSprite = CPolygonSprite::create();
    pSprite->initWithFile("pineapple.png", polyon, false);
    pSprite->setPosition(body->getPosition());
    polyon->setTag(_sliceTag);
    addChild(pSprite);
    */
    
    /*
    Node* node = Node::create();
    PhysicsBody* polyon = PhysicsBody::createPolygon(points, pointsCount, PHYSICSBODY_MATERIAL_DEFAULT, -center);
    node->setPosition(center);
    node->setPhysicsBody(polyon);
    polyon->setVelocity(body->getVelocityAtWorldPoint(center));
    polyon->setAngularVelocity(body->getAngularVelocity());
    polyon->setTag(_sliceTag);
    addChild(node);
    */
    delete[] points;
}