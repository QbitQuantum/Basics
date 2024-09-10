void AvatarGameObj::step_impl() {
  dBodyID body = get_entity().get_id();
  
  const Channel* chn;
  
  chn = &Input::get_axis_ch(ORSave::AxisBoundAction::TranslateX);
  if (chn->is_on()) {
    float v = (chn->get_value())*(MAX_STRAFE/MAX_FPS);
    dBodyAddRelForce(body, -v, 0.0, 0.0);
  }
  
  bool pushing_up = false;
  chn = &Input::get_axis_ch(ORSave::AxisBoundAction::TranslateY);
  if (chn->is_on()) {
    float v = (chn->get_value())*(MAX_STRAFE/MAX_FPS);
    if (Saving::get().config().invertTranslateY()) {
      v = -v;
    }
    dBodyAddRelForce(body, 0.0, -v, 0.0);
    if (v < 0) {
      pushing_up = true;
    }
  }
  
  chn = &Input::get_axis_ch(ORSave::AxisBoundAction::TranslateZ);
  if (chn->is_on()) {
    float v = (chn->get_value())*(MAX_ACCEL/MAX_FPS);
    dBodyAddRelForce(body, 0.0, 0.0, -v);
  }
  
  const dReal* avel = dBodyGetAngularVel(body);
  dVector3 rel_avel;
  dBodyVectorFromWorld(body, avel[0], avel[1], avel[2], rel_avel);
  
  // X-turn and x-counterturn
  chn = &Input::get_axis_ch(ORSave::AxisBoundAction::RotateY);
  if (chn->is_on()) {
    float v = -(chn->get_value())*(MAX_TURN/MAX_FPS);
    dBodyAddRelTorque(body, 0.0, v, 0.0);
  } else {
    float cv = rel_avel[1]*-CTURN_COEF/MAX_FPS;
    dBodyAddRelTorque(body, 0.0, cv, 0.0);
  }
  
  // Y-turn and y-counterturn
  chn = &Input::get_axis_ch(ORSave::AxisBoundAction::RotateX);
  if (chn->is_on()) {
    float v = (chn->get_value())*(MAX_TURN/MAX_FPS);
    if (Saving::get().config().invertRotateY()) {
      v = -v;
    }
    dBodyAddRelTorque(body, v, 0.0, 0.0);
  } else {
    float cv = rel_avel[0]*-CTURN_COEF/MAX_FPS;
    dBodyAddRelTorque(body, cv, 0.0, 0.0);
  }
  
  // Roll and counter-roll
  chn = &Input::get_axis_ch(ORSave::AxisBoundAction::RotateZ);
  if (chn->is_on()) {
    float v = (chn->get_value())*(MAX_ROLL/MAX_FPS);
    dBodyAddRelTorque(body, 0.0, 0.0, v);
  } else {
    float cv = rel_avel[2]*(-CROLL_COEF/MAX_FPS);
    dBodyAddRelTorque(body, 0.0, 0.0, cv);
  }
  
  // Changing stance between superman-style and upright
  if (_attached) {
    _uprightness += UPRIGHTNESS_STEP_DIFF;
  } else {
    _uprightness -= UPRIGHTNESS_STEP_DIFF;
  }
  if (_uprightness > 1.0) { _uprightness = 1.0; } else if (_uprightness < 0.0) { _uprightness = 0.0; }
  
  update_geom_offsets();
  
  _attached = _attached_this_frame;
  
  // If we are attached, work to keep ourselves ideally oriented to the attachment surface
  if (_attached) {
    Vector sn_rel = vector_from_world(_sn);
    Vector lvel = Vector(dBodyGetLinearVel(body));
    Vector lvel_rel = vector_from_world(lvel);
    Vector avel = Vector(dBodyGetAngularVel(body));
    Vector avel_rel = vector_from_world(avel);
    
    // Apply as much of each delta as we can
    
    // X and Z orientation delta
    // TODO Maybe should translate body so that the contact point stays in the same spot through rotation
    float a = limit_abs(_zrot_delta, RUNNING_ADJ_RATE_Z_ROT/MAX_FPS);
    Vector body_x(vector_to_world(Vector(cos(a), sin(a), 0)));
    a = limit_abs(-_xrot_delta, RUNNING_ADJ_RATE_X_ROT/MAX_FPS);
    Vector body_y(vector_to_world(Vector(0, cos(a), sin(a))));
    dMatrix3 matr;
    dRFrom2Axes(matr, body_x.x, body_x.y, body_x.z, body_y.x, body_y.y, body_y.z);
    dBodySetRotation(body, matr);
    
    // Y position delta
    // If the user is pushing up, set the target point high above the ground so we escape sticky attachment
    set_pos(get_pos() + _sn*limit_abs(_ypos_delta + (pushing_up ? RUNNING_MAX_DELTA_Y_POS*2 : 0), RUNNING_ADJ_RATE_Y_POS/MAX_FPS));
    
    // Y linear velocity delta
    lvel_rel.y += limit_abs(_ylvel_delta, RUNNING_ADJ_RATE_Y_LVEL/MAX_FPS);
    lvel = vector_to_world(lvel_rel);
    dBodySetLinearVel(body, lvel.x, lvel.y, lvel.z);
    
    // X and Z angular velocity delta
    avel_rel.x += limit_abs(_xavel_delta, RUNNING_ADJ_RATE_X_AVEL/MAX_FPS);
    avel_rel.z += limit_abs(_zavel_delta, RUNNING_ADJ_RATE_Z_AVEL/MAX_FPS);
    avel = vector_to_world(avel_rel);
    dBodySetAngularVel(body, avel.x, avel.y, avel.z);
  }
  
  if (_attached_this_frame) {
    _attached_this_frame = false;
    dGeomEnable(get_entity().get_geom("sticky_attach"));
  } else {
    dGeomDisable(get_entity().get_geom("sticky_attach"));
  }
}