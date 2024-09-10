void ILiquidBody::updateLiquidBody()
{
    if(EnableGlobalWave)
    {
        if(Device->getTimer()->getTime() >= (LastGlobalWaveUpdateTime+GlobalWaveUpdateFrequency))
        {
            if(LiquidRising)
            {
                if(LiquidExtents.MaxEdge.Y <= (LiquidLevel+MaxGlobalWaveHeight))
                    LiquidExtents.MaxEdge.Y += GlobalWaveChangeIncrement;

                else
                    LiquidRising = false;
            }

            else if(!LiquidRising)
            {
                if(LiquidExtents.MaxEdge.Y >= (LiquidLevel+MinGlobalWaveHeight))
                    LiquidExtents.MaxEdge.Y += -GlobalWaveChangeIncrement;

                else
                    LiquidRising = true;
            }

            LastGlobalWaveUpdateTime = Device->getTimer()->getTime();
        }
    }

    if(DebugDraw)
    {
        Device->getVideoDriver()->setMaterial(DynamicsWorld->getDebugMaterial());
        Device->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());

        Device->getVideoDriver()->draw3DBox(LiquidExtents, irr::video::SColor(255, 0, 0, 100));
    }

    for(u32 i=0; i < DynamicsWorld->getNumCollisionObjects(); i++)
    {
        ICollisionObject* obj = DynamicsWorld->getCollisionObjectByIndex(i);

        if(obj->isLiquidSimulationEnabled())
        {
            if(obj->getObjectType() == ECOT_RIGID_BODY)
            {
                if((!Infinite && LiquidExtents.intersectsWithBox(static_cast<IRigidBody*>(obj)->getLiquidBox()))
                    ||
                    (Infinite && (static_cast<IRigidBody*>(obj)->getLiquidBox().MinEdge.Y<LiquidExtents.MaxEdge.Y
                    && (InfiniteDepth ? InfiniteDepth:(static_cast<IRigidBody*>(obj)->getLiquidBox().MaxEdge.Y>LiquidExtents.MinEdge.Y)))))
                    affectRigidBody(static_cast<IRigidBody*>(obj));
            }
        }
    }
}