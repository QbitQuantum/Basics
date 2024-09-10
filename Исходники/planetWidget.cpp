void PlanetWidget::mouseReleaseEvent (QMouseEvent*) {
	if (!mouseMoving) {
		pointSelected(conjugate(rotation_to_default(planetHandler->planet())) * activeRenderer->to_coordinates(vector(mousePosition)));
	}
	mouseMoving = false;
}