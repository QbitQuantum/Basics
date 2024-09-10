  void CreatureMotionSys::UpdatePursuit(const PursuitObjTarget& target, TimeStep dt)
  {
    const MotionTaskState targetState = CheckPursuitPredState(target);
    if(targetState == MotionTaskState::SEEKING)
    {
      PursuitObjSeekingVRes pursuitResult;
      PursuitObjMethodV::Seek(m_Creature, target, PursuitObjSettingsV(), pursuitResult);
      SeekTargetVel(pursuitResult.velocity, dt);
    }
    else
    {
      const Vector2F currentPosition = m_Creature.GetPosition();
      const Vector2F targetPosition = target.target->GetPosition();
      const AnglePi targetAngle = (targetPosition - currentPosition).GetAngle();
      const Float targetSpeed = target.target->GetTotalLinVelocity().Length();
      if(targetSpeed == 0.0f)
      {
        const Vector2F targetLinVelocity = Vector2F(targetSpeed, 0.0f).Rotate(targetAngle);
        SeekTargetVel(targetLinVelocity, dt);
      }
      else
      {
        UpdateAngleSeeking(SeekAngleTarget(targetAngle), dt);
      }
    }

    UpdateMotionTargetState(targetState);
  }