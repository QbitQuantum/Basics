      void AgentVehicle::onInit()
      {
        InternalMessage("AI","entering AgentVehicle::onInit") ;
        Ogre::Vector3 speed = getSpeed() ;

        m_vehicle.reset(new Vehicle(getPosition(),
                                    getOrientation(),
                                    speed,
                                    speed.length(),
                                    getSize())) ;
        getViewPoint()->setVehicle(m_vehicle.get()) ;
        InternalMessage("AI","leaving AgentVehicle::onInit") ;
      }