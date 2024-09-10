void TrajectoryWaypoint::convert2Vector(Vector& lv) {
	if ( lv.length() != 3 ) {
		lv.deletion();
		lv.creation(3);
	}
	lv.setValueData(this->x,1);
	lv.setValueData(this->y,2);
	lv.setValueData(this->z,3);
}