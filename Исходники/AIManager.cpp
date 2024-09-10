void AIManager::doPatrol(BaseModel* model)
{
	int direction = rand() % 4;
	float pos_x, pos_y, pos_z;
	switch (direction)
	{
	case 0:
		pos_x = model->getPositionX() + rand() % PATROL_RANGE + LEAST_DISTANCE;
		pos_z = model->getPositionZ() + rand() % PATROL_RANGE + LEAST_DISTANCE;
		break;
	case 1:
		pos_x = model->getPositionX() + rand() % PATROL_RANGE + LEAST_DISTANCE;
		pos_z = model->getPositionZ() - rand() % PATROL_RANGE + LEAST_DISTANCE;
		break;
	case 2:
		pos_x = model->getPositionX() - rand() % PATROL_RANGE + LEAST_DISTANCE;
		pos_z = model->getPositionZ() + rand() % PATROL_RANGE + LEAST_DISTANCE;
		break;
	case 3:
		pos_x = model->getPositionX() - rand() % PATROL_RANGE + LEAST_DISTANCE;
		pos_z = model->getPositionZ() - rand() % PATROL_RANGE + LEAST_DISTANCE;
		break;
	default:
		break;
	}
	pos_y = 0;
	model->_targetPos = Vec3(pos_x, pos_y, pos_z);
	Vec3 dir = model->_targetPos - model->getPosition3D();
	dir.y = 0;//使角色的头顶始终朝向y轴正方向
	dir.normalize();
	model->_headingAngle = -1 * acos(dir.dot(Vec3(0, 0, -1)));
	dir.cross(dir, Vec3(0, 0, -1), &model->_headingAxis);
	model->forward();
}