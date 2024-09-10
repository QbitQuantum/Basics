void Rotator::rotate_to(float new_target)
{
	assert(!_isnan(new_target) && _finite(new_target));
	assert(_accel_current > 0);
	assert(_accel_stop > 0);

	new_target = fmodf(new_target, PI2);
	if( new_target < 0 ) new_target += PI2;

	if( new_target == _rCurrent && RS_STOPPED == _state ) return;

	_angle_target = new_target;
	_state = RS_GETTING_ANGLE;
}