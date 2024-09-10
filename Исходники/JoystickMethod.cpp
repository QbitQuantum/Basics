vector2F JoystickMethod::getMovementVector() {
	float val_x = getAxisValueFloat(x_axis);
	float val_y = getAxisValueFloat(y_axis);
	return vector2F(val_x, val_y);
}