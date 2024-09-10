void path_data_item::assign(const arc& value) noexcept {
	_Has_data = true;
	_Data.arc.angle1 = value.angle_1();
	_Data.arc.angle2 = value.angle_2();
	_Data.arc.centerX = value.center().x();
	_Data.arc.centerY = value.center().y();
	_Data.arc.radius = value.radius();
	_Type = value.type();
}