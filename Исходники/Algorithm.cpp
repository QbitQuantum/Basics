      /*
        distance(target_positon+t*target_speed) = t*interceptor_speed
        formal solver gives :
          
        delta = 
            (-target_positon.y^2-target_positon.x^2)*target_speed.z^2
            +(2*target_positon.y*target_positon.z*target_speed.y+2*target_positon.x*target_positon.z*target_speed.x)*target_speed.z
            +(-target_positon.z^2-target_positon.x^2)*target_speed.y^2
            +2*target_positon.x*target_positon.y*target_speed.x*target_speed.y
            +(-target_positon.z^2-target_positon.y^2)*target_speed.x^2
            +interceptor_speed^2*target_positon.z^2
            +interceptor_speed^2*target_positon.y^2
            +interceptor_speed^2*target_positon.x^2
        
        if delta > 0
        t = (sqrt(delta)
              -target_positon.z*target_speed.z-target_positon.y*target_speed.y-target_positon.x*target_speed.x)
            /(target_speed.z^2+target_speed.y^2+target_speed.x^2-laser_speed^2)
        
        special case for delta=0 when equation becomes linear
      */
      std::pair<bool,float> calculateInterceptionTime(
          const Ogre::Vector3& target_position,
          const Ogre::Vector3& target_speed,
          const float& interceptor_speed)
      {
        
        // result ;
        float time = 0 ;
        
        if (target_speed.length() != 0)
        {
          
          float delta = 
                  (-pow(target_position.y,2)-pow(target_position.x,2))*pow(target_speed.z,2)
                  +(2*target_position.y*target_position.z*target_speed.y+2*target_position.x*target_position.z*target_speed.x)*target_speed.z
                  +(-pow(target_position.z,2)-pow(target_position.x,2))*pow(target_speed.y,2)
                  +2*target_position.x*target_position.y*target_speed.x*target_speed.y
                  +(-pow(target_position.z,2)-pow(target_position.y,2))*pow(target_speed.x,2)
                  +pow(interceptor_speed,2)*pow(target_position.z,2)
                  +pow(interceptor_speed,2)*pow(target_position.y,2)
                  +pow(interceptor_speed,2)*pow(target_position.x,2) ;

          float divisor = target_speed.squaredLength()-pow(interceptor_speed,2) ;
          
          if (delta > 0 && fabs(divisor) > 1e-10)
          {
            float b = -target_position.z*target_speed.z-target_position.y*target_speed.y-target_position.x*target_speed.x ;
            time = (sqrt(delta)+b)/divisor ;
            if (time < 0)
              time = (-sqrt(delta)+b)/divisor ;
          }
          else
          {
            /// no real solution : target is unreachable by interceptor
            return std::pair<bool,float>(false,0) ;
          }
        }
        else
        {
          time = target_position.length()/interceptor_speed ;
        }
        
        return std::pair<bool,float>(true,time) ;
      }