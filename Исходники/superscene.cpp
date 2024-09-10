void SuperScene::moveCamera(float deltaTime)
{
	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 600.0f; // 600 units / second

	// Right and Down vector
	Point2 right = Point2(1, 0);
	Point2 up = Point2(0, 1);
	// Direction
	Vector2 direction = Vector2(0,0);

	if (input()->getKey( GLFW_KEY_UP )) {
		direction -= up;
	}
	if (input()->getKey( GLFW_KEY_DOWN )) {
		direction += up;
	}
	if (input()->getKey( GLFW_KEY_RIGHT )) {
		direction += right;
	}
	if (input()->getKey( GLFW_KEY_LEFT )) {
		direction -= right;
	}
	direction.normalize();
	direction *= deltaTime * speed;
	camera()->position += direction;
}