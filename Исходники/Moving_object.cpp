// If the destination is within one delta step away, the object has arrived.
// Set the location to the destination, stop, and return true.
// Otherwise, add the delta to the location, and return false.
bool Moving_object::update_location()
{
	Cartesian_vector diff = destination - location;
	if ((fabs(diff.delta_x) <= fabs(delta.delta_x)) && (fabs(diff.delta_y) <= fabs(delta.delta_y))) {
		location = destination;
		stop_moving();
		return true;
		}
	location = location + delta;
	return false;
}