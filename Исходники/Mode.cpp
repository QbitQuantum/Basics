void TouchPoint::set(Touch::TouchEvent evt, int x, int y, const Plane &plane) {
	set(evt, x, y);
	Camera *camera = app->getCamera();
	Ray ray;
	camera->pickRay(app->getViewport(), x, y, &ray);
	float distance = ray.intersects(plane);
	if(distance != Ray::INTERSECTS_NONE) _point[evt] = ray.getOrigin() + ray.getDirection() * distance;
}