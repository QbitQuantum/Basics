  con_vec drive(situation &s) 
  { 
    con_vec result = CON_VEC_EMPTY;    // This is what is returned. 
    double alpha, vc;                  // components of result 
    static double lane = -10000;       // an absurd value to show not initialized 
    double bias, speed, width; 

    if( s.starting )
    {
      result.fuel_amount = MAX_FUEL;     // fuel when starting
    }

    // service routine in the host software to handle getting unstuck from 
    // from crashes and pileups: 
    if(stuck(s.backward, s.v,s.vn, s.to_lft,s.to_rgt, &result.alpha,&result.vc)) 
      return result; 

    width = s.to_lft + s.to_rgt;       // compute width of track 

    // This is a little trick so that the car will not try to change lanes 
    // during the "dragout" at the start of the race.  We set "lane" to 
    // whatever position we have been placed by the host. 
    if(lane < -9000)                   // will be true only once 
      lane = s.to_lft;                 // better not to change lanes at the start 

    // Set "lane" during curves.  This robot sets "lane" during curves to 
    // try to maintain a fixed distance to the inner rail. 
    // For straightaways, we leave "lane" unchanged until later. 
    if(s.cur_rad > 0.0)                // turning left 
      lane = DIST_FROM_INSIDE; 
    else if(s.cur_rad < 0.0)           // turning right 
      lane = width - DIST_FROM_INSIDE; 

    // set the bias: 
    // Bias is an additive term in the steering servo, so that the servo 
    // doesn't have to "hunt" much for the correct alpha value.  It is an 
    // estimate of the alpha value that would be found by the servo if there 
    // was plenty of settling time.  It is zero for straightaways. 
    // Also, for convenience, we call the corn_spd() function here.  On 
    // the straightaway, we call it to find out the correct speed for the 
    // corner ahead, using s.nex_rad for the radius.  In the curve we of 
    // course use the radius of the curve we are in. 
    if(s.cur_rad == 0.0) 
    { 
      bias = 0.0; 
      speed = corn_spd(s.nex_rad + DIST_FROM_INSIDE); 
    } 
    else  
    { 
      speed = corn_spd(s.cur_rad + DIST_FROM_INSIDE); 
      // See initial paragraphs for discussion of this formula. 
      bias = (s.v*s.v/(speed*speed)) * atan(BIG_SLIP / speed); 
      if(s.cur_rad < 0.0)   // bias must be negative for right turn 
        bias = -bias; 
    } 

    // set alpha:  (This line is the complete steering servo.) 
    alpha = STEER_GAIN * (s.to_lft - lane)/width - DAMP_GAIN * s.vn/s.v + bias; 

    // set vc:  When nearing end of straight, change "lane" for the turn, also. 
    if(s.cur_rad == 0.0)              // If we are on a straightaway, 
    {
      if(s.to_end > ACCEL_FRACTION * s.cur_len)  // if we are far from the end, 
      {
        vc = s.v + 50.0;                           // pedal to the metal! 
      }
      else                      // otherwise, adjust speed for the coming turn: 
      {
        if(s.v > 1.02 * speed)         // if we're 2% too fast, 
          vc = .95 * s.v;              // brake hard. 
        else if(s.v < .98 * speed)     // if we're 2% too slow, 
          vc = 1.05 * speed;           // accelerate hard. 
        else                           // if we are very close to speed, 
          vc = .5 * (s.v + speed);     // approach the speed gently. 
        // approach the lane you want for the turn: 
        if(s.nex_rad > 0.0) 
          lane = DIST_FROM_INSIDE; 
        else 
          lane = width - DIST_FROM_INSIDE; 
      } 
    } 
    else       // This is when we are in a curve:  (seek correct speed) 
    {
      vc = .5 * (s.v + speed)/cos(alpha);   // to maintain speed in corner 
    } 

    // During the acceleration portion of a straightaway, the lane variable 
    // is not changed by the code above.  Hence the code below changes it a 
    // little at a time until there is no car dead_ahead.  This code here has 
    // no affect at all in the turns, nor in the braking portion 
    // of the straight. 
    if(s.dead_ahead)                   // Change the lane a little if someone's 
      if(s.to_lft > s.to_rgt)          // in your way. 
        lane -= DELTA_LANE;            // lane must be a static variable 
      else 
        lane += DELTA_LANE; 

    result.vc = vc;   result.alpha = alpha; 

    // Pit: if the fuel is too low
    //  Fuel: full
    //  Damage: repair all
    if( s.fuel<10.0 ) 
    {
      result.request_pit   = 1;
      result.repair_amount = s.damage;
      result.fuel_amount = MAX_FUEL;
    }

    return result; 
  } 