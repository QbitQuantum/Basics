void KorvianSniper::calculate()
{
  double angle2;

  
  if(beep == TRUE) {
	  if(target && target->exists() && !target->isInvisible()) {
		angle2 = angle - intercept_angle2(pos, vel * 1.0, weaponVelocity,
					target->normal_pos(), target->get_vel() );
		Vector2 v = 350*Vector2(unit_vector(angle+PI/2));
		double w = v.dot(target->get_vel())/distance(target);
		if(w < 0.0) w = -w;
		if(w > angle2 && angle2 > -w) {
			play_sound2(data->sampleSpecial[0]);
			beep = FALSE;
		}
	  }
	}

  Ship::calculate();
}