void Animation::Set( F32 frame, const AnimKey &lastKey, const AnimKey &thisKey, AnimKey &state)
{
  // determine the current fraction to this cycle
  F32 dk = thisKey.frame - lastKey.frame;
  ASSERT( dk > 0);
  F32 dfdk  = (frame - lastKey.frame) / dk;

//  state.type = 0;

  if (lastKey.type & animSCALE)
  {
    // do a parametric interpolation of the quaternion using dfdk
    Quaternion q = (thisKey.quaternion - lastKey.quaternion) * dfdk + lastKey.quaternion;
    
    // do a parametric interpolation of the quaternion using dfdk
    if (q.Dot( q) <= 0)
    {
      LOG_WARN( ("Quat::Set q.Dot(q) <= 0: %f %f %f %f", q.s, q.v.x, q.v.y, q.v.z) );
      LOG_WARN( ("lastKey.quat: %f %f %f %f", lastKey.quaternion.s, lastKey.quaternion.v.x, lastKey.quaternion.v.y, lastKey.quaternion.v.z) );
      LOG_WARN( ("thisKey.quat: %f %f %f %f", thisKey.quaternion.s, thisKey.quaternion.v.x, thisKey.quaternion.v.y, thisKey.quaternion.v.z) );
      LOG_WARN( ("dfdk: %f; lastKey.frame %f; thisKey.frame %f; frame %f", dfdk, lastKey.frame, thisKey.frame, frame) );

      statQuatError = TRUE;

      state.Set(thisKey.quaternion);
    }
    else
    {
      // set the matrix
      state.Set( q);
    }
    // do a parametric interpolation of the scale using dfdk
    Vector v = (thisKey.scale - lastKey.scale) * dfdk + lastKey.scale;
    // set the matrix
    state.SetScale( v);

//    state.type |= animSCALE;
  }
  else if (lastKey.type & animQUATERNION)
  {
    Quaternion q = (thisKey.quaternion - lastKey.quaternion) * dfdk + lastKey.quaternion;

    // do a parametric interpolation of the quaternion using dfdk
    if (q.Dot( q) <= 0)
    {
      LOG_WARN( ("Quat::Set q.Dot(q) <= 0: %f %f %f %f", q.s, q.v.x, q.v.y, q.v.z) );
      LOG_WARN( ("lastKey.quat: %f %f %f %f", lastKey.quaternion.s, lastKey.quaternion.v.x, lastKey.quaternion.v.y, lastKey.quaternion.v.z) );
      LOG_WARN( ("thisKey.quat: %f %f %f %f", thisKey.quaternion.s, thisKey.quaternion.v.x, thisKey.quaternion.v.y, thisKey.quaternion.v.z) );
      LOG_WARN( ("dfdk: %f; lastKey.frame %f; thisKey.frame %f; frame %f", dfdk, lastKey.frame, thisKey.frame, frame) );

      statQuatError = TRUE;

      state.Set(thisKey.quaternion);
    }
    else
    {
      // set the matrix
      state.Set( q);
    }
//    state.type |= animQUATERNION;
  }

  if (lastKey.type & animPOSITION)
  {
    // do a parametric interpolation of the pos using dfdk
    Vector v = (thisKey.position - lastKey.position) * dfdk + lastKey.position;
    // set the matrix
    state.Set( v);

//    state.type |= animPOSITION;
  }
}