void KrecikApp::createCar()
{
    Vector2f ltPos(320.0f, B2toSF(l.getB2Vertexes()[3].y) - 250.0f); // pozycja left-top autka

    // koła
    float whRad = 10.0f;
    float whFr = cc.wheelFriction;
    b2CircleShape wh;
    wh.m_radius = SFtoB2(whRad);

    wh.m_p = SFtoB2(ltPos + Vector2f(20.0f, 60.0f));
    Body* lwheel = this->addDynamicBody("left wheel", wh, &whTex);
    lwheel->b->GetFixtureList()->SetFriction(whFr);

    wh.m_p = SFtoB2(ltPos + Vector2f(90.0f, 60.0f));
    Body* rwheel = this->addDynamicBody("right wheel", wh, &whTex);
    rwheel->b->GetFixtureList()->SetFriction(whFr);

    // karoseria
    b2PolygonShape sh1; // budka kierownicza
    b2PolygonShape sh2; // reszta autka
    const unsigned vxNum = 4;
    b2Vec2 vx[vxNum];
    vx[0] = SFtoB2(ltPos + Vector2f(80.0f, 20.0f));
    vx[1] = SFtoB2(ltPos + Vector2f(60.0f, 0.0f));
    vx[2] = SFtoB2(ltPos + Vector2f(30.0f, 0.0f));
    vx[3] = SFtoB2(ltPos + Vector2f(30.0f, 20.0f));
    sh1.Set(vx, vxNum);
    vx[0] = SFtoB2(ltPos + Vector2f(0.0f, 20.0f));
    vx[1] = SFtoB2(ltPos + Vector2f(0.0f, 40.0f));
    vx[2] = SFtoB2(ltPos + Vector2f(100.0f, 40.0f));
    vx[3] = SFtoB2(ltPos + Vector2f(100.0f, 20.0f));
    sh2.Set(vx, vxNum);
    Body* car = this->addDynamicBody("car", sh1, &bodyTex, false);
    car->addFixture(sh2, 1.0f, &chassTex, Vector2f(50.0f, 30.0f));

    // amortyzatory
    b2WheelJointDef spr;
    spr.collideConnected = false;
    spr.enableMotor = true;
    spr.motorSpeed = 0.0f;
    spr.dampingRatio = cc.springDamp;
    spr.frequencyHz = cc.springHz;
    spr.maxMotorTorque = 1000.0f;

    spr.Initialize(car->b, lwheel->b, SFtoB2(ltPos + Vector2f(20.0f, 60.0f)), b2Vec2(0.0f, 0.4f));
    this->world.CreateJoint(&spr);

    spr.Initialize(car->b, rwheel->b, SFtoB2(ltPos + Vector2f(90.0f, 60.0f)), b2Vec2(0.0f, 0.4f));
    this->world.CreateJoint(&spr);
}