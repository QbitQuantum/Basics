void HelloWorld::update(float delta)
{
    Mat4 transform = Director::getInstance()->getHeadTransform();
    Quaternion q;
    transform.getRotation(&q);
    q.inverse();
    //CCLOG("head rotation is %lf, %lf, %lf, %lf", q.x, q.y,q.z,q.w);
    _headNode->setRotationQuat(q);
    //add moving logic
    if(_isMoving)
    {
        Mat4 headTM;
        Mat4::createRotation(q, &headTM);
        Vec3 toward;
        headTM.transformVector(0, 0, -1, 0, &toward);
        toward.y = 0;
        toward.normalize();
        const float MOVE_SPEED = 2.0;
        Vec3 pos = _headNode->getPosition3D();
        pos += toward * MOVE_SPEED;
        _headNode->setPosition3D(pos);
        
    }
}