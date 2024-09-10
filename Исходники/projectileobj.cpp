//
// ProjectileObjType::MissilePhysics
//
// Simulate a missile, which includes acceleration, turning etc
//
void ProjectileObjType::MissilePhysics(ProjectileObj &obj, Matrix &m, Vector &s)
{
  // Has the odometer clocked ?
  if ((obj.distTravelled * obj.distTravelled) > obj.weaponType->GetMaxRange2())
  {
    GameObjCtrl::MarkForDeletion(&obj);
  }

  F32 speed = obj.GetSpeed();
  F32 fMag = 20.0f;

  // Homing in on target
  if (missile.homingRate > 1e-3F)
  {
    const Target &t = obj.GetTarget();

    if (t.Alive() /* && (t.GetType() == Target::OBJECT)*/)
    {
      Vector f = t.GetLocation() - m.posit;
      fMag = f.Magnitude();

      if (fMag > 0.1F)
      {
        // Close enough to do some rotation
        f *= (1.0F / fMag);
        F32 fdot = f.Dot(m.front);

        if (fdot > missile.cosHomingRate)
        {
          // Within the max turning rate, turn directly there
          m.SetFromFront(f);
        }
        else
        {
          // Axis to rotate around
          Vector u = (f * -1.0F).Cross(m.front);
          u.Normalize();
          Vector r = u.Cross(f);

          // Turn left or right?
          F32 rdot = r.Dot(m.front);

          // Rotate at maximum allowable rate
          F32 angle = Utils::FSign(rdot) * missile.homingRate * GameTime::INTERVAL;
          
          if (fdot < 0.0F)
          {
            if (obj.wasBehind)
            {
              // Keep turning in the last direction
              angle = Utils::FSign(obj.lastAngle) * missile.homingRate * GameTime::INTERVAL;
            }
            else
            {
              // Setup the prev angle, and keep it that way
              obj.lastAngle = angle;
              obj.wasBehind = TRUE;
            }
          }
          else
          {
            // Target not behind us any more
            obj.wasBehind = FALSE;
          }

          // Do the rotation
          Matrix newm(Quaternion(angle, u));
          newm.Rotate(m.front, m.front);
          m.SetFromFront(m.front);
        }
      }
    }
  }

  // Waver the trajectory
  if (missile.waverTurn != 0.0F)
  {
    F32 waverTurn = missile.waverTurn;

    F32 fMag2 = fMag * fMag;

    // If we're in the last 20m then reduce the waver turn
    if (fMag < 20.0f)
    {
      waverTurn *= fMag2 * 0.0025f;
    }

    // apply the waver pitch
    F32 pitchAng = waverTurn * GameTime::INTERVAL * 
      (F32)sin(obj.waverPitch * missile.waverRate * GameTime::INTERVAL);
    Matrix pitchMat(Quaternion(pitchAng, m.right));
    pitchMat.Rotate(m.front, m.front);
    obj.waverPitch += Random::sync.Float() + Random::sync.Float();

    // apply the waver yaw
    F32 yawAng = waverTurn * GameTime::INTERVAL * 
      (F32)sin(obj.waverYaw * missile.waverRate * GameTime::INTERVAL);
    Matrix yawMat(Quaternion(yawAng, m.up));
    yawMat.Rotate(m.front, m.front);
    obj.waverYaw += Random::sync.Float() + Random::sync.Float();

    // update the transform matrix
    m.SetFromFront(m.front);
  }

  // Acceleration
  speed = Min<F32>(missile.topSpeed, speed + missile.acceleration * GameTime::INTERVAL);

  // Velocity
  Vector veloc = m.front * speed;
  
  // Displacement
  s = veloc * GameTime::INTERVAL;

  // Update speed and velocity
  obj.SetSpeed(speed);
  obj.SetVelocity(veloc);
}