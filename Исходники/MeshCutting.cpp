void MeshCutting::setRotationCase(Vec3f localAxis)
{
	if (localAxis[X_AXIS] == X_AXIS){
		if (localAxis[Y_AXIS] == Y_AXIS){
			// 012, O'x'y'z' wrt Oxyz 
			// (Local axis of mesh is same as global axis)
			return;
		}
		else {
			// 021, O'x'z'y' wrt Oxyz
			glRotatef(-90, 1, 0, 0);
		}
	} else if (localAxis[X_AXIS] == Y_AXIS){
		if (localAxis[Y_AXIS] == X_AXIS){
			// 102, O'y'x'z' wrt Oxyz
			glRotatef(-90, 0, 0, 1);
			// No need scaling as symmetric
		}
		else {
			// 120, O'y'z'x' wrt Oxyz			
			Quat quaternion = Quat::createQuaterFromEuler(Vec3f(0, -90 * 3.142 / 180, 0))
				* Quat::createQuaterFromEuler(Vec3f(-90 * 3.142 / 180, 0, 0));
			quaternion.normalize();
			Vec3d axis;	double angle;
			quaternion.quatToAxis(axis, angle);
			glRotatef(angle * 180 / 3.142, axis[0], axis[1], axis[2]);
		}
	}
	else {
		if (localAxis[Y_AXIS] == X_AXIS){
			// 201, O'z'x'y' wrt Oxyz
			Quat quaternion = Quat::createQuaterFromEuler(Vec3f(90 * 3.142 / 180, 0, 0))
				* Quat::createQuaterFromEuler(Vec3f(0, 0, 90 * 3.142 / 180));
			quaternion.normalize();
			Vec3d axis;	double angle;
			quaternion.quatToAxis(axis, angle);
			glRotatef(angle * 180 / 3.142, axis[0], axis[1], axis[2]);
		}
		else {
			// 210, O'z'y'x' wrt Oxyz
			glRotatef(90, 0, 1, 0);
		}
	}
}