void BulletRigidBody::setWorldTransform(const btTransform &centerOfMassWorldTrans) {
    Transform* trans = owner_object()->transform();
    btTransform aux; getWorldTransform(aux);

    if(std::abs(aux.getOrigin().getX() - prevPos.getOrigin().getX()) >= 0.1f ||
       std::abs(aux.getOrigin().getY() - prevPos.getOrigin().getY()) >= 0.1f ||
       std::abs(aux.getOrigin().getZ() - prevPos.getOrigin().getZ()) >= 0.1f)
    {
        mRigidBody->setWorldTransform(aux);
        prevPos = aux;
        //TODO: incomplete solution
    }
    else
    {
        btTransform physicBody = (centerOfMassWorldTrans  * m_centerOfMassOffset);
        convertBtTransform2Transform(physicBody, trans);
        prevPos = physicBody;
    }
    //convertBtTransform2Transform(centerOfMassWorldTrans * m_centerOfMassOffset, trans);
}