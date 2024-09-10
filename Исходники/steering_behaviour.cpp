       Ogre::Vector3 evade(const Vehicle& agent,const Vehicle& target)
       {
         // a parameter
         const float maxPredictionTime = 2 ;
         
         Ogre::Vector3 offset = target.getPosition()-agent.getPosition() ;
         const float distance = offset.length() ;
         
         // may be equal to zero when target has reached agent 
         const float roughTime = distance / target.getSpeed().length() ;
 
         const float predictionTime = ((roughTime > maxPredictionTime) ?
                                       maxPredictionTime :
                                       roughTime);
     
         const Ogre::Vector3 menace_position = target.predictFuturePosition(predictionTime) ;
         
         Ogre::Vector3 desiredVelocity = agent.getPosition() - menace_position ;
         const float desiredSpeed =  desiredVelocity.normalise() ;
 
         if (desiredSpeed == 0)
         {
           desiredVelocity = agent.getForward() ;
           desiredVelocity.normalise() ;
         }
         
         // we should evade with maximum speed 
         desiredVelocity = desiredVelocity*agent.getMaxSpeed() ;
         agent.normalizeSpeed(desiredVelocity) ;
 
         return desiredVelocity-agent.getSpeed() ;
       }