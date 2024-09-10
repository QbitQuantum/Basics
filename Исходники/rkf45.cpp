// Sets the initial step size automatically. The function and initial
// y data must be set for this to work. f, t0 and y0 must be set
// before you can call this method. Also sets the max dt to the same
// value.
void RKF45::set_dt0() {
  // locals
  double yprime = norm(f(t0,y0));
  double y = norm(y0);
  double length_scale;
  if ( debug_level >= 3) {
    cout << "y = " << y << "\n" << "yprime = " << yprime << endl;
  }
  // y/y' = <change in t> * y/<change in y>. A good approximation of dt0. 
  length_scale = y/yprime;
  if ( debug_level >= 3 ) {
    cout << "length scale = " << length_scale << endl;
  }
  dt0 = abs(get_relative_error_factor() * length_scale);
  if ( debug_level >= 1 ) {
    cout << "dt0 = " << dt0 << endl;
    // cout << "Max step size: " << get_max_dt() << endl;
  }

  // dt0 must be a finite, positive number. If it's zero or NaN, make
  // it sqrt(machine epsilon).
  if ( !(dt0 > 0) ) {
    if ( debug_level >= 1 ) {
      cout << "WARNING: dt0 non-finite. Setting it to the default minimum dt"
	   << endl;
    }
    set_dt0(default_min_dt());
  }
  else {
    set_dt0(dt0);
  }
}