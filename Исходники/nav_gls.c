bool_t gls_run(uint8_t _af,uint8_t _sd, uint8_t _tod, uint8_t _td) {


  // set target speed for approach on final
  if (init){
#if USE_AIRSPEED
    v_ctl_auto_airspeed_setpoint = target_speed;
#endif
    init = FALSE;
  }

  // calculate distance tod_td
  float final_x = WaypointX(_td) - WaypointX(_tod);
  float final_y = WaypointY(_td) - WaypointY(_tod);
  float final2 = Max(final_x * final_x + final_y * final_y, 1.);

  struct EnuCoor_f* pos_enu = stateGetPositionEnu_f();
  float hspeed = *stateGetHorizontalSpeedNorm_f();

  float nav_final_progress = ((pos_enu->x - WaypointX(_tod)) * final_x +
                              (pos_enu->y - WaypointY(_tod)) * final_y) / final2;
  Bound(nav_final_progress,-1,1);
  //  float nav_final_length = sqrt(final2);

  // calculate requiered decent rate on glideslope
  float pre_climb_glideslope = hspeed * (-tanf(app_angle));

  // calculate glideslope
  float start_alt = WaypointAlt(_tod);
  float diff_alt = WaypointAlt(_td) - start_alt;
  float alt_glideslope = start_alt + nav_final_progress * diff_alt;

  // calculate intercept
  float nav_intercept_progress = ((pos_enu->x - WaypointX(_sd)) * 2*sd_tod_x +
                                  (pos_enu->y - WaypointY(_sd)) * 2*sd_tod_y) /
                                 Max((sd_intercept*sd_intercept),1.);
  Bound(nav_intercept_progress,-1,1);
  float tmp = nav_intercept_progress * sd_intercept / gs_on_final;
  float alt_intercept = WaypointAlt(_tod) - (0.5 * app_intercept_rate * tmp * tmp);
  float pre_climb_intercept = -nav_intercept_progress * hspeed * (tanf(app_angle));

  //########################################################

  // handle the different vertical approach segments

  float pre_climb = 0.;
  float alt = 0.;

  // distance
  float f_af = sqrt((pos_enu->x - WaypointX(_af))*(pos_enu->x - WaypointX(_af))+
                    (pos_enu->y - WaypointY(_af))*(pos_enu->y - WaypointY(_af)));

  if(f_af<app_distance_af_sd){ // approach fix (AF) to start descent (SD)
    alt = WaypointAlt(_af);
    pre_climb = 0.;
  }
  else if((f_af>app_distance_af_sd) && (f_af<(app_distance_af_sd+sd_intercept))){
    // start descent (SD) to intercept
    alt = alt_intercept;
    pre_climb = pre_climb_intercept;
  }
  else{ //glideslope (intercept to touch down)
    alt = alt_glideslope;
    pre_climb = pre_climb_glideslope;
  }
  // Bound(pre_climb, -5, 0.);


  //######################### autopilot modes

  NavVerticalAltitudeMode(alt, pre_climb);	// vertical   mode (folow glideslope)
  NavVerticalAutoThrottleMode(0);		// throttle   mode
  NavSegment(_af, _td);			// horizontal mode (stay on localiser)

  return TRUE;
}	// end of gls()