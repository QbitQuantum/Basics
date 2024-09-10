void CanopySimulator::CordSimulator::update(float dt)
{
    Vector3f riserPos = _riserJoint->getPos();
    Vector3f innerPos = _innerJoint->getPos();
    Vector3f outerPos = _outerJoint->getPos();

    // now calculate cascade position
    Vector3f cascadePos = innerPos + ( outerPos - innerPos ) * 0.5f ;
    Vector3f riserToCascade = cascadePos - riserPos;
    Vector3f riserToCascadeN = riserToCascade;
    riserToCascadeN.normalize();
    if( riserToCascade.length() < _cascade )
    {
        riserToCascadeN = riserToCascade;
    }
    else
    {
        riserToCascadeN *= _cascade;
    }
    cascadePos = riserPos + riserToCascadeN;

    // place cords
    Matrix4f matrix;
    unsigned int instanceId = _firstInstaceId;
    Jumper::placeCord( matrix, riserPos, cascadePos );
    _cordBatch->setMatrix( instanceId, matrix );
    instanceId++;
    Jumper::placeCord( matrix, cascadePos, innerPos );
    _cordBatch->setMatrix( instanceId, matrix );
    instanceId++;
    Jumper::placeCord( matrix, cascadePos, outerPos );
    _cordBatch->setMatrix( instanceId, matrix );
}