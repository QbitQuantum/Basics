void CameraControl::Update(float delta) 
{
	if (is_looking_at_origin) 
	{
		Matrix m;
		Matrix::createLookAt(camera_node->getTranslation(), Vector3::zero(), Vector3::unitY(), &m);
		m.transpose();
		Quaternion q;
		m.getRotation(&q);
		camera_node->setRotation(q);
	}

	if (camera_move_direction != NONE) 
	{
		if (camera_move_direction & LEFT)
			camera_target += camera_node->getRightVector() * -CAMERA_VELOCITY;
		if (camera_move_direction & RIGHT)
			camera_target += camera_node->getRightVector() * CAMERA_VELOCITY;
		if (camera_move_direction & FORWARD)
			camera_target += camera_node->getForwardVector() * CAMERA_VELOCITY;
		if (camera_move_direction & BACKWARDS)
			camera_target += camera_node->getForwardVector() * -CAMERA_VELOCITY;

		//round target
		camera_target.x = (int) camera_target.x;
		camera_target.y = (int) camera_target.y;
		camera_target.z = (int) camera_target.z;
	}

	camera_node->translateSmooth(camera_target, delta, 100);
	camera_node->getMatrix();
}