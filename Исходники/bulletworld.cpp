void irrBulletWorld::updateCollisionObjects()
{
    list<ICollisionObject*>::Iterator cbit = collisionObjects.begin();

    for(; cbit != collisionObjects.end(); cbit++)
    {
        ICollisionObject* obj = (*cbit);

        if(obj->getObjectType() == ECOT_SOFT_BODY)
        {
            static_cast<ISoftBody*>(obj)->updateSoftBody();
        }

        if(obj)
        {
            for(u32 j=0; j < obj->getNumAffectors(); j++)
            {
                ICollisionObjectAffector* affector = obj->getAffector(j);
                if(affector->hasFinished() == false)
                {
                    affector->affectObject(obj, device->getTimer()->getTime());
                }
            }
        }
    }

    list<ICollisionObject*>::Iterator dlit = deletionList.begin();

    for(; dlit != deletionList.end(); )
    {
        this->removeCollisionObject((*dlit));
        dlit = deletionList.erase(dlit);
    }
}